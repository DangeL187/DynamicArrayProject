#include "Element.hpp"

template <typename T>
Element<T>::Element(T value) : value(value) {}

template <typename T>
T Element<T>::getValue() const {
  return value;
}

template <typename T>
std::string Element<T>::getType() const {
  return typeid(T).name();
}