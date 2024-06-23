#include "DynamicArray/DynamicArray.hpp"

DynamicArray::DynamicArray() : _capacity(1) {
  _data = std::make_unique<BaseElement*[]>(_capacity);
}

DynamicArray::DynamicArray(size_t size) : _capacity(size * 2) {
  _data = std::make_unique<BaseElement*[]>(_capacity);
  for (int i = 0; i < size; ++i) {
    push_back(0);
  }
}

DynamicArray::DynamicArray(size_t size, const py::list& values)
    : _capacity(size * 2) {
  _data = std::make_unique<BaseElement*[]>(_capacity);
  for (auto& value : values) {
    push_back_py((const py::object&)value);
  }
}

DynamicArray::~DynamicArray() { clear(); }

BaseElement** DynamicArray::begin() const { return _data.get(); }

size_t DynamicArray::capacity() const { return _capacity; }

void DynamicArray::clear() {
  for (size_t i = 0; i < _size; ++i) {
    delete _data[i];
  }
  _size = 0;
}

BaseElement** DynamicArray::end() const { return _data.get() + _size - 1; }

void DynamicArray::insert_py(size_t index, const py::object& value) {
  handle_push([this, index](auto v) { insert(index, v); }, value);
}

void DynamicArray::pop(size_t index) {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  delete _data[index];
  for (size_t i = index + 1; i < _size; ++i) {
    _data[i - 1] = _data[i];
  }
  _size--;
}

void DynamicArray::pop_back() {
  if (_size == 0) {
    throw std::underflow_error("Container is empty");
  }
  delete _data[--_size];
}

void DynamicArray::pop_front() {
  if (_size == 0) {
    throw std::underflow_error("Container is empty");
  }
  delete _data[0];
  for (size_t i = 1; i < _size; ++i) {
    _data[i - 1] = _data[i];
  }
  _size--;
}

void DynamicArray::push_back_py(const py::object& value) {
  handle_push([this](auto v) { this->push_back(v); }, value);
}

void DynamicArray::push_front_py(const py::object& value) {
  handle_push([this](auto v) { this->push_front(v); }, value);
}

void DynamicArray::resize(size_t new_size) {
  if (_size == new_size) {
    return;
  }
  if (new_size < _size) {
    for (size_t i = new_size; i < _size; ++i) {
      delete _data[i];
    }
    _size = new_size;
    return;
  }
  std::unique_ptr<BaseElement*[]> new_data(new BaseElement*[new_size]);
  for (size_t i = 0; i < _size; ++i) {
    new_data[i] = _data[i];
  }
  for (size_t i = _size; i < new_size; ++i) {
    new_data[i] = new Element<int>(0);
  }
  _data = std::move(new_data);
  _size = new_size;
  _capacity = new_size;
}

void DynamicArray::reverse() {
  for (size_t i = 0; i < _size / 2; ++i) {
    swap(i, _size - 1 - i);
  }
}

void DynamicArray::shrink_to_fit() {
  if (_size == _capacity) {
    return;
  }
  std::unique_ptr<BaseElement*[]> new_data(new BaseElement*[_size]);
  for (size_t i = 0; i < _size; ++i) {
    new_data[i] = _data[i];
  }
  _data = std::move(new_data);
  _capacity = _size;
}

size_t DynamicArray::size() const { return _size; }

void DynamicArray::swap(size_t index1, size_t index2) {
  if (index1 >= _size || index2 >= _size) {
    throw std::out_of_range("Index out of range");
  }
  std::swap(_data[index1], _data[index2]);
}

BaseElement*& DynamicArray::operator[](size_t index) {
  if (index >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return _data[index];
}
