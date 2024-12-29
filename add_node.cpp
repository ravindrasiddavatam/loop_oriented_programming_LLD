// File: add_node.cpp
// Purpose: Implementation of the addition node.
#include "add_node.h"

ASTResult AddNode::apply(const ASTResult &left, const ASTResult &right) {
  ASTResult result;
  
  // Possible type outputs (Attribute Grammar)
  // INT + INT -> INT     .i + .i
  // REAL + REAL -> REAL   .r + .r
  // INT + REAL -> REAL    .i + .r
  // REAL + INT -> REAL    .r + .i
  if(left.type == ASTResult::INT && right.type == ASTResult::INT) {
    result.type = ASTResult::INT;
    result.parent_union.value.i = left.parent_union.value.i + right.parent_union.value.i;
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::REAL) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.r + right.parent_union.value.r;
  } else if(left.type == ASTResult::INT && right.type == ASTResult::REAL) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.i + right.parent_union.value.r;
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::INT) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.r + right.parent_union.value.i;
  } else {
    //TODO: Handle errors here
    result.type = ASTResult::VOID;
  }

  return result;
}