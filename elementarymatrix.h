#ifndef ELEMENTARYMATRIX_H
#define ELEMENTARYMATRIX_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "compositeelement.h"

/**
  * \class ElementarySquareMatrix
  * \brief Template class for ConcreteSquareMatrix and SymbolicSquareMatrix
  */
template <typename T>
class ElementarySquareMatrix{

public:

  /**
    * \brief Checks, whether parameter string is a square matrix adhering to the proper style
    * \param s String containing matrix
    * \return True, if string is a proper square matrix, else false
    */
  bool isSquareMatrix(const std::string& s);

  /**
    * \brief Converts string-form matrix into vector of vectors containing smart pointers to Element objects
    * \param s String containing square matrix
    * \return Vector of vectors of smart pointers to IntElements or Elements
    */
  std::vector<std::vector<std::unique_ptr<T>>> matrixIntoVector(const std::string& s) const;

  /**
    * \brief Creates size n square matrix whose values are 0 or x
    * \param n Size of square matrix
    * \return Vector of vectors of smart pointers to IntElements or Elements
    */
  std::vector<std::vector<std::unique_ptr<T>>> emptyMatrixIntoVector(const int n) const;

  /**
    * \brief Default constructor for ElementarySquareMatrix class. Defaults to 0-size matrix
    */
  ElementarySquareMatrix() : ElementarySquareMatrix{0}{};

  /**
    * \brief Constructor for ElementarySquareMatrix of size n filled with zeroes.
    * \param n Size of created ElementarySquareMatrix
    */
  ElementarySquareMatrix(const unsigned int length) : n{length}, elements{emptyMatrixIntoVector(length)}{};

  /**
    * \brief Constructor for ElementarySquareMatrix class. Checks with isSquareMatrix that parameter is correct,
             then constructs elements using matrixIntoVector
    * \param s String with square matrix in [[i11,...,i1n]...[in2,...,inn]] format
  */
  ElementarySquareMatrix(const std::string& str_m){
    
    if(!isSquareMatrix(str_m))
      throw std::invalid_argument{"Not square matrix adhering to predetermined form."};

    elements = matrixIntoVector(str_m);
    n = elements.size();
  };

  /**
    * \brief Constructor using vector for ElementarySquareMatrix class. If SquareMatrix doesn't adhere to proper form, throws exception.
    * \param v Vector of vectors of IntElements or Elements, contains a SquareMatrix 
    */
  ElementarySquareMatrix(const std::vector<std::vector<std::unique_ptr<T>>> v){

    for(int i = 0; i < v.size(); i++){
      elements.push_back(std::vector<std::unique_ptr<T>>());
      for(int j = 0; j < v[i].size(); j++){
        elements[i].push_back(std::unique_ptr<T>{v[i][j]->clone()});
      }
    }

    n = elements.size();
    
    if(!isSquareMatrix(toString())){
      throw std::invalid_argument{"Not square matrix adhering to predetermined form."};
    }
  }

  /**
    * \brief Copy constructor for ElementarySquareMatrix class
    * \param m ElementarySquareMatrix to be copied
    */
  ElementarySquareMatrix(const ElementarySquareMatrix<T>& m) : n{m.n}{
    
    int i = 0;

    for(auto& rows : m.elements){
      elements.push_back(std::vector<std::unique_ptr<T>>());
      for(auto& el : rows){
        elements[i].push_back(std::unique_ptr<T>{dynamic_cast<T*>(el->clone())});
      }
      i++;
    }
  };

  /**
    * \brief Move copy constructor for ElementarySquareMatrix class
    * \param m ElementarySquareMatrix to be moved and copied
    */
  ElementarySquareMatrix(ElementarySquareMatrix<T>&& m) : n{std::move(m.n)}, elements{std::move(m.elements)}{};

  /**
    * \brief Virtual destructor for ElementarySquareMatrix class
    */
  virtual ~ElementarySquareMatrix() = default;

  /**
    * \brief Operator overload for operator = for ElementarySquareMatrix class
    * \param m ElementarySquareMatrix to be copied
    * \return ElementarySquareMatrix with copied values
    */
  ElementarySquareMatrix<T>& operator=(const ElementarySquareMatrix<T>& m){
    
    ElementarySquareMatrix<T> copy{m};

    std::swap(elements, copy.elements);
    std::swap(n, copy.n);

    return *this;
  };

  /**
    * \brief Move copy operator for ElementarySquareMatrix class
    * \param m ElementarySquareMatrix to be moved and copied
    * \return ElementarySquareMatrix with copied values
    */
  ElementarySquareMatrix<T>& operator=(ElementarySquareMatrix<T>&& m){
    
    if(elements == m.elements){
      return *this;
    }

    std::swap(elements, m.elements);
    std::swap(n, m.n);

    return *this;
  };

