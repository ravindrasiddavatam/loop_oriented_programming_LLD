// File: ast_node.h
// Purpose: This file contains the definition of a pure virtual class for
//          nodes in an AST. It also contains the definition of an
//          abstract result type.
// Author: Robert Lowe
#ifndef AST_NODE_H
#define AST_NODE_H
#include "map"
#include "ref_env.h"
#include <string>
#include <vector>
class RefEnv;

struct ASTResult;

class ASTNode {
public:
  // virtual destructor
  virtual ~ASTNode();

  // evaluate the node
  virtual ASTResult eval(RefEnv *env) = 0;
};

struct ASTResult {
  enum { VOID = 0, INT, REAL, STRING, ARRAY, FUNCTION_DEF, OBJECT, NEW_OBJECT } type;

  struct Value {
    int i;
    double r;
    std::string *s;
    struct {
      std::vector<std::string> *vec_strings;
      ASTNode *loop_node;
    } function;

    struct {
      std::vector<ASTNode *> *object_functions;
      std::vector<ASTNode *> *object_constructors;
      std::vector<std::string> *object_variables;
    } object;

    struct {
      std::vector<ASTResult> *array_results;
    } array;

    struct {
      RefEnv *env;
    } new_object;
  };

  union {
    Value value;
  } parent_union;

  bool is_true() const;
};

#endif