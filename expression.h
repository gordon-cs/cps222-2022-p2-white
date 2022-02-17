/*
 * expression.h - Declaration for a class representing simple arithmetic
 *                expressions.  Part of CPS222 Project 2.
 *
 * An expression is constructed from its infix form, which may consist
 * of one-digit integers, the operators +, -, *, /, and parentheses,
 * with no other characters (including spaces) allowed.  Public
 * methods are provided to return the postfix and prefix forms of the
 * expression, and to evaluate it - as well as to report errors if any
 * of the above is impossible due to a syntax or arithmetic error.
 * Private methods are provided to convert from infix to postfix and
 * from postfix to prefix, as well as to evaluate the postfix.
 *
 * Copyright (c) 2001, 2003, 2013, 2015 - Russell C. Bjork
 *
 */

#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <exception>
#include <string>
using std::string;

// The constructor of class Expression throws an exception of this type

class SyntaxError : public std::exception
{
 public:

  // Constructor
  // Parameter: position - where the error occurred
  // Parameter: description - descriptive text about the error

  SyntaxError(int position, const string description)
    : _position(position), _description(description)
    { }

  // Get the position where the error occurred on the line
  int getPosition() const {
    return _position;
  }

  // Get a text message describing the error
  const string getDescription() const {
    return _description;
  }

  // Fulfill expectation that std::exception's what() will return a
  // useful message.
  const char * what() const noexcept override {
    return _description.c_str();
  }

 private:

  int _position;
  const string _description;
};

// The code for evaluating an expression throws this if division by zero is
// attempted

class DivideByZeroError
{
 public:

  // Constructor
  // Parameter: position - where the error occurred in the postfix
  DivideByZeroError(int position)
    : _position(position) {
  }

  // Get the position where the error occurred in the postfix
  int getPosition() const {
    return _position;
  }

 private:

  int _position;
};

class Expression
{
 public:

  // Constructor.  Parameter is infix form of the expression (a string).
  // May throw a SyntaxError exception.
  Expression(string infix)
    : _infix(infix), _postfix(string("")), _prefix(string("")) {
  }

  // Return infix form of the expression

  string getInfix() const {
    return _infix;
  }

  // Return postfix form of the expression.  If the postfix form of
  // the expression is not yet known, it is calculated and stored in
  // the instance variable _postfix
  // A SyntaxError is thrown if conversion to postfix is needed and the
  // infix syntax is invalid
  string getPostfix() {
    if (_postfix.length() == 0)
      _postfix = convertToPostfix(_infix);
    return _postfix;
  }

  // Return value of the expression.
  // A SyntaxError is thrown if conversion to postfix is needed and the
  // infix syntax is invalid
  // A DivideByZeroError is thrown if division by zero is attempted
  int getValue() {
    return evaluate(getPostfix());
  }

  // Return prefix form of the expression.  If the prefix form of
  // the expression is not yet known, it is calculated and stored in
  // the instance variable _prefix.
  // A SyntaxError is thrown if conversion is needed and the
  // infix syntax is invalid
  string getPrefix() {
    if (_prefix.length() == 0)
      _prefix = convertToPrefix(getPostfix());
    return _prefix;
  }

 private:

  // Construct postfix form from infix form
  // Parameter is the infix form of the expression (a string)
  // Return value is the postfix form of the expression (a string)
  // A SyntaxError is thrown if infix syntax is invalid
  static string convertToPostfix(string infix);

  // Evaluate postfix form
  // Parameter is the postfix form of the expression (a string)
  // Return value is the value of the expression
  // A DivideByZeroError is thrown if division by zero is attempted
  static int evaluate(string postfix);

  // Construct prefix form of the expresion from postfix form
  // Parameter is the postfix form of the expression (a string)
  // Return value is the prefix form of the expression (a string)
  // No errors are possible if the postfix form is valid
  static string convertToPrefix(string postfix);

  string _infix, _postfix, _prefix;
};

#endif
