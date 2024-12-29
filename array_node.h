#ifndef ARRAY_NODE_H
#define ARRAY_NODE_H

#include "binop_node.h"
#include <vector>

class ArrayNode : public ASTNode {
public:
  ArrayNode(std::vector<ASTNode *> nodes);
  ASTResult eval(RefEnv *env);

private:
  std::vector<ASTNode *> nodes;
};

#endif
