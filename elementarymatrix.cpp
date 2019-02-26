/**
  * \file elementarymatrix.cpp
  * \brief Specializations for ElementaryMatrix class methods and functions
  */

#include "elementarymatrix.h"

template<>
bool ElementarySquareMatrix<IntElement>::isSquareMatrix(const std::string& s){
  
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

template<>
bool ElementarySquareMatrix<Element>::isSquareMatrix(const std::string& s){

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

template<>
std::vector<std::vector<std::unique_ptr<IntElement>>> ElementarySquareMatrix<IntElement>::matrixIntoVector(const std::string& s) const{

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

template<>
std::vector<std::vector<std::unique_ptr<Element>>> ElementarySquareMatrix<Element>::matrixIntoVector(const std::string& s) const{

  char variable;
  int num = 0;
  char delim;
  int rows = 0;
  std::stringstream ss;
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

template<>
std::vector<std::vector<std::unique_ptr<IntElement>>> ElementarySquareMatrix<IntElement>::emptyMatrixIntoVector(const int n) const{

  std::vector<std::vector<std::unique_ptr<IntElement>>> els;

  for(int i = 0; i < n; i++){
    els.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < n; j++){
    els[i].push_back(std::unique_ptr<IntElement>{new IntElement{0}});
    }
  }
  return els;
}

template<>
std::vector<std::vector<std::unique_ptr<Element>>> ElementarySquareMatrix<Element>::emptyMatrixIntoVector(const int n) const{

  std::vector<std::vector<std::unique_ptr<Element>>> els;

  for(int i = 0; i < n; i++){
    els.push_back(std::vector<std::unique_ptr<Element>>());
    for(int j = 0; j < n; j++){
    els[i].push_back(std::unique_ptr<Element>{new VariableElement{'x'}});
    }
  }
  return els;
}

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator+=(const ElementarySquareMatrix<IntElement>& m){
  
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

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator-=(const ElementarySquareMatrix<IntElement>& m){
  
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

template<>
ElementarySquareMatrix<IntElement>& ElementarySquareMatrix<IntElement>::operator*=(const ElementarySquareMatrix<IntElement>& m){
  
  ConcreteSquareMatrix transpose = m;
  checkOperands(transpose);

  transpose = transpose.transpose();
  
  // Initializing result as square matrix of correct size holding zeroes
  ConcreteSquareMatrix result{};
  result.elements = emptyMatrixIntoVector(n);
  result.n = n;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n; k++){
        *result.elements[i][j] += *elements[i][k] * *transpose.elements[j][k];
      }
    }
  }

  std::swap(elements, result.elements);

  return *this;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator+(const ElementarySquareMatrix<IntElement>& m) const{
  ConcreteSquareMatrix result{*this};
  result += m;

  return result;
}

template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator+(const ElementarySquareMatrix<Element>& m) const{

  SymbolicSquareMatrix copy = m;
  SymbolicSquareMatrix result{m};

  checkOperands(copy);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      CompositeElement el{*elements[i][j], *copy.elements[i][j], std::plus<int>{}, '+'};
      result.elements[i][j] = std::unique_ptr<Element>{el.clone()};
    }
  }

  return result;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator-(const ElementarySquareMatrix<IntElement>& m) const{
  ConcreteSquareMatrix result{*this};
  result -= m;

  return result;
}

template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator-(const ElementarySquareMatrix<Element>& m) const{
  
  SymbolicSquareMatrix copy = m;
  SymbolicSquareMatrix result{m};

  checkOperands(copy);

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      CompositeElement el{*elements[i][j], *copy.elements[i][j], std::minus<int>{}, '-'};
      result.elements[i][j] = std::unique_ptr<Element>{el.clone()};
    }
  }

  return result;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<IntElement>::operator*(const ElementarySquareMatrix<IntElement>& m) const{

  ConcreteSquareMatrix temp{*this};
  ConcreteSquareMatrix transpose = m;
  checkOperands(transpose);

  transpose = transpose.transpose();
  
  // Initializing result as square matrix of correct size holding zeroes
  ConcreteSquareMatrix result{};
  result.elements = emptyMatrixIntoVector(n);
  result.n = n;

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      for(int k = 0; k < n; k++){
        *result.elements[i][j] += *temp.elements[i][k] * *transpose.elements[j][k];
      }
    }
  }

  return result;
}

template<>
ElementarySquareMatrix<Element> ElementarySquareMatrix<Element>::operator*(const ElementarySquareMatrix<Element>& m) const{

  SymbolicSquareMatrix transpose = m.transpose();
  std::vector<std::unique_ptr<Element>> sums;
  checkOperands(transpose);
  int finalEls = 0;
  
  SymbolicSquareMatrix result{m};

  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++, finalEls++){
      for(int k = 0; k < n; k++){
        sums.push_back(std::unique_ptr<Element>{new CompositeElement{*elements[i][k], *transpose.elements[j][k], std::multiplies<int>{}, '*'}});
        if(k == 1){
          result.elements[i][j] = std::unique_ptr<Element>{new CompositeElement{*sums[0], *sums[1], std::plus<int>{}, '+'}};
        }
        if(k > 1){
          result.elements[i][j] = std::unique_ptr<Element>{new CompositeElement{*result.elements[i][j], *sums[k], std::plus<int>{}, '+'}};
        }
      }
      sums.clear();
    }
  }

  return result;
}

template<>
ElementarySquareMatrix<IntElement> ElementarySquareMatrix<Element>::evaluate(const Valuation& val) const{
  
  std::vector<std::vector<std::unique_ptr<IntElement>>> concreteEls;

  for(int i = 0; i < n; i++){
    concreteEls.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < n; j++){
      concreteEls[i].push_back(std::unique_ptr<IntElement>{new IntElement{elements[i][j]->evaluate(val)}});
    }
  }

  ConcreteSquareMatrix result{std::move(concreteEls)};

  return result;
};