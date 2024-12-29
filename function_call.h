#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H

#include "binop_node.h"
#include <vector>

class FunctionCall : public ASTNode {
public:
  FunctionCall(std::string &_name, std::vector<ASTNode *> ids,
               std::string &obj_func);
  ASTResult eval(RefEnv *env);

private:
  std::string _name;
  std::vector<ASTNode *> func;
  std::string obj_func;
};

#endif
