#ifndef INTELEMENT_H
#define INTELEMENT_H

#include "element.h"

class IntElement : public Element
{
public:
  IntElement();
  IntElement(int v);
  virtual ~IntElement() = default;
  int getVal() const;
  void setVal(int v);
  Element* clone() const override;
  std::string toString() const override;
  int evaluate(const Valuation& v) const override;
  IntElement& operator+=(const IntElement& i);
  IntElement& operator-=(const IntElement& i);
  IntElement& operator*=(const IntElement& i);
  bool operator==(const IntElement& i) const;

private:
  int val;

};

IntElement operator+(const IntElement& i1, const IntElement& i2);
IntElement operator-(const IntElement& i1, const IntElement& i2);
IntElement operator*(const IntElement& i1, const IntElement& i2);

#endif // INTELEMENT_H