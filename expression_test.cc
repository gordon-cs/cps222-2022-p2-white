#include "gtest/gtest.h"
#include "expression.h"


TEST(postfix, two) {
  Expression e("2");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, someAddition) {
  Expression e("2+3+4");
  EXPECT_EQ("23+4+", e.getPostfix());
}

TEST(postfix, addMult) {
  Expression e("2+3+4+3*4");
  EXPECT_EQ("23+4+34*+", e.getPostfix());
}

// ask about this one !!!!!!
TEST(postfix, addMultDiv) {
  Expression e("2+3*4+5*6/2");
  EXPECT_EQ("234*+56*2/+", e.getPostfix());
}

TEST(postfix, twoParen) {
  Expression e("(2)");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, parenAddMultParenDiv) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ("13+24+*", e.getPostfix());
}

TEST(postfix, longExpression) {
  Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
  EXPECT_EQ("324+11+*7+*25*9+/", e.getPostfix());
}

TEST(postfix, longerExpression) {
  Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
  EXPECT_EQ("742472-*542-**54*5*/+*+", e.getPostfix());
}

TEST(postfix, multipleParentheses) {
  Expression e("(((2)))");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, hw23a) {
  Expression e("(7+2)*(3+4)-1");
  EXPECT_EQ("72+34+*1-", e.getPostfix());
}

TEST(postfix, hw23b) {
  Expression e("8-((4+1)*2-5)/9");
  EXPECT_EQ("841+2*5-9/-", e.getPostfix());
}

TEST(postfix, hw23c) {
  Expression e("(3*2+1)/(4+5)");
  EXPECT_EQ("32*1+45+/", e.getPostfix());
}

TEST(evaluate, two) {
  Expression e("2");
  EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, someAddition) {
  Expression e("2+3+4");
  EXPECT_EQ(9, e.getValue());
}

TEST(evaluate, addMult) {
  Expression e("2+3+4+3*4");
  EXPECT_EQ(21, e.getValue());
}

TEST(evaluate, addMultDiv) {
  Expression e("2+3*4+5*6/2");
  EXPECT_EQ(29, e.getValue());
}

TEST(evaluate, twoParen) {
  Expression e("(2)");
  EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, parenAddMultParenDiv) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ(24, e.getValue());
}

TEST(evaluate, longExpression) {
  Expression e("3*((2+4)*(1+1)+7)/(2*5+9)");
  EXPECT_EQ(3, e.getValue());
}

TEST(evaluate, longerExpression) {
  Expression e("7+4*(2+4*(7-2)*(5*(4-2))/(5*4*5))");
  EXPECT_EQ(23, e.getValue());
}

TEST(evaluate, multipleParentheses) {
  Expression e("(((2)))");
  EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, hw23a) {
  Expression e("(7+2)*(3+4)-1");
  EXPECT_EQ(62, e.getValue());
}

// Unary Tests

TEST(postfix, unary1) {
  Expression e("-3");
  EXPECT_EQ("3#", e.getPostfix());
}

TEST(evaluate, unary1) {
  Expression e("-3");
  EXPECT_EQ(-3, e.getValue());
}

TEST(postfix, unary2) {
  Expression e("2*-3");
  EXPECT_EQ("23#*", e.getPostfix());
}

