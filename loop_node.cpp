#include "loop_node.h"
#include "last_result_exception.h"
#include "stop_node.h"

LoopNode::LoopNode(ASTNode *_statements) { this->_statements = _statements; }

ASTResult LoopNode::eval(RefEnv *env) {
  for (;;) {
    try {
      this->_last_result = _statements->eval(env);
    } catch (const LastResultException &e) {
      return e.last_result();
    }
  }
}

ASTResult LoopNode::last_result() { return _last_result; }