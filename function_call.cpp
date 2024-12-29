#include "function_call.h"
#include "sstream"
#include <iostream>

FunctionCall::FunctionCall(std::string &_name, std::vector<ASTNode *> func,
                           std::string &obj_func)
    : _name(_name), func(func), obj_func(obj_func) {}

std::vector<std::string> splitStringTmp(const std::string &str,
                                        char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

ASTResult FunctionCall::eval(RefEnv *env) {
  RefEnv *tmpEnv = nullptr;

  if (obj_func.length() > 0) {
    if (this->obj_func.find('_') != std::string::npos) {
      std::vector<std::string> result_split =
          splitStringTmp(this->obj_func, '_');
      if (result_split.size() == 2) {
        ASTResult *tmp = env->lookup(result_split[1]);
        if (!tmp ||
            (tmp->type != ASTResult::INT && tmp->type != ASTResult::REAL)) {
          throw std::runtime_error("Array indices should be of type int!");
        }
        int i = tmp->type == ASTResult::INT ? tmp->parent_union.value.i
                                            : (int)tmp->parent_union.value.r;
        i = i - 1;
        ASTResult *res = env->lookup(result_split[0]);
        if (!res || res->type != ASTResult::ARRAY) {
          throw std::runtime_error("Not an array!");
        }
        if (i >= res->parent_union.value.array.array_results->size()) {
          throw std::runtime_error("Array index error!");
        }
        tmpEnv = (*res->parent_union.value.array.array_results)[i]
                     .parent_union.value.new_object.env;
      }
    } else {
      ASTResult *tmp = env->lookup(this->obj_func);
      if (!tmp) {
        throw std::runtime_error("Object not found!");
      }
      tmpEnv = tmp->parent_union.value.new_object.env;
    }
  } else {
    tmpEnv = new RefEnv(env);
  }

  ASTResult *result = tmpEnv->lookup(_name);
  if (!result) {
    throw std::runtime_error("Function not found!");
  }
  std::vector<std::string> ids =
      *result->parent_union.value.function.vec_strings;

  for (int i = 0; i < ids.size(); i++) {
    tmpEnv->declare(ids[i]);
    ASTResult *tmp = tmpEnv->lookup(ids[i]);
    ASTResult tmp2 = func[i]->eval(env);
    tmp->type = tmp2.type;
    if (tmp->type == ASTResult::INT) {
      tmp->parent_union.value.i = tmp2.parent_union.value.i;
    } else if (tmp->type == ASTResult::REAL) {
      tmp->parent_union.value.r = tmp2.parent_union.value.r;
    } else if (tmp->type == ASTResult::STRING) {
      tmp->parent_union.value.s = tmp2.parent_union.value.s;
    } else if (tmp->type == ASTResult::ARRAY) {
      tmp->parent_union.value.array.array_results =
          tmp2.parent_union.value.array.array_results;
    } else if (tmp->type == ASTResult::NEW_OBJECT) {
      tmp->parent_union.value.new_object.env =
          tmp2.parent_union.value.new_object.env;
    }
  }

  ASTResult result2 =
      result->parent_union.value.function.loop_node->eval(tmpEnv);
  if (!obj_func.length()) {
    delete tmpEnv;
  }
  return result2;
}
