/**
  * \file element_tests.cpp
  * \brief Catch tests for Element interface and classes
  */
#include "catch.hpp"
#include "element.h"
#include "compositeelement.h"

/**
  * \brief Tests for IntEelement constructors
  */
TEST_CASE("IntElement constructor tests", "[intelement]"){

  IntElement zero{};
  IntElement one{15};

  CHECK(zero.getVal() == 0);
  CHECK(one.getVal() == 15);

}

/**
  * \brief Tests for IntElement setter and getter
  */
TEST_CASE("IntElement setVal and getVal tests", "[intelement]"){

  IntElement zero{};
  zero.setVal(15);

  CHECK(zero.getVal() == 15);
}

/**
  * \brief Tests for IntElement clone method
  */
TEST_CASE("IntElement clone tests", "[intelement]"){

  IntElement zero{};
  Element* ptr = zero.clone();
  CHECK(ptr->toString() == zero.toString());

  delete ptr;

}

/**
  * \brief Tests for IntElement toString method
  */
TEST_CASE("IntElement toString tests", "[intelement]"){

  IntElement one{15};
  CHECK(one.toString() == "15");
}

/**
  * \brief Tests for IntElement evaluation method
  */
TEST_CASE("IntElement evaluate tests", "[intelement]"){
  
  IntElement one{15};
  std::map<char,int> map{};
  map['x'] = 15;

  CHECK(one.evaluate(map) == 15);
}

/**
  * \brief Tests for IntElement arithmetic operator overloads
  */
TEST_CASE("IntElement arithmetic operator overload tests", "[intelement]"){

  IntElement one{1};
  IntElement two{2};
  IntElement result{};

  // 1 + 2
  result = one + two;
  CHECK(result.getVal() == 3);

  // 2 - 1
  result = two - one;
  CHECK(result.getVal() == 1);

  // 2 * 2
  result = two * two;
  CHECK(result.getVal() == 4);

  // 4 + 2
  result += two;
  CHECK(result.getVal() == 6);

  // 6 - 1
  result -= one;
  CHECK(result.getVal() == 5);

  // 5 * 2
  result *= two;
  CHECK(result.getVal() == 10);
}

/**
  * \brief Tests for VariableElement constructors
  */
TEST_CASE("VariableElement constructor tests", "[varelement]"){

  CHECK_NOTHROW(VariableElement{});
  CHECK_NOTHROW(VariableElement{'a'});
  CHECK_NOTHROW(VariableElement{'A'});
  CHECK_NOTHROW(VariableElement{'z'});
  CHECK_NOTHROW(VariableElement{'Z'});
  CHECK_NOTHROW(VariableElement{int('y')});

  CHECK_THROWS(VariableElement{'['});
  CHECK_THROWS(VariableElement{'&'});
  CHECK_THROWS(VariableElement{char(15)});
  CHECK_THROWS(VariableElement{'1'});
  CHECK_THROWS(VariableElement{'0'});

}

/**
  * \brief Tests for VariableElement getter and setter
  */
TEST_CASE("VariableElement getVal and setVal tests", "[varelement]"){

  VariableElement empty{};
  VariableElement smallOne{'a'};
  VariableElement largeOne{'A'};

  CHECK(smallOne.getVal() == 'a');
  CHECK(largeOne.getVal() == 'A');

  CHECK_NOTHROW(empty.setVal('x'));
  CHECK(empty.getVal() == 'x');
  CHECK_NOTHROW(empty.setVal('Y'));
  CHECK(empty.getVal() == 'Y');

  CHECK_THROWS(empty.setVal('.'));
  CHECK_THROWS(empty.setVal(','));
  CHECK_THROWS(empty.setVal('('));

}

/**
  * \brief Tests for VariableElement clone method
  */
TEST_CASE("VariableElement clone tests", "[varelement]"){

  VariableElement zero{'a'};
  Element * ptr = zero.clone();

  CHECK(ptr->toString() == zero.toString());

  delete ptr;

}

/**
  * \brief Tests for VariableElement toString method
  */
