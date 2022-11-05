
#include <cstdio>
#include <signal.h>

#include "api/api.hpp"
#include "test/Test.hpp"
#include "thread/Thread.hpp"
#include "thread/Mutex.hpp"
#include "thread/Sem.hpp"
#include "thread/Cond.hpp"
#include "thread/Signal.hpp"

using namespace var;
using namespace chrono;
using namespace thread;

#if defined __win32
#define IS_CANCEL_OK false
#else
#define IS_CANCEL_OK true
#endif

using T = thread::Thread;
using M = thread::Mutex;
using S = thread::Signal;
using Sem = thread::Semaphore;

void signal_handler(int a) {
  printf("signal %d\n", a);
  API_ASSERT(false);
  exit(1);
}

static volatile int m_signal_number_io = 0;

class UnitTest : public test::Test {

  volatile bool m_did_execute;
  M *m_mutex_pointer;
  M m_mutex;
  M m_thread_mutex;
  Cond m_cond = Cond(m_thread_mutex);

#if defined __link
  static constexpr size_t minimum_stack_size = 65536;
#else
  static constexpr size_t minimum_stack_size = 8192;
#endif

public:
  UnitTest(var::StringView name) : test::Test(name) {}

  bool execute_class_api_case() {
    TEST_ASSERT_RESULT(thread_api_case());
    TEST_ASSERT_RESULT(mutex_api_case());
    TEST_ASSERT_RESULT(cond_api_case());

#if !defined __macosx && !defined __win32
    TEST_ASSERT_RESULT(sem_api_case());
#endif

    TEST_ASSERT_RESULT(signal_api_case());
    TEST_ASSERT_RESULT(sched_api_case());

    return true;
  }

  bool cond_api_case() {
    printer::Printer::Object po(printer(), "cond_api_case()");

    class ConditionContext {
    public:
      ConditionContext() : cond(mutex) {}
      Cond cond;
      Mutex mutex;
      volatile bool ready = false;
    };

    auto set_ready = [](ConditionContext &context) -> void * {
      Mutex::Guard mg(context.mutex);
      context.ready = true;
      context.cond.signal();
      return nullptr;
    };

    auto wait_for_ready = [](void *args) -> void * {
      ConditionContext *context = reinterpret_cast<ConditionContext *>(args);
      Mutex::Guard mg(context->mutex);
      while (context->ready == false) {
        context->cond.wait();
      }
      return nullptr;
    };

    TEST_ASSERT(is_success());

    {
      ConditionContext context;
      Thread t = Thread(
                   Thread::Attributes().set_joinable(),
                   Thread::Construct().set_argument(&context).set_function(
                     wait_for_ready))
                   .move();
      printer().key("wait", "ready");
      set_ready(context);
      printer().key("cond", "signal");
      context.cond.signal();
      t.join();
    }
    TEST_ASSERT(is_success());

    {
      ConditionContext context;
      Thread t = Thread(
                   Thread::Attributes().set_joinable(),
                   Thread::Construct().set_argument(&context).set_function(
                     wait_for_ready))
                   .move();
      printer().key("set", "ready");
      set_ready(context);
      printer().key("cond", "broadcast");
      context.cond.broadcast();
      t.join();
    }
    TEST_ASSERT(is_success());

    auto wait_timed_for_condition = [](void *args) -> void * {
      ConditionContext *context = reinterpret_cast<ConditionContext *>(args);
      context->cond.lock();
      context->ready = true;
      context->cond.wait_timed(ClockTime(250_milliseconds));
      return nullptr;
    };

    {
      ConditionContext context;
      Thread t = Thread(
                   Thread::Attributes().set_joinable(),
                   Thread::Construct().set_argument(&context).set_function(
                     wait_timed_for_condition))
                   .move();
      printer().key("wait", "timed");
      t.join();
    }
    TEST_ASSERT(is_success());

    return true;
  }

  bool sched_api_case() { return true; }
  bool signal_api_case() {
    printer::Printer::Object po(printer(), "signal_api_case()");
    {
      m_signal_number_io = 0;
      SignalHandler handler
        = SignalHandler(SignalHandler::Construct().set_signal_function(
          [](int a) { m_signal_number_io = 1; }));

#if !defined __win32
      SignalHandler action_handler
        = SignalHandler(SignalHandler::Construct().set_signal_action(
          [](int signo, siginfo_t *sig_info, void *context) {
            m_signal_number_io = sig_info->si_value.sival_int;
          }));

      S s = S(S::Number::terminate).set_handler(handler);
      S sa = S(S::Number::user1, 100).set_handler(action_handler);

      s.send(Sched::get_pid());
      TEST_ASSERT(m_signal_number_io == 1);

      sa.send(Sched::get_pid());
      printer().key_bool("sigqueue", m_signal_number_io == 100);
#endif
    }

    return true;
  }

