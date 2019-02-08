#ifndef SYMBOLICMATRIX_H
#define SYMBOLICMATRIX_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "element.h"
#include "varelement.h"
#include "intelement.h"
#include "valuation.h"
#include "concretematrix.h"


class SymbolicSquareMatrix
{

public:
  SymbolicSquareMatrix();
  SymbolicSquareMatrix(const std::string& str_m);
  SymbolicSquareMatrix(const SymbolicSquareMatrix& m);
  SymbolicSquareMatrix(SymbolicSquareMatrix&& m);
  virtual ~SymbolicSquareMatrix() = default;
  SymbolicSquareMatrix& operator=(const SymbolicSquareMatrix& m);
  SymbolicSquareMatrix& operator=(SymbolicSquareMatrix&& m);
  SymbolicSquareMatrix transpose() const;
  bool operator==(const SymbolicSquareMatrix& m) const;
  void print(std::ostream& os) const;
  std::string toString() const;
  ConcreteSquareMatrix evaluate(const Valuation& val) const;

private:
  unsigned int n;
  std::vector<std::vector<std::unique_ptr<Element>>> elements;

};

std::ostream& operator<<(std::ostream&, const SymbolicSquareMatrix&);
bool isVarSquareMatrix(const std::string& s);
std::vector<std::vector<std::unique_ptr<Element>>> varMatrixIntoVector(const std::string& s);

#endif // SYMBOLICMATRIX_H