/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see
             // LICENSE.md for rights.
#ifndef VAR_API_LIST_HPP_
#define VAR_API_LIST_HPP_

#include <list>

#include "Queue.hpp"

/*! \cond */

namespace var {

// this shouldn't be documented until it is implemented and tested
template <class T> class List : public api::ExecutionContext {
public:
  List();

private:
  std::list<T> m_list;
};

} // namespace var

/*! \endcond */

#endif // VAR_API_LIST_HPP_