  bool sem_api_case() {
    printer::Printer::Object po(printer(), "sem_api_case()");
    {

      Sem::unlink("sem");
      reset_error();

      PRINTER_TRACE(printer(), "wait, post");
      TEST_ASSERT(Sem(5, Sem::IsExclusive::yes, "sem").wait().is_success());

      PRINTER_TRACE(printer(), "exclusive");
      TEST_ASSERT(Sem(5, Sem::IsExclusive::yes, "sem").is_error());
      reset_error();

      PRINTER_TRACE(printer(), "not exclusive");
      TEST_ASSERT(Sem(5, Sem::IsExclusive::no, "sem")
                    .wait()
                    .wait()
                    .wait()
                    .post()
                    .post()
                    .post()
                    .unlink()
                    .is_success());
    }

    {

      PRINTER_TRACE(printer(), "semT");

      Sem::unlink("semT");
      reset_error();

      Sem sem = std::move(Sem(3, Sem::IsExclusive::yes, "semT").wait().wait());
      TEST_ASSERT(is_success());

      m_did_execute = false;

      T t = T(
        T::Attributes().set_detach_state(T::DetachState::joinable),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            PRINTER_TRACE(self->printer(), "wait sem in thread");
            Sem sem = std::move(Sem("semT").wait());
            self->m_did_execute = true;
            PRINTER_TRACE(self->printer(), "done");
            sem.post();
            printer().key_bool("error", is_error());
            return nullptr;
          }));

      TEST_ASSERT(m_did_execute == false);
      wait(250_milliseconds);
      TEST_ASSERT(is_success());

      TEST_ASSERT(sem.post().post().is_success());

      Sched().yield();
      TEST_ASSERT(is_success());

      TEST_ASSERT(sem.wait().is_success());
      PRINTER_TRACE(printer(), "check did exec");
      TEST_ASSERT(m_did_execute == true);
      TEST_ASSERT(t.join().is_success());

