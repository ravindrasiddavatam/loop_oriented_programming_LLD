// File: pos_unary_node.h
#ifndef NEG_UNARY_NODE_H
#define NEG_UNARY_NODE_H

#include "ast_node.h"

class UnaryNode : public ASTNode {
public:
  UnaryNode(ASTNode *child, char whichUnaryOp);
  virtual ~UnaryNode();
  virtual ASTResult eval(RefEnv *env);

private:
  char whichUnaryOp;
  ASTNode *child;
};

#endif
