/**
  * \file intelement.cpp
  * \brief IntElement class
  */
#include "intelement.h"

/**
  * \brief Empty default constructor for IntElement class
  */
IntElement::IntElement() : IntElement{0}{
  
}

/**
  * \brief Constructor for IntElement class
  * \param v Int value to be stored in IntElement class
  */
IntElement::IntElement(int v) : val{v}{
}

/**
  * \brief Getter for int value
  * \return Int value stored in val
  */
int IntElement::getVal() const{
  return val;
}

/**
  * \brief Setter for int value
  * \param v Value to be stored in val
  */
void IntElement::setVal(int v){
  val = v;
}

/**
  * \brief Creates a clone of self and returns pointer to it
  * \return Pointer to clone of self
  */
Element* IntElement::clone() const{
  
  IntElement* ptr{new IntElement{val}};

  return ptr;
}

/**
  * \brief Makes string of IntElement's val
  * \return String containing IntElement's val
  */
std::string IntElement::toString() const{

  std::stringstream ss;
  ss << val;
  return ss.str();}

/**
  * \brief Returns int value of element
  * \param v Map for char variables and int values
  * \return Int value of element
  */
int IntElement::evaluate(const Valuation& v) const{
  return val;
}

/**
  * \brief Operator overload for operator += for IntElements
  * \param i IntElement to be added to self
  * \return Self
  */
IntElement& IntElement::operator+=(const IntElement& i){
  val = val + i.val;
  return *this;
}

/**
  * \brief Operator overload for operator -= for IntElements
  * \param i IntElement to be subtracted from self
  * \return Self
  */
IntElement& IntElement::operator-=(const IntElement& i){
  val = val - i.val;
  return *this;
}

/**
  * \brief Operator overload for operator *= for IntElements
  * \param i IntElement for self to be multiplied by
  * \return Self
  */
IntElement& IntElement::operator*=(const IntElement& i){
  val = val * i.val;
  return *this;
}

/**
  * \brief Checks if parameter IntElement is identical to self
  * \param i IntElement to be compared to
  * \return True if vals in parameter and self are same, false if not
  */
bool IntElement::operator==(const IntElement& i) const{

  if(val == i.val)
    return true;
  else
    return false;

}

/**
  * \brief Operator overload for operator + for IntElements
  * \param i1 First IntElement
  * \param i2 Second IntElement
  * \return IntElement with sum of parameters' int vals
  */
IntElement operator+(const IntElement& i1, const IntElement& i2){
  IntElement result{i1};
  result += i2;
  return result;
}

/**
  * \brief Operator overload for operator - for IntElements
  * \param i1 First IntElement
  * \param i2 Second IntElement
  * \return IntElement with second parameter's int val subtracted from first parameter's int val
  */
IntElement operator-(const IntElement& i1, const IntElement& i2){
  IntElement result{i1};
  result -= i2;
  return result;
}

/**
  * \brief Operator overload for operator * for IntElements
  * \param i1 First IntElement
  * \param i2 Second IntElement
  * \return IntElement with parameters' int vals multiplied together
  */
IntElement operator*(const IntElement& i1, const IntElement& i2){
  IntElement result{i1};
  result *= i2;
  return result;
}