      Sem::unlink("semT");
      reset_error();
      Sem::unlink("sem");
      reset_error();
    }
    return true;
  }

  bool mutex_api_case() {

    {
      auto value = false;
      Mutex mutex;
      Mutex::Scope(mutex, [&]() { value = true; });
      TEST_ASSERT(value);
    }

    {
      m_did_execute = false;
      Mutex m(Mutex::Attributes().set_type(Mutex::Type::recursive));
      m_mutex_pointer = &m;

      TEST_ASSERT(m.lock().lock().lock().is_success());

      T t = T(
        T::Attributes().set_detach_state(T::DetachState::joinable),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            self->m_mutex_pointer->lock().lock();
            self->m_did_execute = true;
            self->m_mutex_pointer->unlock().unlock();
            self->m_cond.set_asserted(true);
            return nullptr;
          }));

      TEST_ASSERT(m.unlock().unlock().unlock().is_success());
      // TEST_ASSERT(t.wait().is_success());
      m_cond.wait_until_asserted().set_asserted(false);

      m.unlock();
      reset_error();
      TEST_ASSERT(m_did_execute);
    }
    {

      printer::Printer::Object po(printer(), "Mutex::Attributes");
      printer().key_bool(
        "protocolNoneOk",
        M::Attributes().set_protocol(M::Protocol::priority_none).get_protocol()
          == M::Protocol::priority_none);

      printer().key_bool(
        "protocolInheritOk",
        M::Attributes()
            .set_protocol(M::Protocol::priority_inherit)
            .get_protocol()
          == M::Protocol::priority_inherit);

      printer().key_bool(
        "protocolProtectOk",
        M::Attributes()
            .set_protocol(M::Protocol::priority_protect)
            .get_protocol()
          == M::Protocol::priority_protect);

      printer().key_bool(
        "processSharedPrivateOk",
        M::Attributes()
            .set_process_shared(M::ProcessShared::private_)
            .get_process_shared()
          == M::ProcessShared::private_);

      printer().key_bool(
        "processSharedOk",
        M::Attributes()
            .set_process_shared(M::ProcessShared::shared)
            .get_process_shared()
          == M::ProcessShared::shared);

      printer().key_bool(
        "recursiveOk",
        M::Attributes().set_type(M::Type::recursive).get_type()
          == M::Type::recursive);

      printer().key_bool(
        "normalOK",
        M::Attributes().set_type(M::Type::normal).get_type()
          == M::Type::normal);

      printer().key_bool(
        "priority10Ok",
        M::Attributes().set_priority_ceiling(10).get_priority_ceiling() == 10);
    }

    return true;
  }

  bool thread_api_case() {
    TEST_ASSERT(is_success());

#if !defined __win32
    {

      TEST_ASSERT(
        T::Attributes().set_stack_size(4096).get_stack_size() >= 4096);

      auto test_policy
        = [](UnitTest *self, const Sched::Policy policy) -> bool {
        const int min_priority = Sched::get_priority_min(policy);
        const int max_priority = Sched::get_priority_max(policy);
        TEST_SELF_ASSERT(min_priority <= max_priority);
        TEST_SELF_ASSERT(is_success());

        TEST_SELF_ASSERT(
          T::Attributes().set_sched_policy(policy).get_sched_policy()
          == policy);

        for (int i = min_priority; i <= max_priority; i++) {
          TEST_SELF_ASSERT(
            T::Attributes()
              .set_sched_policy(policy)
              .set_sched_priority(i)
              .get_sched_priority()
            == i);
        }
        return true;
      };

      TEST_ASSERT(test_policy(this, Sched::Policy::round_robin));
      TEST_ASSERT(test_policy(this, Sched::Policy::fifo));
      TEST_ASSERT(test_policy(this, Sched::Policy::other));
    }

    {
      printer::Printer::Object po(printer(), "Thread::Attributes");
      T::Attributes attributes
        = T::Attributes().set_scope(T::ContentionScope::process);
#if defined __StratifyOS__
      TEST_ASSERT(is_error());
      TEST_ASSERT(api::ExecutionContext::error().error_number() == EINVAL);
      API_RESET_ERROR();
#else
      TEST_ASSERT(is_success());
#endif

      printer().key_bool(
        "scopeProcessOk",
        attributes.get_scope() == T::ContentionScope::process);
      TEST_ASSERT(is_success());

      attributes.set_scope(T::ContentionScope::system);
      TEST_ASSERT(is_success());

      printer().key_bool(
        "scopeSystemOk",
        attributes.get_scope() == T::ContentionScope::system);
      TEST_ASSERT(is_success());

      attributes = T::Attributes().set_inherit_sched(T::IsInherit::yes);

      TEST_ASSERT(is_success());
      printer().key_bool(
        "inheritOk",
        attributes.get_inherit_sched() == T::IsInherit::yes);

#if !defined __StratifyOS__
      TEST_ASSERT(
        attributes.get_inherit_sched() == T::IsInherit::yes
        || attributes.get_inherit_sched() == T::IsInherit::no);

      TEST_ASSERT(is_success());

      attributes.set_inherit_sched(T::IsInherit::no);

      printer().key_bool(
        "explicitOk",
        attributes.get_inherit_sched() == T::IsInherit::no);

      TEST_ASSERT(
        attributes.get_inherit_sched() == T::IsInherit::yes
        || attributes.get_inherit_sched() == T::IsInherit::no);

      TEST_ASSERT(is_success());
#else
      API_RESET_ERROR();
#endif
    }
#endif

    {
      printer().key("didExecuteLocation", NumberString(&m_did_execute, "%p"));
      m_did_execute = false;
      T t(
        T::Attributes().set_joinable(),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            self->m_did_execute = true;
            return nullptr;
          }));

      TEST_ASSERT(is_success());

#if !defined __link
      const int priority = Sched::get_priority_min(Sched::Policy::fifo);

      TEST_ASSERT(
        t.set_sched_parameters(Sched::Policy::fifo, priority)
          .get_sched_priority()
        == priority);

      printer().key(
        "policy",
        NumberString(static_cast<int>(t.get_sched_policy())));
      TEST_ASSERT(t.get_sched_policy() == Sched::Policy::fifo);
