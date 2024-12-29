#include "multi_id.h"

ASTResult MultiId::eval(RefEnv *env) {
  for (std::string id : _ids) {
    ASTResult result;
    env->declare(id);
    ASTResult *tmp = env->lookup(id);
    // We will derieve these types later when we actually call the function
    result.type = ASTResult::VOID;
    *tmp = result;
  }
  ASTResult result;
  result.type = ASTResult::VOID;
  return result;
}

void MultiId::add_id(std::string &id) { _ids.push_back(id); }
