// File: pow_node.cpp
// Purpose: Implementation of the exponentiation (power) node.
#include "pow_node.h"
#include <cmath> // For pow()

ASTResult PowNode::apply(const ASTResult &left, const ASTResult &right) {
  ASTResult result;

  // Exponentiation outcomes are simplified to REAL for simplicity and to accommodate
  // large or fractional powers.
  result.type = ASTResult::REAL;

  if(left.type == ASTResult::INT && right.type == ASTResult::INT) {
    result.type = ASTResult::INT;
    result.parent_union.value.i = (int) std::pow(static_cast<double>(left.parent_union.value.i), right.parent_union.value.i);
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::REAL) {
    result.parent_union.value.r = std::pow(left.parent_union.value.r, right.parent_union.value.r);
  } else if(left.type == ASTResult::INT && right.type == ASTResult::REAL) {
    result.parent_union.value.r = std::pow(static_cast<double>(left.parent_union.value.i), right.parent_union.value.r);
  } else if(left.type == ASTResult::REAL && right.type == ASTResult::INT) {
    result.parent_union.value.r = std::pow(left.parent_union.value.r, static_cast<double>(right.parent_union.value.i));
  } else {
    // Handle invalid cases or errors
    result.type = ASTResult::VOID;
  }

  return result;
}