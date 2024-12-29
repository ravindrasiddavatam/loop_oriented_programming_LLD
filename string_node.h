// File: string_node.h
// Purpose: Definition of a string node for the AST
#ifndef STRING_NODE_H
#define STRING_NODE_H

#include "ast_node.h"
#include "lop_lexer.h"
#include <string>

class StringNode : public ASTNode {
public:
  StringNode(const Lexer::Token &token);
  virtual ~StringNode();
  virtual ASTResult eval(RefEnv *env);
  std::string replaceEscape(const std::string &input);

private:
  ASTResult _value;
};

#endif