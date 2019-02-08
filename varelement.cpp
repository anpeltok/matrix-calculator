/**
  * \file varelement.cpp
  * \brief VariableElement class
  */
#include "varelement.h"

/**
  * \brief Empty default constructor for VariableElement class
  */
VariableElement::VariableElement() : VariableElement{'x'}{
  
}

/**
  * \brief Constructor for VariableElement class
  * \param v Int varue to be stored in VariableElement class
  */
VariableElement::VariableElement(char v){

  if(v < char(65) || (v > char(90) && v < char(97)) || v > char(122)){
    throw std::invalid_argument{"Char needs to be A-Z or a-z."};
  }
  var = v;
}

/**
  * \brief Getter for int varue
  * \return Int varue stored in var
  */
char VariableElement::getVal() const{
  return var;
}

/**
  * \brief Setter for int varue
  * \param v varue to be stored in var
  */
void VariableElement::setVal(char v){
  
  if(v < char(65) || (v > char(90) && v < char(97)) || v > char(122)){
    throw std::invalid_argument{"Char needs to be A-Z or a-z."};
  }
  var = v;
}

/**
  * \brief Creates a clone of self and returns pointer to it
  * \return Pointer to clone of self
  */
Element* VariableElement::clone() const{
  
  VariableElement* ptr{new VariableElement{var}};

  return ptr;
}

/**
  * \brief Makes string of VarElement's var
  * \return String containing VarElement's var
  */
std::string VariableElement::toString() const{
  std::stringstream ss;
  ss << var;
  return ss.str();

}

/**
  * \brief Returns int value matching var or throws exception
  * \param v Map for char variables and int values
  * \return Int value matching var
  */
int VariableElement::evaluate(const Valuation& v) const{
  
  int value;

  try{
    value = v.at(var);
  }
  catch(const std::exception& e)
  {
    throw std::invalid_argument{"Variable not valid."};
  }

  return value;
}

/**
  * \brief Checks if parameter VariableElement is identical to self
  * \param i VariableElement to be compared to
  * \return True if vars in parameter and self are same, false if not
  */
bool VariableElement::operator==(const VariableElement& i) const{

  if(int(getVal()) == i.getVal())
    return true;
  else
    return false;

}