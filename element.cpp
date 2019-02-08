#include "element.h"

/**
  * \brief Operator overload for operator << for VariableElements
  * \param os Output stream
  * \param ii VariableElement
  * \return Output stream with encapsulated int varue
  */
std::ostream& operator<<(std::ostream& os, const Element& i){

  return os << i.toString();

}
