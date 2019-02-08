/**
  * \file symbolicmatrix.cpp
  * \brief SymbolicSquareMatrix class
  */
#include "symbolicmatrix.h"

/**
  * \brief Default constructor for SymbolicSquareMatrix class, sets n = 0 for empty matrix.
  */
SymbolicSquareMatrix::SymbolicSquareMatrix() : SymbolicSquareMatrix{"[[x]]"}{

}

/**
  * \brief Constructor for SymbolicSquareMatrix class. Checks with isSquareMatrix that parameter is correct,
           then construcs elements using matrixIntoVector
  * \param s String with square matrix in [[i11,...,i1n]...[in2,...,inn]] format
  */
SymbolicSquareMatrix::SymbolicSquareMatrix(const std::string& str_m){

  if(!isVarSquareMatrix(str_m))
    throw std::invalid_argument{"Not square matrix adhering to predetermined form."};

  elements = varMatrixIntoVector(str_m);
  n = elements.size();
}

/**
  * \brief Copy constructor for SymbolicSquareMatrix class
  * \param m SymbolicSquareMatrix to be copied
  */
SymbolicSquareMatrix::SymbolicSquareMatrix(const SymbolicSquareMatrix& m) : n{m.n}{
  
  int i = 0;
  for(auto& rows : m.elements){
    elements.push_back(std::vector<std::unique_ptr<Element>>());
    for(auto& el : rows){
      elements[i].push_back(std::unique_ptr<Element>{el->clone()});
    }
    i++;
  }

}

/**
  * \brief Move copy constructor for SymbolicSquareMatrix class
  * \param m SymbolicSquareMatrix to be moved and copied
  */
SymbolicSquareMatrix::SymbolicSquareMatrix(SymbolicSquareMatrix&& m) : n{std::move(m.n)}, elements{std::move(m.elements)}{
  
}

/**
  * \brief Operator overload for operator = for SymbolicSquareMatrix class
  * \param m SymbolicSquareMatrix to be copied
  * \return SymbolicSquareMatrix with copied values
  */
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(const SymbolicSquareMatrix& m){

  SymbolicSquareMatrix copy{m};

  std::swap(elements, copy.elements);
  std::swap(n, copy.n);

  return *this;

}

/**
  * \brief Move copy operator for SymbolicSquareMatrix class
  * \param m SymbolicSquareMatrix to be moved and copied
  * \return SymbolicSquareMatrix with copied values
  */
SymbolicSquareMatrix& SymbolicSquareMatrix::operator=(SymbolicSquareMatrix&& m){

  if(elements == m.elements){
    return *this;
  }

  std::swap(elements, m.elements);
  std::swap(n, m.n);

  return *this;

}

/**
  * \brief Returns transpose of self
  * \return SymbolicSquareMatrix that is transpose of self
  */
SymbolicSquareMatrix SymbolicSquareMatrix::transpose() const{

  SymbolicSquareMatrix transpose{};
  transpose.elements.clear();

  for(int i = 0; i < n; i++){
    transpose.elements.push_back(std::vector<std::unique_ptr<Element>>());
    for(int j = 0; j < n; j++){
      transpose.elements[i].push_back(std::unique_ptr<Element>{(elements[j][i])->clone()});
    }
  }

  transpose.n = n;

  return transpose;
}

/**
  * \brief Checks, if two matrices are identical
  * \param m SymbolicSquareMatrix
  * \return True if matrices are identical, false if not
  */
bool SymbolicSquareMatrix::operator==(const SymbolicSquareMatrix& m) const{
  
  if(n != m.n)
    return false;

  for(int i= 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(!(toString() == m.toString()))
        return false;
    }
  }
  return true;
}

/**
  * \brief Prints toString() to output stream
  * \param os Output stream
  */
void SymbolicSquareMatrix::print(std::ostream& os) const{
  os << toString();
}

/**
  * \brief Returns matrix in predetermined string format
  * \return Matrix in predetermined string format
  */
std::string SymbolicSquareMatrix::toString() const{
  
  std::stringstream ss;
  bool first = true;

  ss << '[';

  for(auto& row : elements){
    first = true;
    ss << '[';
    for(auto& num : row){
      if(!first)
        ss << ',';
      ss << *num;
      first = false;
    }
    ss << ']';
  }

  ss << ']';

  return ss.str();

}

