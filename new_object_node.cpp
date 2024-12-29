#include "new_object_node.h"
#include "function_call.h"
#include <algorithm>
#include <iostream>

NewObjectNode::NewObjectNode(std::string &_name, std::vector<ASTNode *> ids,
                             std::string &_which_constructor) {
  this->_name = _name;
  this->ids = ids;
  this->_which_constructor = _which_constructor;
}

ASTResult NewObjectNode::eval(RefEnv *env) {
  ASTResult ret_result;
  ret_result.type = ASTResult::NEW_OBJECT;
  ret_result.parent_union.value.new_object.env = new RefEnv(env);

  ASTResult *result = env->lookup(_name);

  std::vector<ASTNode *> *object_functions =
      result->parent_union.value.object.object_functions;
  std::vector<ASTNode *> *object_constructors =
      result->parent_union.value.object.object_constructors;
  std::vector<std::string> *object_variables =
      result->parent_union.value.object.object_variables;

  // Evaluate functions and constructors within the new object environment
  for (int i = 0; i < object_functions->size(); i++) {
    (*object_functions)[i]->eval(ret_result.parent_union.value.new_object.env);
  }

  for (int i = 0; i < object_constructors->size(); i++) {
    (*object_constructors)[i]->eval(
        ret_result.parent_union.value.new_object.env);
  }

  // Declare object variables in the new object environment
  for (int i = 0; i < object_variables->size(); i++) {
    ret_result.parent_union.value.new_object.env->declare(
        (*object_variables)[i]);
  }

  // Evaluate the constructor function
  std::string dum = "";
  ASTNode *node = new FunctionCall(_which_constructor, ids, dum);
  ASTResult *tmp =
      ret_result.parent_union.value.new_object.env->lookup(_which_constructor);
  if (!tmp) {
    if (_which_constructor == "constructor0")
      return ret_result;
    throw std::runtime_error("No such constructor found!");
  }

  node->eval(ret_result.parent_union.value.new_object.env);

  return ret_result;
}
