#ifndef CONDITIONS_NODE_H
#define CONDITIONS_NODE_H

#include "binop_node.h"
#include <string>

class ConditionsNode : public BinopNode {
public:
  ConditionsNode(const std::string &condition);
  virtual ~ConditionsNode();
  ASTResult apply(const ASTResult &lhs, const ASTResult &rhs);

private:
  std::string _condition;
};

#endif
