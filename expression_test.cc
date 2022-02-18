#include "gtest/gtest.h"
#include "expression.h"

TEST(postfix, two) {
  Expression e("2");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, someParens) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ("13+24+*", e.getPostfix());
}

TEST(postfix, multipleParentheses) {
  Expression e("(((2)))");
  EXPECT_EQ("2", e.getPostfix());
}

TEST(postfix, someAddition) {
  Expression e("2+3+4");
  EXPECT_EQ("234++", e.getPostfix());
}

TEST(postfix, hw3aMod) {
  Expression e("(7+2)*(3+4)-1");
  EXPECT_EQ("72+34+*1-", e.getPostfix());
}

TEST(postfix, hw3bMod) {
  Expression e("8-((4+1)*2-5)/9");
  EXPECT_EQ("841+2*5-9/-", e.getPostfix());
}

TEST(evaluate, two) {
  Expression e("2");
  EXPECT_EQ(2, e.getValue());
}

TEST(evaluate, someParens) {
  Expression e("(1+3)*(2+4)");
  EXPECT_EQ(24, e.getValue());
}

/*
// The tests below illustrate the error messages
// (exception  descriptions) my tests will look for.
// Please throw exceptions with these messages.

// Comment out tests for options you don't do.
TEST(postfixError, empty) {
  // test that invalid empty expression causes syntax error
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

TEST(postfixError, missingOp) {
  try {
    Expression e("1+23");
    e.getPostfix();
    FAIL() << "Didn't throw the expected exception.";
  } catch(SyntaxError &e) {
    EXPECT_EQ(3, e.getPosition());
    EXPECT_EQ("Operator expected", e.getDescription());
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

*/