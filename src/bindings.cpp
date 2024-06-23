#include "DynamicArray/DynamicArray.hpp"
#include "Element/Element.hpp"

PYBIND11_MODULE(DynamicArrayProject, m) {
  py::class_<BaseElement>(m, "BaseElement")
      .def("getType", &BaseElement::getType);

  py::class_<DynamicArray>(m, "DynamicArray")
      .def(py::init<>())
      .def(py::init<size_t>())
      .def(py::init<size_t, const py::list&>())
      .def("begin", [](DynamicArray& self) { return py::cast(*self.begin()); })
      .def("capacity", [](DynamicArray& self) { return self.capacity(); })
      .def("clear", [](DynamicArray& self) { self.clear(); })
      .def("end", [](DynamicArray& self) { return py::cast(*self.end()); })
      .def("insert",
           [](DynamicArray& self, size_t index, const py::object& value) {
             self.insert_py(index, value);
           })
      .def("pop", [](DynamicArray& self, size_t index) { self.pop(index); })
      .def("pop_back", [](DynamicArray& self) { self.pop_back(); })
      .def("pop_front", [](DynamicArray& self) { self.pop_front(); })
      .def("push_back",
           [](DynamicArray& self, const py::object& value) {
             self.push_back_py(value);
           })
      .def("push_front",
           [](DynamicArray& self, const py::object& value) {
             self.push_front_py(value);
           })
      .def("resize",
           [](DynamicArray& self, size_t new_size) { self.resize(new_size); })
      .def("reverse", [](DynamicArray& self) { self.reverse(); })
      .def("shrink_to_fit", [](DynamicArray& self) { self.shrink_to_fit(); })
      .def("size", &DynamicArray::size)
      .def("swap", [](DynamicArray& self, size_t index1,
                      size_t index2) { self.swap(index1, index2); })
      .def(
          "__getitem__",
          [](DynamicArray& self, size_t index) -> py::object {
            std::string type = self[index]->getType();
            if (type == typeid(int).name()) {
              return py::cast(
                  dynamic_cast<Element<int>*>(self[index])->getValue());
            } else if (type == typeid(double).name()) {
              return py::cast(
                  dynamic_cast<Element<double>*>(self[index])->getValue());
            } else if (type == typeid(std::string).name()) {
              return py::cast(
                  dynamic_cast<Element<std::string>*>(self[index])->getValue());
            } else {
              throw std::runtime_error("Unsupported type");
            }
          })
      .def("__setitem__", [](DynamicArray& self, size_t index,
                             const py::object& value) {
        if (py::isinstance<py::int_>(value)) {
          self[index] = new Element<int>(value.cast<int>());
        } else if (py::isinstance<py::float_>(value)) {
          self[index] = new Element<double>(value.cast<double>());
        } else if (py::isinstance<py::str>(value)) {
          self[index] = new Element<std::string>(value.cast<std::string>());
        } else {
          throw std::runtime_error("Unsupported type");
        }
      });
}
