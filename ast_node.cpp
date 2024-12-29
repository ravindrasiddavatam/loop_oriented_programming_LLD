// File: ast_node.cpp
// Purpose: Empty virtual destructor for ASTNode.
#include "ast_node.h"

// implement our language's truthiness
bool ASTResult::is_true() const {
  int result;

  // extract an integer for the result
  switch (type) {
  case INT:
    result = parent_union.value.i;
    break;
  case REAL:
    result = (int)parent_union.value.r;
    break;
  case STRING:
    result = (*parent_union.value.s).length();
    break;
  case ARRAY:
    result = (*parent_union.value.array.array_results).size();
    break;
  case NEW_OBJECT:
    result = 1;
    break;
  case VOID:
    result = 0;
    break;
  }

  return result != 0;
}

ASTNode::~ASTNode() {}