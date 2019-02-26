/**
  * \file elementarymatrix_tests.cpp
  * \brief Catch tests for ElementarySquareMatrix template class
  */
#include "catch.hpp"
#include "elementarymatrix.h"

/**
  * \brief Tests for ConcreteSquareMatrix constructors
  */
TEST_CASE("ConcreteSquareMatrix constructor tests", "[concretematrix]"){

  CHECK_NOTHROW(ConcreteSquareMatrix{});
  CHECK_NOTHROW(ConcreteSquareMatrix{"[[1,2][3,4]]"});
  CHECK_NOTHROW(ConcreteSquareMatrix("[[1,2,3][4,5,6][7,8,9]]"));
  CHECK_NOTHROW(ConcreteSquareMatrix("[[1]]"));

  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4][5,6]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2,3][4,5]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[a]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1]]abc"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"["});
  CHECK_THROWS(ConcreteSquareMatrix{"[["});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2]["});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,,2][3,4]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1w2][3,4]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2]3,4]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"1,2][3,4]]"});

  CHECK_NOTHROW(ConcreteSquareMatrix{15});

  std::vector<std::vector<std::unique_ptr<IntElement>>> v;
  for(int i = 0; i < 2; i++){
    v.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < 2; j++){
      v[i].push_back(std::unique_ptr<IntElement>{new IntElement{i}});
    }
  }

  std::vector<std::vector<std::unique_ptr<IntElement>>> v2;
  for(int i = 0; i < 3; i++){
    v2.push_back(std::vector<std::unique_ptr<IntElement>>());
    for(int j = 0; j < 2; j++){
      v2[i].push_back(std::unique_ptr<IntElement>{new IntElement{i}});
    }
  }

  CHECK_NOTHROW(ConcreteSquareMatrix{std::move(v)});
  CHECK_THROWS(ConcreteSquareMatrix{std::move(v2)});

}

/**
  * \brief Tests for ConcreteSquareMatrix copy and move constructors
  */
TEST_CASE("ConcreteSquareMatrix copy and move constructor tests", "[concretematrix]"){

  ConcreteSquareMatrix zero{2};
  ConcreteSquareMatrix copyOne{zero};

  // Copying zero to copyOne
  CHECK(copyOne.toString() == zero.toString());

  // Moving zero to copyTwo
  ConcreteSquareMatrix copyTwo{std::move(zero)};
  CHECK(copyTwo.toString() == copyOne.toString());

  // Checking zero is empty after move
  CHECK(zero.toString() == "[]");
}

/**
  * \brief Tests for ConcreteSquareMatrix copy and move operator overloads
  */
TEST_CASE("ConcreteSquareMatrix copy and move operator overload tests", "[concretematrix]"){
  
  ConcreteSquareMatrix zero{};
  ConcreteSquareMatrix one{"[[1,2][3,4]]"};
  ConcreteSquareMatrix two{};

  // Copying one to zero
  zero = one;
  CHECK(zero.toString() == one.toString());

  // Moving zero to two
  two = std::move(zero);
  CHECK(two.toString() == one.toString());

  // Checking zero is empty after move
  CHECK(zero.toString() == "[]");

  two = std::move(two);
  CHECK(two.toString() == two.toString());
}

/**
  * \brief Tests for ConcreteSquareMatrix transpose method
  */
TEST_CASE("ConcreteSquareMatrix transpose tests", "[concretematrix]"){

  ConcreteSquareMatrix one{"[[1,2][3,4]]"};
  ConcreteSquareMatrix transpose{};

  transpose = one.transpose();

  CHECK(transpose.toString() == "[[1,3][2,4]]");
}

/**
  * \brief Tests for ConcreteSquareMatrix arithmetic operator overloads
  */
TEST_CASE("ConcreteSquareMatrix arithmetic operator overload tests", "[concretematrix]"){

  // Testing for incorrect inputs
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]]"} + ConcreteSquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]]"} - ConcreteSquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});
  CHECK_THROWS(ConcreteSquareMatrix{"[[1,2][3,4]]"} * ConcreteSquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});

  ConcreteSquareMatrix result{};

  ConcreteSquareMatrix one{"[[1,2][3,4]]"};
  ConcreteSquareMatrix two{"[[4,3][2,1]]"};

  result = one + two;
  CHECK(result.toString() == "[[5,5][5,5]]");

  result = one - two;
  CHECK(result.toString() == "[[-3,-1][1,3]]");

  result = one * two;
  CHECK(result.toString() == "[[8,5][20,13]]");

  one += two;
  CHECK(one.toString() == "[[5,5][5,5]]");

  one -= two;
  CHECK(one.toString() == "[[1,2][3,4]]");

  one *= two;
  CHECK(one.toString() == "[[8,5][20,13]]");

  ConcreteSquareMatrix threeOne{"[[1,2,3][4,5,6][7,8,9]]"};
  ConcreteSquareMatrix threeTwo{"[[9,8,7][6,5,4][3,2,1]]"};
  
  threeOne *= threeTwo;

  CHECK(threeOne.toString() == "[[30,24,18][84,69,54][138,114,90]]");
}

