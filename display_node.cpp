// File: display_node.cpp
#include "display_node.h"
#include <iostream>

DisplayNode::DisplayNode(ASTNode *_child) : child(_child) {}

DisplayNode::~DisplayNode() { delete child; }

ASTResult DisplayNode::eval(RefEnv *env) {
  ASTResult result = child->eval(env);
  if (result.type == ASTResult::INT) {
    std::cout << result.parent_union.value.i;
  } else if (result.type == ASTResult::REAL) {
    std::cout << result.parent_union.value.r;
  } else if (result.type == ASTResult::STRING) {
    std::cout << *result.parent_union.value.s;
  }
  result.type = ASTResult::VOID;
  return result;
}
