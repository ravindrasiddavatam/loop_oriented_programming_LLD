#include "object_node.h"
#include "ast_node.h"
#include "iostream"
#include "lop_lexer.h"
#include <stdexcept>

ObjectNode::ObjectNode(std::string &_name, std::vector<std::string> ids,
                       std::vector<ASTNode *> function_nodes,
                       std::vector<ASTNode *> constructor_nodes) {
  this->_name = _name;
  this->ids = ids;
  this->function_nodes = function_nodes;
  this->constructor_nodes = constructor_nodes;
}

ASTResult ObjectNode::eval(RefEnv *env) {
  ASTResult result;
  env->declare(_name);
  ASTResult *tmp = env->lookup(_name);
  result.type = ASTResult::OBJECT;
  result.parent_union.value.object.object_variables = &this->ids;
  result.parent_union.value.object.object_functions = &this->function_nodes;
  result.parent_union.value.object.object_constructors =
      &this->constructor_nodes;
  *tmp = result;
  return result;
}
