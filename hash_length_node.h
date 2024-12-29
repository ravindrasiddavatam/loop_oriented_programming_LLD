#ifndef HASH_LENGTH_NODE_H
#define HASH_LENGTH_NODE_H

#include "binop_node.h"

class HashLength : public ASTNode {
public:
  HashLength(ASTNode *node);
  ASTResult eval(RefEnv *env);

private:
  ASTNode *node;
};

#endif
