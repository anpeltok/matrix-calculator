/**
  * \file squarematrix.h
  * \brief Header for SquareMatrix class
  */

#ifndef SQUAREMATRIX_H
#define SQUAREMATRIX_H

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "intelement.h"

/**
  * \class SquareMatrix
  * \brief Class for nxn square matrices
  */
class SquareMatrix
{

public:
  SquareMatrix();
  SquareMatrix(const std::string& s);
  SquareMatrix(const SquareMatrix& m);
  SquareMatrix(SquareMatrix&& m);
  virtual ~SquareMatrix() = default;
  SquareMatrix& operator=(const SquareMatrix& m);
  SquareMatrix& operator=(SquareMatrix&& m);
  SquareMatrix transpose() const;
  SquareMatrix& operator+=(const SquareMatrix& m);
  SquareMatrix& operator-=(const SquareMatrix& m);
  SquareMatrix& operator*=(const SquareMatrix& m);
  bool operator==(const SquareMatrix& m) const;
  void print(std::ostream& os) const;
  std::string toString() const;
  void checkOperands(SquareMatrix& m);

private:
  int n;
  std::vector<std::vector<std::unique_ptr<IntElement>>> elements;

};

SquareMatrix operator+(const SquareMatrix& m1, const SquareMatrix& m2);
SquareMatrix operator-(const SquareMatrix& m1, const SquareMatrix& m2);
SquareMatrix operator*(const SquareMatrix& m1, const SquareMatrix& m2);
std::ostream& operator<<(std::ostream& os, const SquareMatrix& m);
bool isSquareMatrix(const std::string& in);
std::vector<std::vector<std::unique_ptr<IntElement>>> matrixIntoVector(const std::string& s);
std::vector<std::vector<std::unique_ptr<IntElement>>> emptyMatrixIntoVector(int n);

#endif // SQUAREMATRIX_H