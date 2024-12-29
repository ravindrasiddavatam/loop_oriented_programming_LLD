#include "ref_node.h"
#include "string"
#include <iostream>
#include <sstream>

RefNode::RefNode(const std::string &_name, std::string &obj) {
  this->_name = _name;
  this->obj = obj;
}

RefNode::~RefNode() {}

std::vector<std::string> splitString(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;
  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

ASTResult RefNode::eval(RefEnv *env) {
  if (obj.length() > 0) {
    if (this->obj == "my") {
      if (!env->parent()) {
        throw std::runtime_error("Cannot access parent environment. Reference "
                                 "'my' used without parent.");
      }
      env = env->parent();
    } else {
      if (this->obj.find('_') != std::string::npos) {
        std::vector<std::string> result_split = splitString(this->obj, '_');
        if (result_split.size() == 2) {
          ASTResult *tmp = env->lookup(result_split[1]);
          if (tmp->type != ASTResult::INT && tmp->type != ASTResult::REAL) {
            throw std::runtime_error(
                "Array indices must be integers or real numbers.");
          }
          int i = tmp->type == ASTResult::INT ? tmp->parent_union.value.i
                                              : (int)tmp->parent_union.value.r;
          i = i - 1;
          ASTResult *res = env->lookup(result_split[0]);
          if (res->type != ASTResult::ARRAY) {
            throw std::runtime_error("Object is not an array.");
          }

          if (i >= (*res->parent_union.value.array.array_results).size()) {
            throw std::runtime_error("Index out of bounds for array.");
          }
          env = (*res->parent_union.value.array.array_results)[i]
                    .parent_union.value.new_object.env;
        }
      } else {
        ASTResult *tmp = env->lookup(this->obj);
        if (!tmp) {
          throw std::runtime_error("Object referenced does not exist.");
        }
        env = tmp->parent_union.value.new_object.env;
      }
    }
  }

  if (this->_name.find('_') != std::string::npos) {
    std::vector<std::string> result = splitString(this->_name, '_');
    if (result.size() == 2) {
      ASTResult *tmp = env->lookup(result[1]);
      if (tmp->type != ASTResult::INT && tmp->type != ASTResult::REAL) {
        throw std::runtime_error(
            "Array indices must be integers or real numbers.");
      }
      int i = tmp->type == ASTResult::INT ? tmp->parent_union.value.i
                                          : (int)tmp->parent_union.value.r;
      i = i - 1;
      ASTResult *res = env->lookup(result[0]);
      if (res->type != ASTResult::ARRAY) {
        throw std::runtime_error("Object is not an array.");
      }

      if (i >= (*res->parent_union.value.array.array_results).size()) {
        throw std::runtime_error("Index out of bounds for array.");
      }
      return (*res->parent_union.value.array.array_results)[i];
    }
  }
  ASTResult *result = env->lookup(this->_name);

  if (!result) {
    std::cerr << "Error: Variable " << this->_name << " not found."
              << std::endl;
    ASTResult error;
    error.type = ASTResult::VOID;
    return error;
  }

  return *result;
}

void RefNode::assign(RefEnv *env, ASTResult _value) {
  if (obj.length() > 0) {
    if (this->obj == "my") {
      if (!env->parent()) {
        throw std::runtime_error("Cannot access parent environment. Reference "
                                 "'my' used without parent.");
      }
      env = env->parent();
    } else {
      if (this->obj.find('_') != std::string::npos) {
        std::vector<std::string> result_split = splitString(this->obj, '_');
        if (result_split.size() == 2) {
          ASTResult *tmp = env->lookup(result_split[1]);
          if (tmp->type != ASTResult::INT && tmp->type != ASTResult::REAL) {
            throw std::runtime_error(
                "Array indices must be integers or real numbers.");
          }
          int i = tmp->type == ASTResult::INT ? tmp->parent_union.value.i
                                              : (int)tmp->parent_union.value.r;
          i = i - 1;
          ASTResult *res = env->lookup(result_split[0]);
          if (res->type != ASTResult::ARRAY) {
            throw std::runtime_error("Object is not an array.");
          }

          if (i >= (*res->parent_union.value.array.array_results).size()) {
            throw std::runtime_error("Index out of bounds for array.");
          }
          env = (*res->parent_union.value.array.array_results)[i]
                    .parent_union.value.new_object.env;
        }
      } else {
        ASTResult *tmp = env->lookup(this->obj);
        if (!tmp) {
          throw std::runtime_error("Object referenced does not exist.");
        }
        env = tmp->parent_union.value.new_object.env;
      }
    }
  }

  if (this->_name.find('_') != std::string::npos) {
    std::vector<std::string> result = splitString(this->_name, '_');
    if (result.size() == 2) {
      ASTResult *tmp = env->lookup(result[1]);
      if (tmp->type != ASTResult::INT && tmp->type != ASTResult::REAL) {
        throw std::runtime_error(
            "Array indices must be integers or real numbers.");
      }
      int i = tmp->type == ASTResult::INT ? tmp->parent_union.value.i
                                          : (int)tmp->parent_union.value.r;
      i = i - 1;
      ASTResult *res = env->lookup(result[0]);
      if (res->type != ASTResult::ARRAY) {
        throw std::runtime_error("Object is not an array.");
      }

      if (i >= (*res->parent_union.value.array.array_results).size()) {
        throw std::runtime_error("Index out of bounds for array.");
      }
      (*res->parent_union.value.array.array_results)[i] = _value;
      return;
    }
  }

  ASTResult *result = env->lookup(this->_name);
  if (!result) {
    env->declare(this->_name);
    result = env->lookup(this->_name);
  }

  *result = _value;
}
