/**
  * \file compositeelement.h
  * \brief Header for CompositeElement class
  */
#ifndef COMPOSITEELEMENT_H
#define COMPOSITEELEMENT_H

#include <functional>
#include "element.h"

/**
  * \class CompositeElement
  * \brief Class encapsulating composites of two Element objects and arithmetic function between them
  */
class CompositeElement : public Element
{
public:
  /**
    * \brief Constructor for CompositeElement class
    * \param e1 First element object to be stored
    * \param e2 Second element object to be stored
    * \param op Function for arithmetic operation to be applied to parameters
    * \param opc Symbol for arithmetic operation
    */
  CompositeElement(const Element& e1, const Element& e2, const std::function<int(int,int)>& op, char opc);

  /**
    * \brief Copy constructor for CompositeElement class
    * \param e CompositeElement to be copied
  */
  CompositeElement(const CompositeElement& e);

  /**
    * \brief Copies the contents of param to self
    * \param e CompositeElement whose contents are copied
    * \return Self with copied contents
    */
  CompositeElement& operator=(const CompositeElement& e);

  /**
    * \brief Virtual destructor for CompositeElement class
    */
  virtual ~CompositeElement() = default;

  /**
    * \brief Creates a clone of self and returns pointer to it
    * \return Pointer to clone of self
    */
  Element* clone() const override;

  /**
    * \brief Returns contents of CompositeElement in string form
    * \return Contents of CompositeElement in string form
    */
  std::string toString()const override;

  /**
    * \brief Carries out arithmetic operation based on mapped values and returns result
    * \param v Map for char variables and int values
    * \return Int value for result of operation based on mapped values
    */
  int evaluate(const Valuation& v) const override;

private:
  std::unique_ptr<Element> oprnd1;
  std::unique_ptr<Element> oprnd2;
  std::function<int(int,int)> op_fun;
  char op_ch;

};

#endif // COMPOSITEELEMENT_H