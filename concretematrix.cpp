/**
  * \file concretematrix.cpp
  * \brief ConcreteSquareMatrix class
  */
#include "concretematrix.h"

/**
  * \brief Default constructor for ConcreteSquareMatrix class, sets n = 0 for empty matrix.
  */
ConcreteSquareMatrix::ConcreteSquareMatrix() : ConcreteSquareMatrix{0}{
}

/**
  * \brief Constructor for ConcreteSquareMatrix of size n filled with zeroes.
  * \param n Size of created ConcreteSquareMatrix
  */
ConcreteSquareMatrix::ConcreteSquareMatrix(const unsigned int length){
  elements = emptyMatrixIntoVector(length);
  n = length;
}

/**
  * \brief Constructor for ConcreteSquareMatrix class. Checks with isSquareMatrix that parameter is correct,
           then constructs elements using matrixIntoVector
  * \param s String with square matrix in [[i11,...,i1n]...[in2,...,inn]] format
  */
ConcreteSquareMatrix::ConcreteSquareMatrix(const std::string& str_m){

  if(!isSquareMatrix(str_m))
    throw std::invalid_argument{"Not square matrix adhering to predetermined form."};

  elements = matrixIntoVector(str_m);
  n = elements.size();
}

/**
  * \brief Constructor for ConcreteSquareMatrix class. If SquareMatrix doesn't adhere to proper form, throws exception.
  * \param v Vector of vectors of IntElements, contains a SquareMatrix 
  */
ConcreteSquareMatrix::ConcreteSquareMatrix(std::vector<std::vector<std::unique_ptr<IntElement>>> v){
  elements = std::move(v);
  n = elements.size();
  if(!isSquareMatrix(toString())){
    throw std::invalid_argument{"Not square matrix adhering to predetermined form."};
  }
}

/**
  * \brief Copy constructor for ConcreteSquareMatrix class
  * \param m ConcreteSquareMatrix to be copied
  */
ConcreteSquareMatrix::ConcreteSquareMatrix(const ConcreteSquareMatrix& m) : n{m.n}{
  
  int i = 0;

  for(auto& rows : m.elements){
    elements.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(auto& el : rows){
      elements[i].push_back(std::unique_ptr<IntElement>{dynamic_cast<IntElement*>(el->clone())});
    }
    i++;
  }

}

/**
  * \brief Move copy constructor for ConcreteSquareMatrix class
  * \param m ConcreteSquareMatrix to be moved and copied
  */
ConcreteSquareMatrix::ConcreteSquareMatrix(ConcreteSquareMatrix&& m) : n{std::move(m.n)}, elements{std::move(m.elements)}{
  
}

/**
  * \brief Operator overload for operator = for ConcreteSquareMatrix class
  * \param m ConcreteSquareMatrix to be copied
  * \return ConcreteSquareMatrix with copied values
  */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(const ConcreteSquareMatrix& m){

  ConcreteSquareMatrix copy{m};

  std::swap(elements, copy.elements);
  std::swap(n, copy.n);

  return *this;

}

/**
  * \brief Move copy operator for ConcreteSquareMatrix class
  * \param m ConcreteSquareMatrix to be moved and copied
  * \return ConcreteSquareMatrix with copied values
  */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator=(ConcreteSquareMatrix&& m){

  if(elements == m.elements){
    return *this;
  }

  std::swap(elements, m.elements);
  std::swap(n, m.n);

  return *this;

}

/**
  * \brief Returns transpose of self
  * \return ConcreteSquareMatrix that is transpose of self
  */
ConcreteSquareMatrix ConcreteSquareMatrix::transpose() const{

  ConcreteSquareMatrix transpose{};

  for(int i = 0; i < n; i++){
    transpose.elements.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < n; j++){
      transpose.elements[i].push_back(std::unique_ptr<IntElement>{dynamic_cast<IntElement*>(elements[j][i]->clone())});
    }
  }

  transpose.n = n;

  return transpose;
}

/**
  * \brief Operator overload for operator +=
  * \param m Reference to ConcreteSquareMatrix object to be added to self
  * \return Self
  */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator+=(const ConcreteSquareMatrix& m){

  ConcreteSquareMatrix copy = m;

  checkOperands(copy);

  int rows = 0;
  int nums = 0;

  for(auto& row : elements){
    for(auto& num : row){
      *num = *num + *copy.elements[rows][nums];
      nums++;
    }
    nums = 0;
    rows++;
  }

  return *this;
}

/**
  * \brief Operator overload for operator -=
  * \param m Reference to ConcreteSquareMatrix object to be subtracted from self
  * \return Self
  */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator-=(const ConcreteSquareMatrix& m){

  ConcreteSquareMatrix copy = m;

  checkOperands(copy);

  int rows = 0;
  int nums = 0;

  for(auto& row : elements){
    for(auto& num : row){
      *num = *num - *copy.elements[rows][nums];
      nums++;
    }
    nums = 0;
    rows++;
  }

  return *this;
}

/**
  * \brief Operator overload for operator *=
  * \param m Reference to ConcreteSquareMatrix object for self to be multiplied by
  * \return Self
  */
ConcreteSquareMatrix& ConcreteSquareMatrix::operator*=(const ConcreteSquareMatrix& m){

  ConcreteSquareMatrix transpose = m;
  checkOperands(transpose);

  transpose = transpose.transpose();
  
  // Initializing result as square matrix of correct size holding zeroes
  ConcreteSquareMatrix result{};
  result.elements = emptyMatrixIntoVector(n);
  result.n = n;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0, l = 0; l < n; k++, l++){
        *result.elements[i][j] += *elements[i][k] * *transpose.elements[j][l];
      }
    }
  }

  std::swap(elements, result.elements);

  return *this;
}

