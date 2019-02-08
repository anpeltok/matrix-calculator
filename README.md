
Matrix calculator for Advanced Object Oriented Programming course in C++.

Currently work in progress, includes calculator functionality for square matrix inputs of strings in "[[n11,...,n1n]...[nn1,...,nnn]]" format.
Functionality is tested with Catch tests in tests.cpp.

Lastly edited to for Element interface, char variables and symbolic square matrices.

Currently work in progress, includes calculator functionality for square matrix inputs of strings in "[[n11,...,n1n]...[nn1,...,nnn]]" format. ConcreteSquareMatrix class contains matrices of IntElement objects encapsulating int values. SymbolicSquareMatrix contains matrices of both IntElement objects and VariableElements encapsulating char variables. Element interface for both Element subclasses. Evaluation class for mapping variables to int values.

Using Doxygen notation as required by the course.

Andrea Peltokorpi, 2019