/**
  * \file main.cpp
  * \brief Main, runs tests, then implements calculator in command line interface
  */

#define CATCH_CONFIG_RUNNER
#include <stack>
#include "catch.hpp"
#include "element.h"
#include "compositeelement.h"
#include "elementarymatrix.h"

int main(){

  // Calling Catch for tests
  Catch::Session().run();

  std::string input = "";
  std::stack<SymbolicSquareMatrix> matrices;
  Valuation map{};

  // Instructions
  std::cout << "Matrix calculator" << std::endl;
  std::cout << "=======================================================================================================" << std::endl;
  std::cout << "Add matrix: \t\tInput square matrix in format \"[[i11,...,inn]...[in1,...,inn]]\" to add to stack" << std::endl;
  std::cout << "Operations: \t\tInput \'+\', \'-\', or \'*\'' to perform operation using two latest matrices" << std::endl;
  std::cout << "Valuation: \t\tInput variable = value to map value. Ex. \"x=7\"" << std::endl;
  std::cout << "Values: \t\tInput \"values\" to print out mapped values" << std::endl;
  std::cout << "Result: \t\tInput \'=\'' to print value of latest matrix" << std::endl;
  std::cout << "Quit: \t\t\tInput \"quit\" to quit" << std::endl;
  std::cout << std::endl;

  // Run until "quit"
  while(input != "quit"){

    std::cout << "input: ";
    std::cin >> input;
    std::cout << std::endl;
    char c = input.at(0);

    // Quit
    if(input == "quit"){
      std::cout << "Quitting." << std::endl << std::endl;
      return 0;
    }

    // Operation
    else if(input == "+" || input == "-" || input == "*"){
      try{
        if(matrices.size() >= 2){

          SymbolicSquareMatrix one{};
          SymbolicSquareMatrix two{};
          SymbolicSquareMatrix result{};

          if(input == "+"){
            two = matrices.top();
            matrices.pop();
            one = matrices.top();
            matrices.pop();
            result = one + two;
          }
          else if(input == "-"){
            two = matrices.top();
            matrices.pop();
            one = matrices.top();
            matrices.pop();
            result = one - two;
          }
          else if(input == "*"){
            two = matrices.top();
            matrices.pop();
            one = matrices.top();
            matrices.pop();
            result = one * two;
          }
          std::cout << "Performed " << one << " "<< input << " " << two << std::endl << std::endl;
          matrices.emplace(result);
        }
        else{
          throw std::invalid_argument{"At least two matrices of same size needed for operation."};
        }
      }
      catch(std::exception e){
        std::cout << "At least two matrices of same size needed for operation." << std::endl << std::endl;
      }

    }

    // Valuation
    else if(input == "="){
      try{
        if(!matrices.empty()){
          try{
            std::cout << "Result: " << matrices.top().evaluate(map) << std::endl << std::endl;
          }
          catch(std::exception e){
            std::cout << "Value of variable missing" << std::endl << std::endl;
          }
        }
        else{
          throw std::invalid_argument{"No matrices"};
        }
      }
      catch(std::exception e){
        std::cout << "No matrices added" << std::endl << std::endl;
      }
    }

    // Printing valuation
    else if(input == "values"){

      for(auto& val : map){
        std::cout << val.first << " = " << val.second << std::endl;
      }
      std::cout << std::endl;

    }

    // Mapping values
    else if((c >= char(65) && c <= char(90)) || (c >= char(97) && c <= char(122))){

      char eq;
      int num;
      
      try{
        eq = input.at(1);
        input.erase(0,2);
        if(eq == '='){
          num = stoi(input);
          map[c] = num;
          std::cout << "Added valuation " << c << " = " << num << std::endl << std::endl;
        }
        else{
          throw std::invalid_argument{"No \'=\'"};
        }
      }
      catch(std::exception e){
        std::cout << "The format needs to be \"variable=value\", ex. \"x=7\"" << std::endl << std::endl;
      }
    }

    // Adding matrix
    else{
      try{
        matrices.emplace(SymbolicSquareMatrix{input});
        std::cout << "Added " << input << std::endl << std::endl;
      }
      catch(std::exception e){
        std::cout << "Input not valid" << std::endl << std::endl;
      }
    }
  }

  return 0;
}