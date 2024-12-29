// File: display_node.h
#ifndef DISPLAY_NODE_H
#define DISPLAY_NODE_H

#include "ast_node.h"

class DisplayNode : public ASTNode {
public:
  DisplayNode(ASTNode *child);
  virtual ~DisplayNode();
  virtual ASTResult eval(RefEnv *env);

private:
  ASTNode *child;
};

#endif