  /**
    * \brief Returns transpose of self
    * \return ElementarySquareMatrix that is transpose of self
    */
  ElementarySquareMatrix<T> transpose() const{
    
    ElementarySquareMatrix<T> transpose{};

    for(int i = 0; i < n; i++){
      transpose.elements.push_back(std::vector<std::unique_ptr<T>>());
      for(int j = 0; j < n; j++){
        transpose.elements[i].push_back(std::unique_ptr<T>{dynamic_cast<T*>(elements[j][i]->clone())});
      }
    }

    transpose.n = n;

    return transpose;
  };

  /**
    * \brief Operator overload for operator += for ConcreteSquareMatrix class
    * \param m Reference to ConcreteSquareMatrix object to be added to self
    * \return Self
    */
  ElementarySquareMatrix<IntElement>& operator+=(const ElementarySquareMatrix<IntElement>& m);

  /**
    * \brief Operator overload for operator -= for ConcreteSquareMatrix class
    * \param m Reference to ConcreteSquareMatrix object to be subtracted from self
    * \return Self
    */
  ElementarySquareMatrix<IntElement>& operator-=(const ElementarySquareMatrix<IntElement>& m);

  /**
    * \brief Operator overload for operator *= for ConcreteSquareMatrix class
    * \param m Reference to ConcreteSquareMatrix object for self to be multiplied by
    * \return Self
    */
  ElementarySquareMatrix<IntElement>& operator*=(const ElementarySquareMatrix<IntElement>& m);

  /**
    * \brief Calculates sum of two ElementarySquareMatrix. 
             For ConcreteSquareMatrix calculates sum.
             For SymbolicSquareMatrix makes CompositeElements.
    * \param m ElemenetarySquareMatrix to be added to copy of self
    * \return ElemenetarySquareMatrix with param added to copy of self
    */
  ElementarySquareMatrix<T> operator+(const ElementarySquareMatrix<T>& m) const;

  /**
    * \brief Detracts param ElementarySquareMatrix from copy of self.
             For ConcreteSquareMatrix calculates result.
             For SymbolicSquareMatrix makes CompositeElements.
    * \param m ElemenetarySquareMatrix to be detracted from copy of self
    * \return ElemenetarySquareMatrix with param detracted from copy of self
    */
  ElementarySquareMatrix<T> operator-(const ElementarySquareMatrix<T>& m) const;
  
  /**
    * \brief Multiplies self by param ElementarySquareMatrix.
             For ConcreteSquareMatrix calculates result.
             For SymbolicSquareMatrix makes CompositeElements.
    * \param m ElemenetarySquareMatrix to be multiplied with copy of self
    * \return ElemenetarySquareMatrix with param multiplied by copy of self
    */
  ElementarySquareMatrix<T> operator*(const ElementarySquareMatrix<T>& m) const;

  /**
    * \brief Checks, if param matrix is identical to self
    * \param m ElementarySquareMatrix
    * \return True if matrices are identical, false if not
    */
  bool operator==(const ElementarySquareMatrix<T>& m) const{
    
    if(n != m.n)
      return false;

    if(!(toString() == m.toString()))
      return false;
    else
      return true;
  };

  /**
    * \brief Prints toString() to output stream
    * \param os Output stream
    */
  void print(std::ostream& os) const{
    
    os << toString();
  };

  /**
    * \brief Returns matrix in predetermined string format
    * \return Matrix in predetermined string format
    */
  std::string toString() const{

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
  };

  /**
    * \brief Returns int values mapped to SymbolicSquareMatrix' char values
    * \param Map containing int values corresponding to char values
    * \return ConcreteSquareMatrix of mapped values corresponding to SymbolicSquareMatrix' char values
              If no mapped value, throws exception
    */
  ElementarySquareMatrix<IntElement> evaluate(const Valuation& val) const;

  /**
  * \brief Checks, whether two operands are empty and/or same size. If both are empty, throws exception. 
           If one is empty, creates empty matrix the same size as the other, but filled with zeroes. 
           If non-empty matrices are not the same size, throws exception.
  * \param m ElementarySquareMatrix to be compared to self
  */
  void checkOperands(ElementarySquareMatrix<T>& m) const{
    
    // If matrices are different size, throw exception
    if(n != m.n){
      throw std::invalid_argument{"Square matrices are not same size."};
    }
  };
  
private:
  unsigned int n;
  std::vector<std::vector<std::unique_ptr<T>>> elements;

  friend class ElementarySquareMatrix<Element>;

};


/**
  * \brief Operator overload for operator <<
  * \param os Output stream
  * \param m ElementarySquareMatrix to be printed to output stream
  * \return Output stream with contents of square matrix printed
  */
template<typename T>
std::ostream& operator<<(std::ostream& os, const ElementarySquareMatrix<T>& m){

  m.print(os);
  return os;
}

using ConcreteSquareMatrix = ElementarySquareMatrix<IntElement>;
using SymbolicSquareMatrix = ElementarySquareMatrix<Element>;


#endif // ELEMENTARYMATRIX_H