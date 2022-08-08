//
// Created by Tyler Gilbert on 8/8/22.
//

#ifndef VAR_API_SET_HPP_
#define VAR_API_SET_HPP_

#include <set>
#include <unordered_set>
#include <functional>

#include "ContainerObject.hpp"

namespace var {

template <typename Key, class Compare = std::less<Key>>
class OrderedSet : public ContainerObject<OrderedSet<Key,Compare>, std::set<Key, Compare>, Key> {
  using Base = ContainerObject<Vector<Key>, std::set<Key, Compare>, Key>;

public:

  using Self = OrderedSet<Key,Compare>;

  using iterator = typename std::set<Key,Compare>::iterator;
  using const_iterator = typename std::set<Key,Compare>::const_iterator;
  using reverse_iterator = typename std::set<Key,Compare>::reverse_iterator;
  using const_reverse_iterator =
    typename std::set<Key,Compare>::const_reverse_iterator;

  iterator insert(const_iterator hint, const Key &value) {
    return this->m_container.insert(hint, value);
  }

  Self& insert(const Key & value){
    this->m_container.insert(value);
    return *this;
  }

  Self& insert(Key && value){
    this->m_container.insert(std::forward<Key>(value));
    return *this;
  }

  Self& erase(const Key & value){
    this->m_container.erase(value);
    return *this;
  }

  iterator lookup(const Key & value){
    return this->m_container.find(value);
  }

  const_iterator lookup(const Key & value) const {
    return this->m_container.find(value);
  }

private:


};

#if 0
//TODO No reverse iterator. Can't just inherit ContainerObject
template <typename Key, class Hash = std::hash<Key>>
class UnorderedSet : public ContainerObject<UnorderedSet<Key,Hash>, std::unordered_set<Key, Hash>, Key> {
  using Base = ContainerObject<Vector<Key>, std::unordered_set<Key, Hash>, Key>;

public:

  using Self = UnorderedSet<Key,Hash>;

  using iterator = typename std::unordered_set<Key,Hash>::iterator;
  using const_iterator = typename std::unordered_set<Key,Hash>::const_iterator;
  using reverse_iterator = typename std::unordered_set<Key,Hash>::reverse_iterator;
  using const_reverse_iterator =
    typename std::unordered_set<Key,Hash>::const_reverse_iterator;

  iterator insert(const_iterator hint, const Key &value) {
    return this->m_container.insert(hint, value);
  }

  Self& insert(const Key & value){
    this->m_container.insert(value);
    return *this;
  }

  Self& insert(Key && value){
    this->m_container.insert(std::forward<Key>(value));
    return *this;
  }

  Self& erase(const Key & value){
    this->m_container.erase(value);
    return *this;
  }

  iterator lookup(const Key & value){
    return this->m_container.find(value);
  }

  const_iterator lookup(const Key & value) const {
    return this->m_container.find(value);
  }

private:

};
#endif

} // namespace var
#endif // VAR_API_SET_HPP_
