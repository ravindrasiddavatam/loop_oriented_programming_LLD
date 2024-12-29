#ifndef OBJECT_NODE_H
#define OBJECT_NODE_H
#include "binop_node.h"
#include <vector>

class ObjectNode : public ASTNode {
public:
  ObjectNode(std::string &_name, std::vector<std::string> ids,
             std::vector<ASTNode *> function_nodes,
             std::vector<ASTNode *> constructor_nodes);
  ASTResult eval(RefEnv *env);

private:
  std::string _name;
  std::vector<std::string> ids;
  std::vector<ASTNode *> function_nodes;
  std::vector<ASTNode *> constructor_nodes;
};
#endif