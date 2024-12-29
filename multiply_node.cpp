// File: multiply_node.cpp
// Purpose: Implementation of the multiplication node.
#include "multiply_node.h"

ASTResult MultiplyNode::apply(const ASTResult &left, const ASTResult &right) {
  ASTResult result;

  // Possible type outputs
  // INT * INT -> INT
  // REAL * REAL -> REAL
  // INT * REAL -> REAL
  // REAL * INT -> REAL
  if(left.type == ASTResult::INT && right.type == ASTResult::INT) {
    result.type = ASTResult::INT;
    result.parent_union.value.i = left.parent_union.value.i * right.parent_union.value.i;
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::REAL) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.r * right.parent_union.value.r;
  } else if(left.type == ASTResult::INT && right.type == ASTResult::REAL) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.i * right.parent_union.value.r;
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::INT) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.r * right.parent_union.value.i;
  } else {
    //TODO: Handle errors here
    result.type = ASTResult::VOID;
  }

  return result;
}