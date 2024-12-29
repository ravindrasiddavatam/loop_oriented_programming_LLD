// File: if_node.cpp
// Purpose: This file contains the imlplementation of the IfNode class.
#include "if_node.h"
#include "iostream"

ASTResult IfNode::eval(RefEnv *env) {
  ASTResult result;
  result.type = ASTResult::VOID;

  // do the if staement
  if (left()->eval(env).is_true()) {
    try {
      result = right()->eval(env);
    } catch (const StopException &e) {
      throw StopException();
    }
  }

  return result;
}

ASTResult IfNode::apply(const ASTResult &lhs, const ASTResult &rhs) {
  // Nothing to do here
  ASTResult result;
  return result;
}