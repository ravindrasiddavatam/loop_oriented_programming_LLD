#include "statements_node.h"
#include "last_result_exception.h"
#include "stop_node.h"

ASTResult StatementsNode::eval(RefEnv *env) {
  try {
    for (ASTNode *node : _statements) {
      _last_result = node->eval(env);
    }
  } catch (const StopException &e) {
    throw LastResultException(_last_result);
  }
  return _last_result;
}

void StatementsNode::add_statement(ASTNode *node) {
  _statements.push_back(node);
}

ASTResult StatementsNode::last_result() { return _last_result; }