// File: input_node.h
// Purpose: This file contains the definition of the reference node.
#ifndef INPUT_NODE_H
#define INPUT_NODE_H
#include "ast_node.h"
#include <string>

class InputNode : public ASTNode {
public:
  // Constructor and Destructor
  InputNode(ASTNode *prompt, const std::string &_name);
  virtual ~InputNode();

  // Evaluate the node
  virtual ASTResult eval(RefEnv *env);

private:
  std::string _name;
  ASTNode *_prompt;
};
#endif