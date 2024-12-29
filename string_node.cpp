// File: string_node.cpp
// Purpose: Implementation of the string node.
#include "string_node.h"
#include <string>

std::string StringNode::replaceEscape(const std::string &input) {
  std::string result;
  size_t pos = 0;
  size_t found = input.find("\\");
  while (found != std::string::npos) {
    result += input.substr(pos, found - pos);
    switch (input[found + 1]) {
    case 'n':
      result += '\n';
      pos = found + 2;
      break;
    case 't':
      result += '\t';
      pos = found + 2;
      break;
    case 'r':
      result += '\r';
      pos = found + 2;
      break;
    case '\\':
      result += '\\';
      pos = found + 2;
      break;
    default:
      result += '\\';
      pos = found + 1;
      break;
    }
    found = input.find("\\", pos);
  }
  result += input.substr(pos);
  return result;
}

StringNode::StringNode(const Lexer::Token &token) {
  if (token.tok == CalculatorLexer::STRING) {
    _value.type = ASTResult::STRING;
    // Remove the quotes from the lexeme
    _value.parent_union.value.s = new std::string(
        replaceEscape(token.lexeme.substr(1, token.lexeme.size() - 2)));
  } else {
    _value.type = ASTResult::VOID;
  }
}

StringNode::~StringNode() {}

ASTResult StringNode::eval(RefEnv *env) { return _value; }