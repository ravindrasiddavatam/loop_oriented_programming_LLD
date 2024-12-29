// File: lop_lexer.h
// Purpose: This file contains the definition of the calculator lexer.
// Author: Robert Lowe
#ifndef CALCULATOR_LEXER_H
#define CALCULATOR_LEXER_H
#include "lib/reglex.h"
#include <string.h>

class CalculatorLexer {
public:
  CalculatorLexer();

  // Lexer Tokens
  enum token_type {
    EOI = Lexer::END_OF_INPUT,
    INVALID = Lexer::INVALID,
    ADD = 1,
    SUB,
    MUL,
    DIV,
    POW,
    LPAREN,
    RPAREN,
    LFLOWER,
    RFLOWER,
    INT,
    REAL,
    ID,
    ASSIGN,
    IF,
    THEN,
    SKIP,
    STOP,
    DISPLAY,
    STRING,
    READ,
    FUNCTION,
    SEMI,
    PROMPT,
    LT,
    LTE,
    GT,
    GTE,
    EQ,
    NEQ,
    COMMA,
    HASH,
    NEW,
    LCLOSE,
    RCLOSE,
    INPUT,
    COLON,
    CONSTRUCTOR,
    PIPE
  };

  // set the input string to scan
  virtual void input(const std::string &_input);

  // return the input string being scanned
  virtual std::string input() const;

  // Get the next token from the input string
  virtual Lexer::Token next();

private:
  Lexer _lex;
};

#endif