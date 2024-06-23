#ifndef DYNAMICARRAYPROJECT_DYNAMICARRAY_HPP
#define DYNAMICARRAYPROJECT_DYNAMICARRAY_HPP

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>

namespace py = pybind11;

class BaseElement;
template <typename T>
class Element;

class DynamicArray {
 public:
  DynamicArray();
  explicit DynamicArray(size_t size);
  DynamicArray(size_t size, const py::list& values);
  ~DynamicArray();

  [[nodiscard]] BaseElement** begin() const;
  [[nodiscard]] size_t capacity() const;
  void clear();
  [[nodiscard]] BaseElement** end() const;

  template <typename Func, typename T, typename... Args>
  void handle_push(Func func, T value, Args&&... args);

  template <typename T>
  void insert(size_t index, T value);

  void insert_py(size_t index, const py::object& value);
  void pop(size_t index);
  void pop_back();
  void pop_front();

  template <typename T>
  void push_back(T value);

  void push_back_py(const py::object& value);

  template <typename T>
  void push_front(T value);

  void push_front_py(const py::object& value);
  void resize(size_t new_size);

  void reverse();
  void shrink_to_fit();
  [[nodiscard]] size_t size() const;
  void swap(size_t index1, size_t index2);
  BaseElement*& operator[](size_t index);

 private:
  size_t _capacity;
  std::unique_ptr<BaseElement*[]> _data;
  size_t _size = 0;
};

#include "DynamicArray.tpp"

#endif  // DYNAMICARRAYPROJECT_DYNAMICARRAY_HPP
