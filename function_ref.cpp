#include "function_ref.h"
#include <iostream>

FunctionRef::FunctionRef(std::string &_name, std::vector<std::string> ids,
                         ASTNode *loop_node)
    : _name(_name), ids(ids), loop_node(loop_node) {}

ASTResult FunctionRef::eval(RefEnv *env) {
  ASTResult result;
  env->declare(_name);
  ASTResult *tmp = env->lookup(_name);
  result.type = ASTResult::FUNCTION_DEF;
  result.parent_union.value.function.vec_strings = &ids;
  result.parent_union.value.function.loop_node = loop_node;
  *tmp = result;
  return result;
}
