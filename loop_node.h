// File: statements_node.h
// Purpose: An AST Node representing a sequence of statements.
#ifndef LOOP_NODE
#define LOOP_NODE
#include <vector>
#include "ast_node.h"

class LoopNode : public ASTNode {
public:
  LoopNode(ASTNode *_statements);
  virtual ASTResult eval(RefEnv *env);
  virtual ASTResult last_result();
private:
  ASTNode * _statements;
  ASTResult _last_result;
};
#endif