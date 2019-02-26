/**
  * \file element.h
  * \brief Header for Element interface and TElement template class
  */
#ifndef ELEMENT_H
#define ELEMENT_H

#include <sstream>
#include <stdexcept>
#include <memory>
#include "valuation.h"

/**
  * \class Element
  * \brief Interface for IntElement and VariableElement classes
  */
class Element
{
public:
  /**
    * \brief Virtual destructor for Element class
    */
  virtual ~Element() = default;

  /**
    * \brief Abstract clone method for Element class
    * \return Pointer of copy of self
    */
  virtual Element* clone() const = 0;

  /*
    * \brief Abstract toString method for Element class
    * \return Value of IntElement in string form
    */
  virtual std::string toString() const = 0;

    /**
    * \brief Abstract evaluation method for Element class
    * \return Integer value of Element, either directly or mapped
    */
  virtual int evaluate(const Valuation& val) const = 0;

};

/**
  * \class TElement
  * \brief Template class for IntElements and VariableElements
  */
template <typename T>
class TElement : public Element{

public:
  /**
    * \brief Empty default constructor for TElement class
    */
  TElement();

  /**
    * \brief Constructor for TElement class
    * \param v Int or char value to be stored in TElement class
    */
  TElement(T v);

  /**
    * \brief Virtual destructor for TElement class
    */
  virtual ~TElement() = default;

  /**
    * \brief Getter for int or char value
    * \return Int or char value stored in val
    */
  T getVal() const{
    return val;
  };

  /**
    * \brief Setter for int or char value
    * \param v Value to be stored in val
    */
  void setVal(T v);

  /**
    * \brief Creates a clone of self and returns pointer to it
    * \return Pointer to clone of self
    */
  TElement* clone() const{
    return new TElement{val};
  };

  /**
    * \brief Makes string of TElement's val
    * \return String containing TElement's val
    */
  std::string toString() const{
    std::stringstream ss;
    ss << val;
    return ss.str();
  };

  /**
    * \brief Returns int value of element
    * \param v Map for char variables and int values
    * \return Int value of element
    */
  int evaluate(const Valuation& v) const;

  /**
    * \brief Operator overload for operator += for IntElements
    * \param i IntElement to be added to self
    * \return Self
    */
  TElement<int>& operator+=(const TElement<T>& i);

  /**
    * \brief Operator overload for operator -= for IntElements
    * \param i IntElement to be subtracted from self
    * \return Self
    */
  TElement<int>& operator-=(const TElement<T>& i);

  /**
    * \brief Operator overload for operator *= for IntElements
    * \param i IntElement for self to be multiplied by
    * \return Self
    */
  TElement<int>& operator*=(const TElement<T>& i);

private:
  T val;

};

/**
  * \brief Operator overload for operator + for IntElements
  * \param i1 IntElement to be summed
  * \param i2 IntElement to be summed
  * \return Resulting IntElement
  */
TElement<int> operator+(const TElement<int>& i1, const TElement<int>& i2);

/**
  * \brief Operator overload for operator - for IntElements
  * \param i1 IntElement to be subtracted
  * \param i2 IntElement to be subtracted
  * \return Resulting IntElement
  */
TElement<int> operator-(const TElement<int>& i1, const TElement<int>& i2);

/**
  * \brief Operator overload for operator * for IntElements
  * \param i1 IntElement to be multiplied
  * \param i2 IntElement to be multiplied
  * \return Resulting IntElement
  */
TElement<int> operator*(const TElement<int>& i1, const TElement<int>& i2);

/**
  * \brief Operator overload for operator << for Element subclasses
  * \param os Output stream
  * \param ii Element
  * \return Output stream with encapsulated value
  */
std::ostream& operator<<(std::ostream& os, const Element& i);

/**
  * \brief Operator overload for operator == for Element subclasses
  * \param e1 First Element to be compared
  * \param e2 Second Element to be compared
  * \return True if identical, false if not
  */
bool operator==(const Element& e1, const Element& e2);

using IntElement = TElement<int>;
using VariableElement = TElement<char>;

#endif // ELEMENT_H