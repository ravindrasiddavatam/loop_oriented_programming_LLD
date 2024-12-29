#include "array_node.h"

ArrayNode::ArrayNode(std::vector<ASTNode *> nodes) : nodes(nodes) {}

ASTResult ArrayNode::eval(RefEnv *env) {
  ASTResult ret_result;
  ret_result.type = ASTResult::ARRAY;
  ret_result.parent_union.value.array.array_results =
      new std::vector<ASTResult>();

  for (const auto &node : nodes) {
    ret_result.parent_union.value.array.array_results->push_back(
        node->eval(env));
  }

  return ret_result;
}
