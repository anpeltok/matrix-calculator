/**
  * \file intelement.h
  * \brief Header for IntElement class
  */

#ifndef INTELEMENT_H
#define INTELEMENT_H
#include <sstream>
#include <stdexcept>
#include <memory>

/**
  * \class IntElement
  * \brief Class encapsulating int elements 
  */
class IntElement
{
public:
  IntElement();
  IntElement(int v);
  virtual ~IntElement() = default;
  int getVal() const;
  void setVal(int v);
  std::unique_ptr<IntElement> clone() const; 
  IntElement& operator+=(const IntElement& i);
  IntElement& operator-=(const IntElement& i);
  IntElement& operator*=(const IntElement& i);
  bool operator==(const IntElement& i) const;
  bool operator!=(const IntElement& i) const;


private:
  int val;

};

IntElement operator+(const IntElement& i1, const IntElement& i2);
IntElement operator-(const IntElement& i1, const IntElement& i2);
IntElement operator*(const IntElement& i1, const IntElement& i2);
std::ostream& operator<<(std::ostream& os, const IntElement& i);


#endif // INTELEMENT_H