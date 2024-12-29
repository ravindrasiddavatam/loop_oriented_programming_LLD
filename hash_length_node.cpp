#include "hash_length_node.h"
#include "stdexcept"

HashLength::HashLength(ASTNode *node) : node(node) {}

ASTResult HashLength::eval(RefEnv *env) {
  ASTResult ret_result;
  ret_result.type = ASTResult::INT;
  ASTResult result = node->eval(env);
  if (result.type == ASTResult::ARRAY) {
    ret_result.parent_union.value.i =
        result.parent_union.value.array.array_results->size();
  } else if (result.type == ASTResult::STRING) {
    ret_result.parent_union.value.i = result.parent_union.value.s->length();
  } else {
    throw std::runtime_error("Invalid type for length!");
  }
  return ret_result;
}
