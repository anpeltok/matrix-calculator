#ifndef VARELEMENT_H
#define VARELEMENT_H

#include "element.h"

class VariableElement : public Element
{

public:
  VariableElement();
  VariableElement(char v);
  virtual ~VariableElement() = default;
  char getVal() const;
  void setVal(char v);
  Element* clone() const override;
  std::string toString() const override;
  int evaluate(const Valuation& v) const override;
  bool operator==(const VariableElement& i) const;

private:
  char var;
};

#endif // VARELEMENT_H