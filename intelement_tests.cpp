/**
  * \file intelement_tests.cpp
  * \brief Catch tests for IntElement class
  */
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "intelement.h"

/**
  * \brief Testing constructors, getter, setter, output methods and operator overloads
  */
TEST_CASE("IntElement tests", "[intelement]"){

  IntElement empty{};
  CHECK(empty.getVal() == 0);

  empty = *empty.clone();
  CHECK(empty.getVal() == 0);

  empty.setVal(15);
  CHECK(empty.getVal() == 15);

  IntElement five{5};
  CHECK(five.getVal() == 5);

  IntElement result{};
  result = empty + five;
  CHECK(result.getVal() == 20);

  result = empty - five;
  CHECK(result.getVal() == 10);

  result = empty * five;
  CHECK(result.getVal() == 75);

  result += five;
  result.setVal(10);
  result += five;
  CHECK(result.getVal() == 15);

  result -= five;
  CHECK(result.getVal() == 10);

  result *= five;
  CHECK(result.getVal() == 50);

  CHECK((empty == result) == false);
  CHECK((empty != result) == true);

  empty.setVal(50);
  CHECK((empty == result) == true);
  CHECK((empty != result) == false);

  std::stringstream test;
  test << result;
  CHECK(test.str() == std::to_string(result.getVal()));

  IntElement value{5};
  std::unique_ptr<IntElement> ptr = value.clone();
  CHECK(*ptr == value);

  IntElement testi{0};
  std::unique_ptr<IntElement> defel = testi.clone();



  CHECK(testi.getVal() == 0);


}