/**
  * \brief Checks, if two matrices are identical
  * \param m ConcreteSquareMatrix
  * \return True if matrices are identical, false if not
  */
bool ConcreteSquareMatrix::operator==(const ConcreteSquareMatrix& m) const{
  
  if(n != m.n)
    return false;

  for(int i= 0; i < n; i++){
    for(int j = 0; j < n; j++){
      if(!(*elements[i][j] == *m.elements[i][j]))
        return false;
    }
  }
  return true;
}

/**
  * \brief Prints toString() to output stream
  * \param os Output stream
  */
void ConcreteSquareMatrix::print(std::ostream& os) const{
  os << toString();
}

/**
  * \brief Returns matrix in predetermined string format
  * \return Matrix in predetermined string format
  */
std::string ConcreteSquareMatrix::toString() const{
  
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
  * \brief Checks, whether two operands are empty and/or same size. If both are empty, throws exception. 
           If one is empty, creates empty matrix the same size as the other, but filled with zeroes. 
           If non-empty matrices are not the same size, throws exception.
  * \param m ConcreteSquareMatrix to be compared to self
  */
void ConcreteSquareMatrix::checkOperands(ConcreteSquareMatrix& m){

  // If both matrices are empty, throw exception
  if(n == 0 && m.n == 0){
    throw std::invalid_argument{"Square matrices are empty"};
  }

  // If one of the matrices is empty, create a matrix with only zeroes with same length as other operand
  if(n == 0){
    elements = emptyMatrixIntoVector(m.n);
    n = m.n;
  }
  if(m.n == 0){
    m.elements = emptyMatrixIntoVector(n);
    m.n = n;
  }

  // If matrices are different size, throw exception
  if(n != m.n){
    throw std::invalid_argument{"Square matrices are not same size."};
  }

}  

/**
  * \brief Operator overload for operator +
  * \param m1 Reference to first ConcreteSquareMatrix
  * \param m2 Reference to second ConcreteSquareMatrix
  * \return Matrix with parameter matrices added together
  */
ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){

  ConcreteSquareMatrix result = m1;
  result += m2;

  return result;
}

/**
  * \brief Operator overload for operator -
  * \param m1 Reference to first ConcreteSquareMatrix
  * \param m2 Reference to second ConcreteSquareMatrix
  * \return Matrix with second parameter matrix detracted from first
  */
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){

  ConcreteSquareMatrix result{m1};
  result -= m2;

  return result;
}

/**
  * \brief Operator overload for operator *
  * \param m1 Reference to first ConcreteSquareMatrix
  * \param m2 Reference to second ConcreteSquareMatrix
  * \return Matrix with parameter matrices multiplied together
  */
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2){
  
  ConcreteSquareMatrix result{m1};
  result *= m2;

  return result;
}

/**
  * \brief Operator overload for operator <<
  * \param os Output stream
  * \param m ConcreteSquareMatrix to be printed to output stream
  * \return Output stream with contents of square matrix printed
  */
std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m){
  
  m.print(os);
  return os;

}

/**
  * \brief Checks, whether parameter string is a square matrix adhering to the proper style
  * \param s String containing square matrix
  * \return True, if string is a proper square matrix, else false
  */
bool isSquareMatrix(const std::string& s){
  int num;
  char delim;
  int nums = 0;
  int finalNums = -1;
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

      // Checking for integer
      ss >> num;

      if(!ss.good())
        return false;

      // Checking for ',' or ']'
      ss >> delim;
      if(delim != ',' && delim != ']')
        return false;

      nums++; // Counting the number of nums in a row

    } while(delim != ']'); // Repeat until first ']'

    // Rows and nums need to be equal in square matrix
    if(finalNums == -1)
      finalNums = nums;
    if(finalNums != nums)
      return false;

    nums = 0; // Resetting numbers in row

    // Making sure the string does not end with first ']'
    ss >> delim;
    if(!ss.good())
      return false;

    rows++; // Counting the number of rows in matrix
  }

  if(finalNums != rows)
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
std::vector<std::vector<std::unique_ptr<IntElement>>> matrixIntoVector(const std::string& s){
  int num;
  char delim;
  int rows = 0;
  int nums = 0;
  std::stringstream ss;
  std::vector<std::vector<std::unique_ptr<IntElement>>> els;

  ss << s;

  ss >> delim;  // Removing first '[' from stringstream
  ss >> delim;  // Removing second '[' from stringstream

  while(delim != ']'){
    els.push_back(std::vector<std::unique_ptr<IntElement>>());
    do{
      ss >> num;
      els[rows].push_back(std::unique_ptr<IntElement>{new IntElement{num}});
      ss >> delim;  // Removing ',' or ']' from stringstream
      nums++;
    } while(delim != ']');

    ss >> delim;  // Removing final ']' from stringstream
    rows++;
  }

  return els;
}

/**
  * \brief Creates size n square matrix whose values are all 0
  * \param n Size of square matrix
  * \return Vector of vectors of smart pointers to IntElements
  */
std::vector<std::vector<std::unique_ptr<IntElement>>> emptyMatrixIntoVector(int n){

  std::vector<std::vector<std::unique_ptr<IntElement>>> els;

  for(int i = 0; i < n; i++){
    els.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < n; j++){
    els[i].push_back(std::unique_ptr<IntElement>{new IntElement{0}});
    }
  }
  return els;
}