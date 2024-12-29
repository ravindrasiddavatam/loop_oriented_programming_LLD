// File: divide_node.cpp
// Purpose: Implementation of the division node.
#include "divide_node.h"

ASTResult DivideNode::apply(const ASTResult &left, const ASTResult &right) {
  ASTResult result;

  // Check for division by zero
  if ((right.type == ASTResult::INT && right.parent_union.value.i == 0) ||
      (right.type == ASTResult::REAL && right.parent_union.value.r == 0.0)) {
    //TODO: Handle division by zero error
    result.type = ASTResult::VOID;
    return result;
  }

  // Possible type outcomes
  // INT / INT -> REAL (to handle fractional results)
  // REAL / REAL -> REAL
  // INT / REAL -> REAL
  // REAL / INT -> REAL
  if(left.type == ASTResult::INT && right.type == ASTResult::INT) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = static_cast<double>(left.parent_union.value.i) / right.parent_union.value.i;
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::REAL) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.r / right.parent_union.value.r;
  } else if(left.type == ASTResult::INT && right.type == ASTResult::REAL) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.i / right.parent_union.value.r;
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::INT) {
    result.type = ASTResult::REAL;
    result.parent_union.value.r = left.parent_union.value.r / right.parent_union.value.i;
  } else {
    // If the operation doesn't match any known type combination, set the type to VOID
    result.type = ASTResult::VOID;
  }

  return result;
}