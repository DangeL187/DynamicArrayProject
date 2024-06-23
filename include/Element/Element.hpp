#ifndef DYNAMICARRAYPROJECT_ELEMENT_HPP
#define DYNAMICARRAYPROJECT_ELEMENT_HPP

#include <string>
#include <typeinfo>

class BaseElement {
 public:
  virtual ~BaseElement() = default;
  [[nodiscard]] virtual std::string getType() const = 0;
};

template <typename T>
class Element : public BaseElement {
 public:
  explicit Element(T value);
  [[nodiscard]] T getValue() const;
  [[nodiscard]] std::string getType() const override;

 private:
  T value;
};

#include "Element.tpp"

#endif  // DYNAMICARRAYPROJECT_ELEMENT_HPP