/**
  * \brief Tests for ConcreteSquareMatrix comparison operator overload
  */
TEST_CASE("ConcreteSquareMatrix comparison operator overload tests", "[concretematrix]"){
  
  ConcreteSquareMatrix empty{};
  ConcreteSquareMatrix one{"[[1,2][3,4]]"};
  ConcreteSquareMatrix two("[[4,3][2,1]]");

  CHECK(empty == empty);
  CHECK(one == one);
  CHECK_FALSE(empty == one);
  CHECK_FALSE(one == two);
}

/**
  * \brief Tests for ConcreteSquareMatrix print and toString methods and operator overload
  */
TEST_CASE("ConcreteSquareMatrix print, toString and operator<< overload tests", "[concretematrix]"){
  
  ConcreteSquareMatrix one{"[[1,2][3,4]]"};

  CHECK(one.toString() == "[[1,2][3,4]]");

  std::stringstream ss;
  one.print(ss);
  ss << one;

  CHECK(ss.str() == "[[1,2][3,4]][[1,2][3,4]]");
}

/**
  * \brief Tests for ConcreteSquareMatrix checkOperands function
  */
TEST_CASE("ConcreteSquareMatrix checkOperands tests", "[concretematrix]"){

  ConcreteSquareMatrix emptyOne{};
  ConcreteSquareMatrix emptyTwo{};
  ConcreteSquareMatrix zero{3};
  ConcreteSquareMatrix one{"[[1,2][3,4]]"};

  CHECK_THROWS(zero.checkOperands(one));
  CHECK_NOTHROW(emptyOne.checkOperands(emptyTwo));
  
}

/**
  * \brief Tests for ConcreteSquareMatrix matrix checker and creation functions
  */
TEST_CASE("ConcreteSquareMatrix matrixIntoVector and emptyMatrixIntoVector tests", "[concretematrix]"){

  std::vector<std::vector<std::unique_ptr<IntElement>>> v;

  ConcreteSquareMatrix vector{};
  v = vector.matrixIntoVector("[[1,2][3,4]]");
  ConcreteSquareMatrix matrix{std::move(v)};
  CHECK(matrix.toString() == "[[1,2][3,4]]");

  ConcreteSquareMatrix emptyVector{};
  v = emptyVector.emptyMatrixIntoVector(2);
  ConcreteSquareMatrix emptyMatrix{std::move(v)};
  CHECK(emptyMatrix.toString() == "[[0,0][0,0]]");
}





/**
  * \brief Tests for SymbolicSquareMatrix constructors
  */
