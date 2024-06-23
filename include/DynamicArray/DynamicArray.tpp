#include "DynamicArray.hpp"
#include "Element/Element.hpp"

template <typename Func, typename T, typename... Args>
void DynamicArray::handle_push(Func func, T value, Args&&... args) {
  if (py::isinstance<py::int_>(value)) {
    func(value.template cast<int>(), std::forward<Args>(args)...);
  } else if (py::isinstance<py::float_>(value)) {
    func(value.template cast<double>(), std::forward<Args>(args)...);
  } else if (py::isinstance<py::str>(value)) {
    func(value.template cast<std::string>(), std::forward<Args>(args)...);
  } else {
    throw std::runtime_error("Unsupported type");
  }
}

template <typename T>
void DynamicArray::insert(size_t index, T value) {
  if (index > _size) {
    throw std::out_of_range("Index out of range");
  }
  if (_size == _capacity) {
    _capacity = _capacity == 0 ? 1 : _capacity * 2;
  }
  for (size_t i = _size; i > index; --i) {
    _data[i] = _data[i - 1];
  }
  _data[index] = new Element<T>(value);
  _size++;
}

template <typename T>
void DynamicArray::push_back(T value) {
  if (_size == _capacity) {
    _capacity = _capacity == 0 ? 1 : _capacity * 2;
  }
  _data[_size++] = new Element<T>(value);
}

template <typename T>
void DynamicArray::push_front(T value) {
  if (_size == _capacity) {
    _capacity = _capacity == 0 ? 1 : _capacity * 2;
  }
  for (size_t i = _size; i > 0; --i) {
    _data[i] = _data[i - 1];
  }
  _data[0] = new Element<T>(value);
  _size++;
}

template void DynamicArray::push_back(int value);
template void DynamicArray::push_back(double value);
template void DynamicArray::push_back(const std::string& value);

template void DynamicArray::push_front(int value);
template void DynamicArray::push_front(double value);
template void DynamicArray::push_front(const std::string& value);

template void DynamicArray::insert(size_t index, int value);
template void DynamicArray::insert(size_t index, double value);
template void DynamicArray::insert(size_t index, const std::string& value);