TEST(evaluate, unary2) {
  Expression e("2*-3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(postfix, unary3) {
  Expression e("2*(-3)");
  EXPECT_EQ("23#*", e.getPostfix());
}

TEST(evaluate, unary) {
  Expression e("2*(-3)");
  EXPECT_EQ(-6, e.getValue());
}

TEST(postfix, unary4) {
  Expression e("-2*3");
  EXPECT_EQ("2#3*", e.getPostfix());
}

TEST(evaluate, unary4) {
  Expression e("-2*3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(postfix, unary5) {
  Expression e("-2*3");
  EXPECT_EQ("2#3*", e.getPostfix());
}

TEST(evaluate, unary5) {
  Expression e("-2*3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(postfix, unary6) {
  Expression e("--3");
  EXPECT_EQ("3##", e.getPostfix());
}

TEST(evaluate, unary6) {
  Expression e("--3");
  EXPECT_EQ(3, e.getValue());
}

TEST(postfix, unary7) {
  Expression e("---3");
  EXPECT_EQ("3###", e.getPostfix());
}

TEST(evaluate, unary7) {
  Expression e("---3");
  EXPECT_EQ(-3, e.getValue());
}

TEST(postfix, unary8) {
  Expression e("2*---3");
  EXPECT_EQ("23###*", e.getPostfix());
}

TEST(evaluate, unary8) {
  Expression e("2*---3");
  EXPECT_EQ(-6, e.getValue());
}

TEST(postfix, unary9) {
  Expression e("2*(---3)");
  EXPECT_EQ("23###*", e.getPostfix());
}

TEST(evaluate, unary9) {
  Expression e("2*(---3)");
  EXPECT_EQ(-6, e.getValue());
}

TEST(postfix, unary10) {
  Expression e("---2*2+--3");
  EXPECT_EQ("2###2*3##+", e.getPostfix());
}

TEST(evaluate, unary10) {
  Expression e("---2*2+--3");
  EXPECT_EQ(-1, e.getValue());
}

// Error checking tests

TEST(postfixError, empty) {
  try {
    Expression e("");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, plus) {
  try {
    Expression e("+");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOperator) {
  try {
    Expression e("1+23");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOperator2) {
  try {
    Expression e("0+12*3");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOperand) {
  try {
    Expression e("0+*1+2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(2, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOperand2) {
  try {
    Expression e("*1+2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOperand3) {
  try {
    Expression e("1+2+");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(4, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOperator3) {
  try {
    Expression e("1+2(3+4");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOperator4) {
  try {
    Expression e("(1+2)3+4");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
  }
}

TEST(postfixError, missingOperand4) {
  try {
    Expression e("(*4)+(2*4)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(1, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOperand5) {
  try {
    Expression e("(2*)+(2*4)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}

TEST(postfixError, missingOperand6) {
  try {
    Expression e("((1*3)+)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(7, e.getPosition());
    EXPECT_EQ("Operand expected", e.getDescription());
  }
}


TEST(postfixError, missingParen) {
  try {
    Expression e("1)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(1, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen2) {
  try {
    Expression e("(1*3)+(2*4");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(6, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen3) {
  try {
    Expression e("((((2)))");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen4) {
  try {
    Expression e("1+2)");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen5) {
  try {
    Expression e("(1*3))");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen6) {
  try {
    Expression e("(1*3))(");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(postfixError, missingParen7) {
  try {
    Expression e("(1*3))+(2");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(5, e.getPosition());
    EXPECT_EQ("Unbalanced parentheses", e.getDescription());
  }
}

TEST(evaluateError, divByZero) {
  try {
    Expression e("3/0");
    e.getValue();
    FAIL() << "Didn't throw the expected exception.";
  } catch(DivideByZeroError &e) {
    EXPECT_EQ(2, e.getPosition());
  }
}

TEST(evaluateError, divByZero2) {
  try {
    Expression e("3/(1-1)");
    e.getValue();
    FAIL() << "Didn't throw the expected exception.";
  } catch(DivideByZeroError &e) {
    EXPECT_EQ(4, e.getPosition());
  }
}

TEST(postfixError, invalidCharacter) {
  try {
    Expression e("a+2");
    e.getValue();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(0, e.getPosition());
    EXPECT_EQ("Invalid character", e.getDescription());
  }
}

TEST(postfixError, invalidCharacter2) {
  try {
    Expression e("1a2");
    e.getValue();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(1, e.getPosition());
    EXPECT_EQ("Invalid character", e.getDescription());
  }
}