TEST_CASE("SymbolicSquareMatrix constructor tests", "[symbolicmatrix]"){

  CHECK_NOTHROW(SymbolicSquareMatrix{});
  CHECK_NOTHROW(SymbolicSquareMatrix{"[[x,y][X,Y]]"});
  CHECK_NOTHROW(SymbolicSquareMatrix("[[a,V,B][y,Z,e][f,G,t]]"));
  CHECK_NOTHROW(SymbolicSquareMatrix("[[x]]"));
  CHECK_NOTHROW(SymbolicSquareMatrix{"[[a,A][b,B]]"});
  CHECK_NOTHROW(SymbolicSquareMatrix("[[a,V,3][y,1,e][f,0,t]]"));
  CHECK_NOTHROW(SymbolicSquareMatrix{"[[a,b][c,1]]"});
  CHECK_NOTHROW(SymbolicSquareMatrix{"[[a,b][c,11]]"});

  CHECK_THROWS(SymbolicSquareMatrix{"[[d]]abc"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[g,f]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"["});
  CHECK_THROWS(SymbolicSquareMatrix{"[["});
  CHECK_THROWS(SymbolicSquareMatrix{"[[a"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[a,"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[a,A"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[b,B]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[b,B]["});
  CHECK_THROWS(SymbolicSquareMatrix{"[[B,a][C"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[D,f][g,y"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[r,a][x,y]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[z,f][e,f]]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[a,,e][d,f]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[wwe][e,a]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[a,A]B,c]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"d,g][a,4e]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[d,g][a,e][1,2]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[d,g][a,e][e,r]]"});
  CHECK_THROWS(SymbolicSquareMatrix{"[[d,g][a,e,s]]"});

}

/**
  * \brief Tests for SymbolicSquareMatrix copy and move constructors
  */
TEST_CASE("SymbolicSquareMatrix copy and move constructor tests", "[symbolicmatrix]"){

  SymbolicSquareMatrix zero{};
  SymbolicSquareMatrix copyOne{zero};

  // Copying zero to copyOne
  CHECK(copyOne.toString() == zero.toString());

  // Moving zero to copyTwo
  SymbolicSquareMatrix copyTwo{std::move(zero)};
  CHECK(copyTwo.toString() == copyOne.toString());

  // Checking zero is empty after move
  CHECK(zero.toString() == "[]");
}

/**
  * \brief Tests for SymbolicSquareMatrix copy and move operator overloads
  */
TEST_CASE("SymbolicSquareMatrix copy and move operator overload tests", "[symbolicmatrix]"){
  
  SymbolicSquareMatrix zero{};
  SymbolicSquareMatrix one{"[[a,A][b,B]]"};
  SymbolicSquareMatrix two{};

  // Copying one to zero
  zero = one;
  CHECK(zero.toString() == one.toString());

  // Moving zero to two
  two = std::move(zero);
  CHECK(two.toString() == one.toString());

  // Checking zero is empty after move
  CHECK(zero.toString() == "[]");

  two = std::move(two);
  CHECK(two.toString() == two.toString());

}

/**
  * \brief Tests for SymbolicSquareMatrix transpose method
  */
TEST_CASE("SymbolicSquareMatrix transpose tests", "[symbolicmatrix]"){
  
  SymbolicSquareMatrix one{"[[a,A][b,B]]"};
  SymbolicSquareMatrix transpose{};

  transpose = one.transpose();

  CHECK(transpose.toString() == "[[a,b][A,B]]");  

}

/**
  * \brief Tests for SymbolicSquareMatrix arithmetic operator overloads
  */
TEST_CASE("SymbolicSquareMatrix arithmetic operator overload tests", "[symbolicmatrix]"){

  SymbolicSquareMatrix one{"[[x,y][a,b]]"};
  SymbolicSquareMatrix two{"[[1,2][3,4]]"};
  SymbolicSquareMatrix three("[[1,2,3][x,y,a][1,2,3]]");

  Valuation map{};
  map['x'] = 1;
  map['y'] = 2;
  map['a'] = 3;
  map['b'] = 4;

  SymbolicSquareMatrix result = one + two;
  CHECK(result.evaluate(map).toString() == "[[2,4][6,8]]");

  result = one - two;
  CHECK(result.evaluate(map).toString() == "[[0,0][0,0]]");

  result = one * two;
  CHECK(result.evaluate(map).toString() == "[[7,10][15,22]]");

  result = three * three;
  CHECK(result.evaluate(map).toString() == "[[6,12,18][6,12,18][6,12,18]]");
}

/**
  * \brief Tests for SymbolicSquareMatrix comparison operator overloads
  */
TEST_CASE("SymbolicSquareMatrix comparison operator overload tests", "[symbolicmatrix]"){

  SymbolicSquareMatrix empty{};
  SymbolicSquareMatrix one{"[[a,A][B,C]]"};
  SymbolicSquareMatrix two{"[[b,D][x,C]]"};

  CHECK(empty == empty);
  CHECK(one == one);
  CHECK_FALSE(empty == one);
  CHECK_FALSE(one == two);
}

/**
  * \brief Tests for SymbolicSquareMatrix print and toString methods and operator overloads
  */
TEST_CASE("SymbolicSquareMatrix print, toString and operator<< overload tests", "[symbolicmatrix]"){

  SymbolicSquareMatrix one{"[[a,B][C,a]]"};

  CHECK(one.toString() == "[[a,B][C,a]]");

  std::stringstream ss;
  one.print(ss);
  ss << one;

  CHECK(ss.str() == "[[a,B][C,a]][[a,B][C,a]]"); 
}

/**
  * \brief Tests for SymbolicSquareMatrix evaluation method
  */
TEST_CASE("SymbolicSquareMatrix evaluate tests", "[symbolicmatrix]"){

  Valuation map{};
  map['x'] = 1;
  map['X'] = 2;
  map['y'] = 3;
  map['Z'] = 4;

  SymbolicSquareMatrix one{"[[x,X][y,Z]]"};
  ConcreteSquareMatrix result{};

  result = one.evaluate(map);

  CHECK(result.toString() == "[[1,2][3,4]]");
}

/**
  * \brief Tests for SymbolicSquareMatrix checkOperands function
  */
TEST_CASE("SymbolicSquareMatrix checkOperands tests", "[symbolicmatrix]"){

  SymbolicSquareMatrix emptyOne{};
  SymbolicSquareMatrix emptyTwo{};
  SymbolicSquareMatrix one{"[[x,y][a,b]]"};
  SymbolicSquareMatrix two{"[[1,2,3][4,5,6][7,8,9]]"};

  CHECK_THROWS(one.checkOperands(two));
  CHECK_NOTHROW(emptyOne.checkOperands(emptyTwo));
  
}

/**
  * \brief Tests for SymbolicSquareMatrix matrix checker and creation functions
  */
TEST_CASE("SymbolicSquareMatrix matrixIntoVector and emptyMatrixIntoVector tests", "[symbolicmatrix]"){

  std::vector<std::vector<std::unique_ptr<Element>>> v;

  SymbolicSquareMatrix matrix{};
  v = matrix.matrixIntoVector("[[1,2][3,4]]");
  SymbolicSquareMatrix vector{std::move(v)};
  CHECK(vector.toString() == "[[1,2][3,4]]");

  SymbolicSquareMatrix emptyMatrix{};
  v = emptyMatrix.emptyMatrixIntoVector(2);
  SymbolicSquareMatrix emptyVector{std::move(v)};
  CHECK(emptyVector.toString() == "[[x,x][x,x]]");
}