#endif

      TEST_ASSERT(t.join().is_success());
      TEST_ASSERT(m_did_execute);
    }

    {
      m_did_execute = false;
      printer().key("wait", "joinable");
      printer().key_bool("asserted", m_cond.is_asserted());
      T(T::Attributes().set_detach_state(T::DetachState::joinable),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            self->m_did_execute = true;
            self->printer().key("condition", "assert");
            self->m_cond.set_asserted();
            return nullptr;
          }))
        .join();

      m_cond.wait_until_asserted().set_asserted(false);
      TEST_ASSERT(is_success());
      TEST_ASSERT(m_did_execute);

      m_did_execute = false;
      printer().key("wait", "joinable api::Function");
      printer().key_bool("asserted", m_cond.is_asserted());
      T(T::Attributes().set_detach_state(T::DetachState::joinable),
        [&]() -> void * {
          m_did_execute = true;
          printer().key("condition", "assert");
          m_cond.set_asserted();
          return nullptr;
        })
        .join();

      m_cond.wait_until_asserted().set_asserted(false);
      TEST_ASSERT(is_success());
      TEST_ASSERT(m_did_execute);

      printer().key("wait", "detached");
      printer().key_bool("asserted", m_cond.is_asserted());
      m_did_execute = false;
      T(T::Attributes().set_detach_state(T::DetachState::detached),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            self->m_did_execute = true;
            self->m_cond.set_asserted();
            return nullptr;
          }));

      m_cond.wait_until_asserted().set_asserted(false);
      TEST_ASSERT(is_success());
      TEST_ASSERT(m_did_execute);
      TEST_ASSERT(!m_cond.is_asserted());
    }

#if !__SANITIZE_THREAD__
    {

      // this section does not work if -fsanitize=thread is enabled
      m_did_execute = true;
      printer().key("wait", "joinable - cancel");
      auto t = T(
        T::Attributes().set_joinable(),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            while (IS_CANCEL_OK) {
              wait(10_milliseconds);
            }
            self->m_did_execute = false;
            return nullptr;
          }));

      TEST_ASSERT(is_success());

      const auto old_state = t.set_cancel_state(T::CancelState::enable);
      printer().key("oldState", Thread::to_cstring(old_state));
      printer().key(
        "newState",
        Thread::to_cstring(t.set_cancel_state(T::CancelState::enable)));
      const auto old_type = t.set_cancel_type(T::CancelType::deferred);
      printer().key("oldType", Thread::to_cstring(old_type));

      printer().key("thread", "cancel");
      t.cancel();
      TEST_ASSERT(is_success());
      printer().key("thread", "join");
      TEST_ASSERT(t.join().is_success());
      TEST_ASSERT(is_success());
      TEST_ASSERT(m_did_execute == IS_CANCEL_OK);
      printer().key_bool("didExecute", m_did_execute);
    }
#endif

    {
      m_did_execute = false;
      printer().key("wait", "minstacksize");
      T(T::Attributes().set_joinable().set_stack_size(minimum_stack_size),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            auto *self = reinterpret_cast<UnitTest *>(args);
            self->m_did_execute = true;
            self->m_cond.set_asserted();
            return nullptr;
          }))
        .join();

      m_cond.wait_until_asserted().set_asserted(false);
      TEST_ASSERT(m_did_execute);
    }

    {
      TEST_ASSERT(m_mutex.lock().is_success());
      TEST_ASSERT(Thread::self() == Thread::self());

      m_did_execute = false;
      T t = T(
        T::Attributes().set_detach_state(T::DetachState::joinable),
        T::Construct().set_argument(this).set_function(
          [](void *args) -> void * {
            UnitTest *self = reinterpret_cast<UnitTest *>(args);
            Mutex::Guard mg(self->m_mutex);
            Mutex::Guard t_mg(self->m_thread_mutex);
            self->printer().info("wait 250ms");
            wait(250_milliseconds);
            self->m_did_execute = true;
            return nullptr;
          }));

      // unlock to allow thread to continue
      TEST_ASSERT(m_mutex.unlock().is_success());
      wait(10_milliseconds);
      TEST_ASSERT(m_mutex.try_lock() == false);

      while (m_thread_mutex.try_lock() == false) {
        wait(10_milliseconds);
      }
      m_thread_mutex.unlock();

      TEST_ASSERT(t.is_joinable());
      TEST_ASSERT(t.join().is_success());
      TEST_ASSERT(m_did_execute);
    }

    return true;
  }
};
