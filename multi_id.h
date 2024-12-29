// File: ids.h
// Purpose: An AST Node representing a sequence of statements.
#ifndef IDS_NODE
#define IDS_NODE
#include "ast_node.h"
#include <vector>

class MultiId : public ASTNode {
public:
  virtual ASTResult eval(RefEnv *env);
  virtual void add_id(std::string &id);

private:
  std::vector<std::string> _ids;
};
#endif