TEST_CASE("VariableElement toString tests", "[varelement]"){

  VariableElement smallOne{'a'};
  VariableElement smallTwo{'y'};
  VariableElement largeOne{'A'};
  VariableElement largeTwo{'Y'};

  CHECK(smallOne.toString() == "a");
  CHECK(smallTwo.toString() == "y");
  CHECK(largeOne.toString() == "A");
  CHECK(largeTwo.toString() == "Y");
}

/**
  * \brief Tests for VariableElement evaluation method
  */
TEST_CASE("VariableElement evaluate tests", "[varelement]"){

  std::map<char,int> map{};
  
  map['x'] = 1;
  map['X'] = 2;
  map['y'] = 3;
  map['Y'] = 4;
  map['z'] = 5;

  VariableElement one{'x'};
  VariableElement two{'X'};
  VariableElement three{'y'};
  VariableElement four{'Y'};
  VariableElement five{'z'};
  VariableElement six{'Z'};

  CHECK(one.evaluate(map) == 1);
  CHECK(two.evaluate(map) == 2);
  CHECK(three.evaluate(map) == 3);
  CHECK(four.evaluate(map) == 4);
  CHECK(five.evaluate(map) == 5);
  CHECK_THROWS(six.evaluate(map));
}






/**
  * \brief Tests for Element print operator overload
  */
TEST_CASE("Element operator<< overload tests", "[element]"){

  IntElement val{15};
  VariableElement var{'x'};

  std::stringstream ss;
  ss << var << val;

  CHECK(ss.str() == "x15");
}

/**
  * \brief Tests for Element comparison operator overload
  */
TEST_CASE("Element operator== overload tests", "[element]"){

  IntElement one{1};
  IntElement two{2};
  VariableElement x{'x'};
  CompositeElement comp{one, x, std::plus<int>{}, '+'};

  CHECK(one == one);
  CHECK(x == x);
  CHECK(comp == comp);
  CHECK_FALSE(one == two);
  CHECK_FALSE(one == x);
  CHECK_FALSE(one == comp);


}








/**
  * \brief Tests for CompositeElement constructors
  */
TEST_CASE("CompositeElement constructor tests", "[compositeelement]"){

  IntElement one{1};
  VariableElement x{'x'};
  CHECK_NOTHROW(CompositeElement{one, x, std::plus<int>{}, '+'});

  CompositeElement comp{one, x, std::plus<int>{}, '+'};
  CHECK_NOTHROW(CompositeElement{comp});


}

/**
  * \brief Tests for CompositeElement copy operator overload
  */
TEST_CASE("CompositeElement copy operator tests", "[compositeelement"){

  IntElement one{1};
  VariableElement x{'x'};
  CompositeElement comp1{one, x, std::plus<int>{}, '+'};
  CompositeElement comp2{x, one, std::minus<int>{}, '-'};
  comp2 = comp1;
  CHECK(comp2 == comp1);
}

/**
  * \brief Tests for CompositeElement clone method
  */
TEST_CASE("CompositeElement clone tests", "[compositeelement]"){

  IntElement one{1};
  VariableElement x{'x'};
  CompositeElement comp{one, x, std::plus<int>{}, '+'};

  Element * ptr = comp.clone();

  CHECK(ptr->toString() == comp.toString());

  delete ptr;

}

/**
  * \brief Tests for CompositeElement toString method
  */
TEST_CASE("CompositeElement toString tests", "[compositeelement]"){

  IntElement one{1};
  VariableElement x{'x'};
  CompositeElement comp{one, x, std::plus<int>{}, '+'};

  CHECK(comp.toString() == "(1+x)");


}

/**
  * \brief Tests for CompositeElement evaluation method
  */
TEST_CASE("CompositeElement evaluate tests", "[compositeelement]"){

  Valuation map{};
  
  map['x'] = 4;
  map['y'] = 5;
  map['z'] = 6;

  IntElement one{1};
  IntElement two{2};
  IntElement three{3};
  VariableElement x{'x'};
  VariableElement y{'y'};
  VariableElement z{'z'};

  CompositeElement first{one, x, std::plus<int>{}, '+'};
  CompositeElement second{two, y, std::plus<int>{}, '+'};
  CompositeElement third{three, z, std::plus<int>{}, '+'};

  CHECK(first.evaluate(map) == 5);
  CHECK(second.evaluate(map) == 7);
  CHECK(third.evaluate(map) == 9);
}