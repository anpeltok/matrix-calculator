/**
  * \file squarematrix_tests.cpp
  * \brief Catch tests for SquareMatrix class
  */
#include "catch.hpp"
#include "squarematrix.h"

/**
  * \brief Testing transpose method
  */
TEST_CASE("Test transpose, [correct]"){

  SquareMatrix two{"[[1,2][3,4]]"};
  SquareMatrix transpose = two.transpose();
  CHECK(transpose.toString() == "[[1,3][2,4]]");

  SquareMatrix single("[[1]]");
  SquareMatrix transposeTesti = single.transpose();
  CHECK(transposeTesti.toString() == "[[1]]");

  SquareMatrix three{"[[1,2,3][4,5,6][7,8,9]]"};
  SquareMatrix transpose1 = three.transpose();
  CHECK(transpose1.toString() == "[[1,4,7][2,5,8][3,6,9]]");

}

/**
  * \brief Testing copy and move copy methods, and operator overload for <<
  */
TEST_CASE("Test copy methods, [correct]"){

  SquareMatrix first{"[[1,2][3,4]]"};
  SquareMatrix second{"[[4,3][2,1]]"};
  SquareMatrix copy{first};
  CHECK(first.toString() == copy.toString());

  SquareMatrix moveCopy{std::move(copy)};
  CHECK(first.toString() == moveCopy.toString());
  CHECK_FALSE(moveCopy.toString() == copy.toString());

  copy = std::move(moveCopy);
  CHECK(first.toString() == copy.toString());
  CHECK_FALSE(moveCopy.toString() == copy.toString());

  moveCopy = copy;
  CHECK(first.toString() == moveCopy.toString());

  moveCopy = std::move(moveCopy);
  CHECK(first.toString() == moveCopy.toString());

  std::stringstream stream;
  copy.print(stream);
  CHECK(stream.str() == copy.toString());

  SquareMatrix empty{};
  CHECK((first == copy) == true);
  CHECK((first == empty) == false);
  CHECK((first == second) == false);

  std::stringstream stream2;
  stream2 << first;
  CHECK(stream2.str() == "[[1,2][3,4]]");

}

/**
  * \brief Testing methods and functions that handle arithmetics
  */
TEST_CASE("Test arithmetics, [correct]"){

  SquareMatrix result{};

  SquareMatrix first{"[[1,2][3,4]]"};
  SquareMatrix second{"[[4,3][2,1]]"};

  result = first + second;
  CHECK(result.toString() == "[[5,5][5,5]]");

  result = first - second;
  CHECK(result.toString() == "[[-3,-1][1,3]]");

  result = first * second;
  CHECK(result.toString() == "[[8,5][20,13]]");

  SquareMatrix threeOne{"[[1,2,3][4,5,6][7,8,9]]"};
  SquareMatrix threeTwo{"[[9,8,7][6,5,4][3,2,1]]"};
  threeOne *= threeTwo;
  CHECK(threeOne.toString() == "[[30,24,18][84,69,54][138,114,90]]");

}

/**
  * \brief Testing operand check method and empty matrix function
  */
TEST_CASE("Tests for operand checks and empty matrices, [correct]"){

  SquareMatrix result{};
  SquareMatrix empty{};

  SquareMatrix first{"[[1,2][3,4]]"};
  SquareMatrix second{"[[4,3][2,1]]"};

  result = empty + first;
  CHECK(result.toString() == "[[1,2][3,4]]");

  result = empty - second;
  CHECK(result.toString() == "[[-4,-3][-2,-1]]");

  result = empty * first;
  CHECK(result.toString() == "[[0,0][0,0]]");

  result = second + empty;
  CHECK(result == second);

  result = first - empty;
  CHECK(result == first);

  result = second * empty;
  CHECK(result.toString() == "[[0,0][0,0]]");
};

/**
  * \brief Testing incorrept inputs for arithmetic methods and functions
  */
TEST_CASE("Test for incorrect parameters, [incorrect input]"){

  CHECK_THROWS(SquareMatrix{} + SquareMatrix{});
  CHECK_THROWS(SquareMatrix{} - SquareMatrix{});
  CHECK_THROWS(SquareMatrix{} * SquareMatrix{});
  CHECK_THROWS(SquareMatrix{"[[1,2][3,4]]"} + SquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});
  CHECK_THROWS(SquareMatrix{"[[1,2][3,4]]"} - SquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});
  CHECK_THROWS(SquareMatrix{"[[1,2][3,4]]"} * SquareMatrix{"[[1,2,3][4,5,6][7,8,9]]"});

}

/**
  * \brief Testing SquareMatrix constructors with correct parameters
  */
TEST_CASE("Test for correct square matrix constructor inputs", "[squarematrix]"){
    
    CHECK_NOTHROW(SquareMatrix{});
    CHECK_NOTHROW(SquareMatrix{"[[1,2][3,4]]"});
    CHECK_NOTHROW(SquareMatrix("[[1,2,3][4,5,6][7,8,9]]"));
    CHECK_NOTHROW(SquareMatrix("[[1]]"));

}

/**
  * \brief Testing SquareMatrix constructors with incorrect parameters
  */
TEST_CASE("Test for incorrect square matrix inputs", "[incorrect squarematrix]"){
    
    CHECK_THROWS(SquareMatrix("[[1,2][3,4][5,6]]"));
    CHECK_THROWS(SquareMatrix("[[1,2,3][4,5]]"));
    CHECK_THROWS(SquareMatrix("[[a]]"));
    CHECK_THROWS(SquareMatrix("[[1]]abc"));
    CHECK_THROWS(SquareMatrix("[[1,2]]"));
    CHECK_THROWS(SquareMatrix("["));
    CHECK_THROWS(SquareMatrix("[["));
    CHECK_THROWS(SquareMatrix("[[1"));
    CHECK_THROWS(SquareMatrix("[[1,"));
    CHECK_THROWS(SquareMatrix("[[1,2"));
    CHECK_THROWS(SquareMatrix("[[1,2]"));
    CHECK_THROWS(SquareMatrix("[[1,2]["));
    CHECK_THROWS(SquareMatrix("[[1,2][3"));
    CHECK_THROWS(SquareMatrix("[[1,2][3,4"));
    CHECK_THROWS(SquareMatrix("[[1,2][3,4]"));
    CHECK_THROWS(SquareMatrix("[[1,2][3,4]]]"));
    CHECK_THROWS(SquareMatrix("[[1,,2][3,4]]"));
    CHECK_THROWS(SquareMatrix("[[1w2][3,4]]"));
    CHECK_THROWS(SquareMatrix("[[1,2]3,4]]"));
    CHECK_THROWS(SquareMatrix("1,2][3,4]]"));


}