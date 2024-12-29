// File: ref_node.h
// Purpose: This file contains the definition of the reference node.
#ifndef REF_NODE_H
#define REF_NODE_H
#include "ast_node.h"
#include <string>

class RefNode : public ASTNode {
public:
  // Constructor and Destructor
  RefNode(const std::string &_name, std::string &obj);
  virtual ~RefNode();

  // Evaluate the node
  virtual ASTResult eval(RefEnv *env);

  // Assign a value to the reference
  void assign(RefEnv *env, ASTResult _value);

private:
  std::string _name;
  std::string obj;
};
#endif