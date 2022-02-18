/*
 * expression.cc - Implementation of a class representing simple arithmetic
 *                 expressions, as declared in expression.h.  Part of CPS222
 *                 Project 2.
 *
 * Skeleton copyright (c) 2001, 2013 - Russell C. Bjork
 *
 */

#include "expression.h"

/* The following methods are to be written by students, and constitute
 * CPS222 Project 2.
 */

string Expression::convertToPostfix(string infix) {
  stack<char> operators;
  string postfix = "";
  for (int i = 0; i < infix.length(); i++) {
    if (infix[i] > 47 && infix[i] < 58) {
      postfix += infix[i];
    } else if (infix[i] == '(') {
      operators.push(infix[i]);
    } else if (infix[i] == ')') {
      while (operators.top() != '(') {
        postfix += operators.top();
        operators.pop();
      }
      // Remove the '('
      operators.pop();
    } else {
      while (!operators.empty() && precedence(infix[i]) < precedence(operators.top())) {
        postfix += operators.top();
        operators.pop();
      }
      operators.push(infix[i]);
    }
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
      numStack->push(*val1 / *val2);
    } else if (postfix[i] == '-') {
      getValsFromStack(numStack, val1, val2);
      numStack->push(*val1 - *val2);
    } else if (postfix[i] == '+') {
      getValsFromStack(numStack, val1, val2);
      numStack->push(*val1 + *val2);
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
  if (c == '/' || c == '*') {
    return 2;
  } else if (c == '+' || '-') {
    return 1;
  } else {
    return 0;
  }
}