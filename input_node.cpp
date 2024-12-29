// File: input_node.cpp
// Purpose: Implementation of the reference node.
#include "input_node.h"
#include "string_node.h"
#include <iostream>
#include <sstream>

// Constructor and Destructor
InputNode::InputNode(ASTNode *prompt, const std::string &_name) {
  this->_name = _name;
  this->_prompt = prompt;
}

InputNode::~InputNode() {}

ASTResult InputNode::eval(RefEnv *env) {
  ASTResult result;

  std::string input;
  if (_prompt) {
    std::cout << *(this->_prompt->eval(env).parent_union.value.s);
  } else {
    std::cout << this->_name << "=";
  }
  std::getline(std::cin, input);
  std::istringstream iss(input);

  env->declare(_name);
  ASTResult *tmp = env->lookup(_name);

  if (iss >> result.parent_union.value.r) {
    result.type = ASTResult::REAL;
  } else if (iss >> result.parent_union.value.i) {
    result.type = ASTResult::INT;
  } else {
    result.type = ASTResult::STRING;
    Lexer::Token token;
    StringNode stringNode(token);

    if (input.find('"') != std::string::npos) {
      result.parent_union.value.s = new std::string(
          stringNode.replaceEscape(input.substr(1, input.size() - 2)));
    } else {
      result.parent_union.value.s = new std::string(stringNode.replaceEscape(input));
    }
  }
  *tmp = result;
  result.type = ASTResult::VOID;
  return result;
}
