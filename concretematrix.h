#ifndef CONCRETEMATRIX_H
#define CONCRETEMATRIX_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "intelement.h"
#include "varelement.h"
#include "element.h"

class ConcreteSquareMatrix
{

public:
  ConcreteSquareMatrix();
  ConcreteSquareMatrix(const unsigned int n);
  ConcreteSquareMatrix(const std::string& str_m);
  ConcreteSquareMatrix(std::vector<std::vector<std::unique_ptr<IntElement>>> v);
  ConcreteSquareMatrix(const ConcreteSquareMatrix& m);
  ConcreteSquareMatrix(ConcreteSquareMatrix&& m);
  virtual ~ConcreteSquareMatrix() = default;
  ConcreteSquareMatrix& operator=(const ConcreteSquareMatrix& m);
  ConcreteSquareMatrix& operator=(ConcreteSquareMatrix&& m);
  ConcreteSquareMatrix transpose() const;
  ConcreteSquareMatrix& operator+=(const ConcreteSquareMatrix& m);
  ConcreteSquareMatrix& operator-=(const ConcreteSquareMatrix& m);
  ConcreteSquareMatrix& operator*=(const ConcreteSquareMatrix& m);
  bool operator==(const ConcreteSquareMatrix& m) const;
  void print(std::ostream& os) const;
  std::string toString() const;
  void checkOperands(ConcreteSquareMatrix& m);

private:
  unsigned int n;
  std::vector<std::vector<std::unique_ptr<IntElement>>> elements;

};

ConcreteSquareMatrix operator+(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
ConcreteSquareMatrix operator-(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
ConcreteSquareMatrix operator*(const ConcreteSquareMatrix& m1, const ConcreteSquareMatrix& m2);
std::ostream& operator<<(std::ostream& os, const ConcreteSquareMatrix& m);
bool isSquareMatrix(const std::string& s);
std::vector<std::vector<std::unique_ptr<IntElement>>> matrixIntoVector(const std::string& s);
std::vector<std::vector<std::unique_ptr<IntElement>>> emptyMatrixIntoVector(int lenght);


#endif // CONCRETEMATRIX_H