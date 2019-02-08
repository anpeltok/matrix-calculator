#ifndef ELEMENT_H
#define ELEMENT_H

#include <sstream>
#include <stdexcept>
#include <memory>
#include "valuation.h"

class Element
{
public:
  virtual ~Element() = default;
  virtual Element* clone() const = 0;
  virtual std::string toString() const = 0;
  virtual int evaluate(const Valuation& val) const = 0;

};

std::ostream& operator<<(std::ostream& os, const Element& i);



#endif // ELEMENT_H