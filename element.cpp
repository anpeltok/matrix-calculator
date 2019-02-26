/**
  * \file element.cpp
  * \brief Specializations for TElement class methods and functions
  */

#include "element.h"

template<>
TElement<int>::TElement(int v) : val{v}{}

template<>
TElement<char>::TElement(char v){
  if(v < char(65) || (v > char(90) && v < char(97)) || v > char(122)){
    throw std::invalid_argument{"Char needs to be A-Z or a-z."};
  }
  val = v;
}

template<>
TElement<int>::TElement() : TElement<int>{0}{}

template<>
TElement<char>::TElement() : TElement<char>{'x'}{}

template<>
void TElement<int>::setVal(int v){
  val = v;
}

template<>
void TElement<char>::setVal(char v){
  if(v < char(65) || (v > char(90) && v < char(97)) || v > char(122)){
    throw std::invalid_argument{"Char needs to be A-Z or a-z."};
  }
  val = v;
}

template<>
int TElement<int>::evaluate(const Valuation& v) const{
  return val;
}

template<>
int TElement<char>::evaluate(const Valuation& v) const{
  return v.at(val);
}

template<>
TElement<int>& TElement<int>::operator+=(const TElement<int>& i){
  val = val + i.val;
  return *this;
}

template<>
TElement<int>& TElement<int>::operator-=(const TElement<int>& i){
  val = val - i.val;
  return *this;
}

template<>
TElement<int>& TElement<int>::operator*=(const TElement<int>& i){
  val = val * i.val;
  return *this;
}

TElement<int> operator+(const TElement<int>& i1, const TElement<int>& i2){
  IntElement result{i1};
  result += i2;
  return result;
}

TElement<int> operator-(const TElement<int>& i1, const TElement<int>& i2){
  IntElement result{i1};
  result -= i2;
  return result;
}

TElement<int> operator*(const TElement<int>& i1, const TElement<int>& i2){
  IntElement result{i1};
  result *= i2;
  return result;
}

std::ostream& operator<<(std::ostream& os, const Element& i){
  return os << i.toString();
}

bool operator==(const Element& e1, const Element& e2){
  if(e1.toString() == e2.toString())
    return true;
  else
    return false;
}