/**
  * \brief Goes through symbolic matrix with map, returns a concrete matrix based on mapped values. If no mapped value, throws exception.
  * \param val Valuation object, map of char elements and int elements
  * \return ConcreteSquareMatrix based on symbolic matrix
  */
ConcreteSquareMatrix SymbolicSquareMatrix::evaluate(const Valuation& val) const{

  std::vector<std::vector<std::unique_ptr<IntElement>>> concreteEls;

  for(int i = 0; i < n; i++){
    concreteEls.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < n; j++){
        
      concreteEls[i].push_back(std::unique_ptr<IntElement>{new IntElement{elements[i][j]->evaluate(val)}});
    }
  }
  return ConcreteSquareMatrix{std::move(concreteEls)};
}

/**
  * \brief Operator overload for operator <<
  * \param os Output stream
  * \param m SymbolicSquareMatrix to be printed to output stream
  * \return Output stream with contents of square matrix printed
  */
std::ostream& operator<<(std::ostream& os, const SymbolicSquareMatrix& m){
  
  m.print(os);
  return os;

}

/**
  * \brief Checks, whether parameter string is a square matrix adhering to the proper style
  * \param s String containing square matrix
  * \return True, if string is a proper square matrix, else false
  */
bool isVarSquareMatrix(const std::string& s){
  char variable = ' ';
  int num = 0;
  char delim = ' ';
  int vars = 0;
  int finalVars = -1;
  int rows = 0;
  std::stringstream ss;

  ss << s;

  // Checking for first '['
  ss >> delim;
  if(delim != '[')
    return false;

  ss >> delim;

  // Repeat until first ']'
  while(delim != ']'){

    // Checking for second '['
    if(delim != '[')
      return false;

    do{

      // Checking for char
      ss >> num;

      if(!ss.good()){
        ss.clear();
        ss >> variable;
        if(ss.eof()){
          return false;
        }
        if(!std::isalpha(variable)){
          return false;
        }
      }

      ss >> delim;
      // Checking for ',' or ']'
      if(delim != ',' && delim != ']')
        return false;

      vars++; // Counting the number of vars in a row

    } while(delim != ']'); // Repeat until first ']'

    // Rows and vars need to be equal in square matrix
    if(finalVars == -1)
      finalVars = vars;
    if(finalVars != vars)
      return false;
    vars = 0; // Resetting numbers in row

    // Making sure the string does not end with first ']'
    ss >> delim;
    if(!ss.good())
      return false;

    rows++; // Counting the number of rows in matrix
  }

  if(finalVars != rows)
    return false;
  // Checking, that ss is clear after final ']'
  std::string right;
  ss >> right;
  if(right != "")
    return false;

  return true;
}

/**
  * \brief Converts string-form matrix into vector of vectors containing smart pointers to IntElement objects
  * \param s String containing square matrix
  * \return Vector of vectors of smart pointers to IntElements
  */
std::vector<std::vector<std::unique_ptr<Element>>> varMatrixIntoVector(const std::string& s){
  char variable;
  int num = 0;
  char delim;
  int rows = 0;
  std::stringstream ss;
  std::string integer;
  std::vector<std::vector<std::unique_ptr<Element>>> els;

  ss << s;

  ss >> delim;  // Removing first '[' from stringstream
  ss >> delim;  // Removing second '[' from stringstream

  while(delim != ']'){
    els.push_back(std::vector<std::unique_ptr<Element>>());
    do{
      
      // Creating VariableElement if char, else IntElement
      ss >> num;

      if(!ss.good()){
        ss.clear();
        ss >> variable;
        if(std::isalpha(variable)){
          els[rows].push_back(std::unique_ptr<VariableElement>{new VariableElement{variable}});
        }
      }
      else{
        els[rows].push_back(std::unique_ptr<IntElement>{new IntElement{num}});
      }

      ss >> delim;
    } while(delim != ']');

    ss >> delim;  // Removing final ']' from stringstream
    rows++;
  }

  return els;
}