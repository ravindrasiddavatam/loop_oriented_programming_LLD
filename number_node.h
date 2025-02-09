// File: number_node.h
// Purpose: Definition of a numeric node for the AST
#ifndef NUMBER_NODE_H
#define NUMBER_NODE_H

#include "ast_node.h"
#include "lop_lexer.h"
#include <string>

class NumberNode : public ASTNode {
public:
    NumberNode(const Lexer::Token &token);
    virtual ~NumberNode();
    virtual ASTResult eval(RefEnv *env);

private:
    ASTResult _value;
};

#endif // NUMBER_NODE_H