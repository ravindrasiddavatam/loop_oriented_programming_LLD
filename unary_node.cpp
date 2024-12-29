#include "unary_node.h"
#include <iostream>

UnaryNode::UnaryNode(ASTNode *_child, char whichUnaryOp) : child(_child), whichUnaryOp(whichUnaryOp) {}

UnaryNode::~UnaryNode() { delete child; }

ASTResult UnaryNode::eval(RefEnv *env) {
  ASTResult result = child->eval(env);
  if (result.type == ASTResult::INT) {
    if(whichUnaryOp == '-')
      result.parent_union.value.i = -result.parent_union.value.i;
    else
      result.parent_union.value.i = +result.parent_union.value.i;
  } else if (result.type == ASTResult::REAL) {
    if(whichUnaryOp == '-')
      result.parent_union.value.r = -result.parent_union.value.r;
    else
      result.parent_union.value.r = +result.parent_union.value.r; 
  } else {
    throw std::runtime_error("Expected Number!");
  }
  return result;
}
