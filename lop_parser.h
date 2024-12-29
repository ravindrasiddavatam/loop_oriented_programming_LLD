// File: lop_parser.h
// Purpose: This file contains the definition of the calculator parser.
// Author: Robert Lowe
#ifndef CALCULATOR_PARSER_H
#define CALCULATOR_PARSER_H
#include "add_node.h"
#include "array_node.h"
#include "assign_node.h"
#include "ast_node.h"
#include "conditions_node.h"
#include "display_node.h"
#include "divide_node.h"
#include "function_call.h"
#include "function_ref.h"
#include "hash_length_node.h"
#include "if_node.h"
#include "input_node.h"
#include "loop_node.h"
#include "lop_lexer.h"
#include "multi_id.h"
#include "multiply_node.h"
#include "new_object_node.h"
#include "number_node.h"
#include "object_node.h"
#include "pow_node.h"
#include "ref_node.h"
#include "statements_node.h"
#include "stop_node.h"
#include "string_node.h"
#include "subtract_node.h"
#include "unary_node.h"
#include <iostream>
#include <stdexcept>

class CalculatorParser {
public:
  ASTNode *parse(CalculatorLexer *_lexer);

private:
  CalculatorLexer *_lexer;
  Lexer::Token _cur;

  // advance the lexer
  void next();

  // check to see if the cur  rent token matches the given token
  bool has(int t);

  // < Expression > ::= < Ref > < Expression' >
  //                    | < Sum >
  ASTNode *parse_expression();

  // < Expression' > ::= ASSIGN < Expression >
  //                     | < Sum' >
  ASTNode *parse_expression2(ASTNode *left);

  //< Sum > ::= < Term > < Sum' >
  ASTNode *parse_sum();

  //< Sum' >::= ADD < Term > < Sum' >
  //                   | SUB < Term > < Sum' >
  //                   | ""
  ASTNode *parse_sum2(ASTNode *left);

  //< Term >       ::= < Factor > < Term' >
  ASTNode *parse_term();

  //< Term' >      ::= MUL < Factor > < Term' >
  //                   | DIV < Factor > < Term' >
  //                   | ""
  ASTNode *parse_term2(ASTNode *left);

  //< Factor >     ::= < Exponent > < Factor' >
  ASTNode *parse_factor();

  //< Factor' >    ::= POW < Exponent >
  //                   | ""
  ASTNode *parse_factor2(ASTNode *left);

  //< Exponent >   ::= INT
  //                   | REAL
  //                   | < Ref >
  //                   | LPAR < Expression > RPAR
  ASTNode *parse_unary();
  ASTNode *parse_access();

  //< Ref >        ::= ID
  ASTNode *parse_ref();

  // if condition then statement
  ASTNode *parse_if();

  // collection of statements
  ASTNode *parse_statements();

  ASTNode *parse_input();

  ASTNode *parse_display();

  ASTNode *parse_loop();

  ASTNode *parse_function_def();

  ASTNode *parse_id();

  ASTNode *parse_comparisons();

  ASTNode *parse_comparisons2(ASTNode *left);

  ASTNode *parse_condition();

  ASTNode *parse_condition2(ASTNode *left);

  ASTNode *parse_assign();

  ASTNode *parse_constructor();

  ASTNode *parse_object_def(std::string &id);

  ASTNode *parse_assign2(ASTNode *left);
};

#endif