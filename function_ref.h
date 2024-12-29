#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "binop_node.h"
#include <vector>

class FunctionRef : public ASTNode {
public:
  FunctionRef(std::string &_name, std::vector<std::string> ids,
              ASTNode *loop_node);
  ASTResult eval(RefEnv *env);

private:
  std::string _name;
  std::vector<std::string> ids;
  ASTNode *loop_node;
};

#endif
