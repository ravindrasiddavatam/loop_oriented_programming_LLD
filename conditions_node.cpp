#include "conditions_node.h"
#include <iostream>

ConditionsNode::ConditionsNode(const std::string &condition)
    : _condition(condition) {}

ConditionsNode::~ConditionsNode() {}

ASTResult ConditionsNode::apply(const ASTResult &lhs, const ASTResult &rhs) {
  ASTResult result;
  float lhs_value = lhs.type == ASTResult::INT ? lhs.parent_union.value.i
                                               : lhs.parent_union.value.r;
  float rhs_value = rhs.type == ASTResult::INT ? rhs.parent_union.value.i
                                               : rhs.parent_union.value.r;
  result.type = ASTResult::INT;
  if (this->_condition == "=") {
    result.parent_union.value.i = lhs_value == rhs_value;
    if (lhs.type == ASTResult::STRING)
      result.parent_union.value.i =
          *lhs.parent_union.value.s == *rhs.parent_union.value.s;
  } else if (this->_condition == "<>") {
    result.parent_union.value.i = lhs_value != rhs_value;
    if (lhs.type == ASTResult::STRING)
      result.parent_union.value.i =
          *lhs.parent_union.value.s != *rhs.parent_union.value.s;
  } else if (this->_condition == ">") {
    result.parent_union.value.i = lhs_value > rhs_value;
    if (lhs.type == ASTResult::STRING)
      result.parent_union.value.i =
          *lhs.parent_union.value.s > *rhs.parent_union.value.s;
  } else if (this->_condition == ">=") {
    result.parent_union.value.i = lhs_value >= rhs_value;
    if (lhs.type == ASTResult::STRING)
      result.parent_union.value.i =
          *lhs.parent_union.value.s >= *rhs.parent_union.value.s;
  } else if (this->_condition == "<=") {
    result.parent_union.value.i = lhs_value <= rhs_value;
    if (lhs.type == ASTResult::STRING)
      result.parent_union.value.i =
          *lhs.parent_union.value.s <= *rhs.parent_union.value.s;
  } else if (this->_condition == "<") {
    result.parent_union.value.i = lhs_value < rhs_value;
    if (lhs.type == ASTResult::STRING)
      result.parent_union.value.i =
          *lhs.parent_union.value.s < *rhs.parent_union.value.s;
  } else {
    result.type = ASTResult::VOID;
  }

  return result;
}
