
#include <iostream>

int main()
{
    int i, j, * p;
    i = 7; // variable i is an lvalue, the literal 7 is a prvalue
    *p = i; //the dereferenced pointer is an lvalue.
    ((i < 3) ? i : j) = 7; //the conditional operator returns an lvalue.

}

/*
* Every c++ expression has a Category value.
* those values sets the rules that the compiler follow to for the creation, copy, movement of object during
* the evaluation of an expression
*
* for c++ 17 standard there are 5 values
*                           expression
*                               |
*                   glvalue  --------- rvalue
*                      |                 |
*                  -----------    ---------------
*                 |           |  |              |
*              lvalue        xvalue           prvalue
*
* glvalue: is an expression whose evaluation determines the identity of an object, bit-field, or function.
* prvalue: is an expression whose evaluation initializes an object or a bit-field, or computes the value of the operand of an operator, as specified by the context in which it appears.
* xvalue: is a glvalue that denotes an object or bit-field whose resources can be reused.
* lvalue is a glvalue that isn't an xvalue.
* rvalue is a prvalue or an xvalue.
*
* lvalues has an address that the programm can access: variable names, const, array elements, function calls that return an lvalue element, bit-fields, union, class members
* prvalue has no accessible address: literals, function that return a non reference type, temporary object
* xvalue has no longer an accessible address but it can be used to initialize an rvalue:function calls that return an rvalue reference, and the array subscript, member and pointer to member expressions where the array or object is an rvalue reference.
*/