// Copyright 2020-2021 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md

#if defined __link

#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include "fs/FileSystem.hpp"
#include "sys/Process.hpp"

extern "C" char **environ;

using namespace sys;

Process::Environment::Environment(char **env) : Process::Arguments("") {
  char **effective_env = (env == nullptr) ? environ : env;
  size_t i = 0;
  do {
    if (effective_env[i] != nullptr) {
      push(effective_env[i]);
      i++;
    }
  } while (effective_env[i] != nullptr);
}

Process::Environment &Process::Environment::set(const var::StringView name,
                 const var::StringView value) {

  auto format = [](const var::StringView name,
                   const var::StringView value){
    return name | "=" | value;
  };

  //check to see if the entry exists
  const auto starts_with = name | "=";
  for(size_t i=0; i < m_arguments.count(); i++){
    char * value = m_arguments.at(i);
    if( var::StringView(value).find(starts_with) == 0 ){
      replace(i, format(name,value));
      return *this;
    }
  }

  push(format(name,value));
  return *this;
}

Process::Environment& Process::Environment::set_working_directory(const var::StringView path){
  return set("PWD", path);
}

var::PathString Process::which(const var::StringView executable){
  const char * pwd = getenv("PWD");
  if( pwd ){
    if( const auto path = var::StringView(pwd) / executable; fs::FileSystem().exists(path) ){
      return path;
    }
  }

  const char * path = getenv("PATH");
  if( path == nullptr ){
    return var::PathString();
  }

  const auto path_list = var::StringView(path).split(";:");
  for(const auto & entry: path_list){
    const auto path = entry / executable;
    if( fs::FileSystem().exists(path) ){
      return path;
    }
  }

  return var::PathString();
}

u8 Process::Status::exit_status() const { return WEXITSTATUS(m_status_value); }

bool Process::Status::is_exited() const { return WIFEXITED(m_status_value) != 0; }
bool Process::Status::is_terminated() const {
  return WIFSIGNALED(m_status_value) != 0;
}
int Process::Status::terminated_signal_number() const {
  return WTERMSIG(m_status_value);
}
bool Process::Status::is_stopped() const {
  return WIFSTOPPED(m_status_value) != 0;
}
int Process::Status::stopped_signal_number() const {
  return WSTOPSIG(m_status_value);
}
bool Process::Status::is_continued() const {
  return WIFCONTINUED(m_status_value) != 0;
}

Process::Process(const Arguments &arguments, const Environment &environment) {
  API_RETURN_IF_ERROR();
  m_pid = API_SYSTEM_CALL("fork()", fork());
  if (m_pid == 0) {

    // this will run in the child process
    Arguments args(arguments);
    Environment env(environment);


    dup2(m_pipe.write_file().fileno(), STDOUT_FILENO);
    // stdout will now write to the pipe -- this fileno isn't needed anymore
    // but doesn't necessarily have to be closed
    m_pipe.write_file() = fs::File();
    // replace the current process with the one specified
    ::execve(args.m_arguments.at(0), args.m_arguments.data(), environ);
    perror("failed to launch\n");
    exit(1);
  }
}

Process::~Process() {
  // if process is NOT detached -- wait for it to complete
  wait();
}

Process &Process::wait() {
  API_RETURN_VALUE_IF_ERROR(*this);
  if (m_pid < 0) {
    return *this;
  }

  int status = 0;
  auto result = API_SYSTEM_CALL("waitpid()", ::waitpid(m_pid, &status, 0));
  if( result == m_pid ){
    m_pid = -1;
    m_status = status;
  }

  return *this;
}

bool Process::is_running(){
  API_RETURN_VALUE_IF_ERROR(false);
  if( m_pid < 0 ){
    return false;
  }

  api::ErrorScope error_scope;
  int status = 0;
  auto result = API_SYSTEM_CALL("waitpid()", ::waitpid(m_pid, &status, WNOHANG));
  if( result == m_pid ){
    m_status = status;
    m_pid = -1;
    return false;
  }

  return true;
}

#endif
