
Matrix calculator for Advanced Object Oriented Programming course in C++
========================================================================

Uses template class TElement for int elements and variable elements, and for matrices containing only int Elements and both int and variable elements. Both are under Element interface. Also uses CompositeElement class to perform arithmetic operations on variable based matrices.

Also uses template class ElementarySquareMatrix for matrices containing either int specialization of TElement, or both int and char specializations of classes.

Includes calculator functionality for nxn size square matrix inputs of strings in "[[11,...,1n][n1,...,nn]]" format. Main first runs Catch tests, then waits for user input.


Inputs:

Add matrix:             Input matrix in format "[[11,1n][n1,nn]" to add square matrix into stack.

Operations:             Input +, - or * to perform corresponding operation on two topmost matrices in stack (matrices must be                         same size).

Map value:              Input "variable=value" to map values to char variables, ex. "x=7".

Print stored values:    Input "values" to print stored values.

Print result:           Input = to print evaluation of topmost matrix.

Quit:                   Input "quit" to quit.


Using Doxygen notation as required by the course.

Functionality is tested with Catch tests in elmentarymatrix_tests.cpp and element_tests.cpp.



Andrea Peltokorpi, 2019
