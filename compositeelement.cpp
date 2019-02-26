/**
  * \file compositeelement.cpp
  * \brief CompositeElement class
  */

#include "compositeelement.h"

CompositeElement::CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc) : 
oprnd1{e1.clone()}, oprnd2{e2.clone()}, op_fun{op}, op_ch{opc}{}

CompositeElement::CompositeElement(const CompositeElement& e){
    
  oprnd1 = std::unique_ptr<Element>{e.oprnd1->clone()};
  oprnd2 = std::unique_ptr<Element>{e.oprnd2->clone()};
  op_fun = e.op_fun;
  op_ch = e.op_ch;

}

CompositeElement& CompositeElement::operator=(const CompositeElement& e){

  CompositeElement copy{e};

  oprnd1 = std::move(copy.oprnd1);
  oprnd2 = std::move(copy.oprnd2);
  op_fun = std::move(copy.op_fun);
  op_ch = std::move(copy.op_ch);

  return *this;
}

Element* CompositeElement::clone() const{

  return new CompositeElement{*oprnd1, *oprnd2, op_fun, op_ch};

}

std::string CompositeElement::toString()const{

  std::stringstream ss;
  ss << '(' << oprnd1->toString() << op_ch << oprnd2->toString() << ')';
  return ss.str();

}

int CompositeElement::evaluate(const Valuation& v) const{

  return op_fun(oprnd1->evaluate(v), oprnd2->evaluate(v));

}