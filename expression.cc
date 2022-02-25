/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */

#include "expression.h"
#include <iostream>
using std::cout;
using std::endl;

/* The following methods are to be written by students, and constitute
 * CPS222 Project 2.
 */

string Expression::convertToPostfix(string infix) {
  
  // Error checking variables
  bool expectOperator = false;
  int parenCount = 0;
  stack<int> parenPos;

  // Variables for the algorithm
  stack<char> operators;
  string postfix = "";

  for (int i = 0; i < infix.length(); i++) {
    if (infix[i] > 47 && infix[i] < 58) {

      // Error checking: make sure operand expected
      if (expectOperator) {
        throw SyntaxError(i, "Operator expected");
      }
      expectOperator = true;


      postfix += infix[i];

    } else if (infix[i] == '(') {

      // Error checking: make sure operator before open paren
      if (expectOperator) {
        throw SyntaxError(i, "Operator expected");
      }

      // Error checking: Keep track of opened paren position and value
      parenPos.push(i);
      parenCount++;


      operators.push(infix[i]);

    } else if (infix[i] == ')') {

      // Error Checking: Make sure paren was expected
      if (parenCount == 0) {
        throw SyntaxError(i, "Unbalanced parentheses");
      }
      // Error checking: make sure closing paren is after an operand
      if (!expectOperator) {
        throw SyntaxError(i, "Operand expected");
      }
      parenPos.pop();
      parenCount--;


      while (operators.top() != '(') {
        postfix += operators.top();
        operators.pop();
      }
      // Remove the '('
      operators.pop();

    } else if (infix[i] == '*' || 
                infix[i] == '+' || 
                infix[i] == '-' || 
                infix[i] == '/') {
      // Error checking: make sure operator expected
      if (!expectOperator && infix[i] != '-') {
        throw SyntaxError(i, "Operand expected");
      } else if (!expectOperator && infix[i] == '-') {
        operators.push('#');
      } else {
        expectOperator = false;
        while (!operators.empty() && precedence(infix[i]) <= precedence(operators.top())) {
          postfix += operators.top();
          operators.pop();
        }
        operators.push(infix[i]);
      }

    } else {
      // If not a valid mathematical operation, throw error
      throw SyntaxError(i, "Invalid character");
    }
  }

  if (parenCount > 0) {
    throw SyntaxError(parenPos.top(), "Unbalanced parentheses");
  }

  if (!expectOperator) {
    throw SyntaxError(infix.size(), "Operand expected");
  }

  while (!operators.empty()) {
    postfix += operators.top();
    operators.pop();
  }
  return string(postfix);
}

int Expression::evaluate(string postfix) {
  // (int)postfix[i] - 48
  stack<int> *numStack = new stack<int>;
  int *val1 = new int;
  int *val2 = new int;
  for (int i = 0; i < postfix.length(); i++) {
    if (postfix[i] > 47 && postfix[i] < 58) {
      numStack->push((int)postfix[i] - 48);
    } else if (postfix[i] == '*') {
      getValsFromStack(numStack, val1, val2);
      numStack->push(*val1 * *val2);
    } else if (postfix[i] == '/') {
      getValsFromStack(numStack, val1, val2);
      if (*val2 == 0) {
        throw DivideByZeroError(i);
      }
      numStack->push(*val1 / *val2);
    } else if (postfix[i] == '-') {
      getValsFromStack(numStack, val1, val2);
      numStack->push(*val1 - *val2);
    } else if (postfix[i] == '+') {
      getValsFromStack(numStack, val1, val2);
      numStack->push(*val1 + *val2);
    } else if (postfix[i] == '#') {
      *val1 = -numStack->top();
      numStack->pop();
      numStack->push(*val1);
    }
  }
  return numStack->top();
}

void getValsFromStack(stack<int> *numStack, int *val1, int *val2) {
  *val2 = numStack->top();
  numStack->pop();
  *val1 = numStack->top();
  numStack->pop(); 
}


string Expression::convertToPrefix(string postfix) {
  return string(""); // Students: replace code and remove this comment
}

int precedence(char c) {
  if (c == '#') {
    return 3;
  } else if (c == '/' || c == '*') {
    return 2;
  } else if (c == '+' || c == '-') {
    return 1;
  } else {
    return 0;
  }
}