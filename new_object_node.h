#ifndef NEW_OBJECT_NODE_H
#define NEW_OBJECT_NODE_H
#include "ast_node.h"
#include <vector>

class NewObjectNode : public ASTNode {
public:
  NewObjectNode(std::string &_name, std::vector<ASTNode *> ids,
                std::string &_which_constructor);
  ASTResult eval(RefEnv *env);

private:
  std::string _name;
  std::vector<ASTNode *> ids;
  std::string _which_constructor;
};
#endif