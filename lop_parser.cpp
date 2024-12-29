#include "lop_parser.h"

void CalculatorParser::next() { _cur = _lexer->next(); }

bool CalculatorParser::has(int t) { return _cur.tok == t; }

ASTNode *CalculatorParser::parse_expression() {
  if (has(CalculatorLexer::LFLOWER)) {
    return parse_loop();
  } else if (has(CalculatorLexer::IF)) {
    return parse_if();
  } else if (has(CalculatorLexer::DISPLAY)) {
    return parse_display();
  } else if (has(CalculatorLexer::READ) || has(CalculatorLexer::PROMPT) ||
             has(CalculatorLexer::INPUT)) {
    return parse_input();
  } else if (has(CalculatorLexer::FUNCTION)) {
    return parse_function_def();
  } else if (has(CalculatorLexer::STOP)) {
    next();
    return new StopNode();
  }

  return parse_assign();
}

ASTNode *CalculatorParser::parse_assign() {
  ASTNode *node = parse_comparisons();
  return parse_assign2(node);
}

ASTNode *CalculatorParser::parse_assign2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::ASSIGN)) {
    next();
    result = new AssignNode();
    result->left(left);
    result->right(parse_expression());
    return result;
  }

  return left;
}

ASTNode *CalculatorParser::parse_comparisons() {
  ASTNode *node = parse_condition();
  return parse_comparisons2(node);
}

ASTNode *CalculatorParser::parse_comparisons2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::EQ)) {
    next();
    result = new ConditionsNode("=");
  } else if (has(CalculatorLexer::NEQ)) {
    next();
    result = new ConditionsNode("<>");
  }

  if (result) {
    result->left(left);
    result->right(parse_condition());
    return parse_comparisons2(result);
  }

  return left;
}

ASTNode *CalculatorParser::parse_condition() {
  ASTNode *node = parse_sum();
  return parse_condition2(node);
}

ASTNode *CalculatorParser::parse_condition2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::LT)) {
    next();
    result = new ConditionsNode("<");
  } else if (has(CalculatorLexer::LTE)) {
    next();
    result = new ConditionsNode("<=");
  } else if (has(CalculatorLexer::GT)) {
    next();
    result = new ConditionsNode(">");
  } else if (has(CalculatorLexer::GTE)) {
    next();
    result = new ConditionsNode(">=");
  }

  if (result) {
    result->left(left);
    result->right(parse_sum());
    return parse_condition2(result);
  }

  return left;
}

ASTNode *CalculatorParser::parse_function_def() {
  std::string id;
  if (has(CalculatorLexer::FUNCTION)) {
    next();
  } else {
    throw std::runtime_error("Expected function");
  }

  if (has(CalculatorLexer::ID)) {
    id = _cur.lexeme;
    next();
  } else {
    throw std::runtime_error("Expected ID!");
  }

  if (has(CalculatorLexer::LPAREN)) {
    next();
  } else {
    throw std::runtime_error("Expected LPAREN");
  }

  std::vector<std::string> ids;
  while (has(CalculatorLexer::ID)) {
    ids.push_back(_cur.lexeme);
    next();
    if (has(CalculatorLexer::COMMA)) {
      next();
    }
  }

  if (has(CalculatorLexer::RPAREN)) {
    next();
  } else {
    throw std::runtime_error("Expected RPAREN");
  }

  ASTNode *loop = parse_loop();
  id = id + std::to_string(ids.size());
  FunctionRef *node = new FunctionRef(id, ids, loop);

  return node;
}

ASTNode *CalculatorParser::parse_loop() {
  if (has(CalculatorLexer::LFLOWER)) {
    next(); // consume {
  } else {
    throw std::runtime_error("Expected Left Flower Bracket!");
  }

  StatementsNode *stmts_node = new StatementsNode();

  while (!has(CalculatorLexer::RFLOWER)) {
    stmts_node->add_statement(parse_expression());
  }

  LoopNode *node = new LoopNode(stmts_node);

  if (has(CalculatorLexer::RFLOWER)) {
    next(); // consume }
  } else {
    throw std::runtime_error("Expected Right Flower Bracket!");
  }

  return node;
}

ASTNode *CalculatorParser::parse_display() {
  next();
  return new DisplayNode(parse_sum());
}

ASTNode *CalculatorParser::parse_input() {
  ASTNode *child = nullptr;
  if (has(CalculatorLexer::PROMPT)) {
    next();
    ASTNode *node = nullptr;
    if (has(CalculatorLexer::STRING)) {
      node = new StringNode(_cur);
      next();
    } else {
      throw std::runtime_error("Expected ID!");
    }

    if (has(CalculatorLexer::ID)) {
      child = new InputNode(node, _cur.lexeme);
      next();
    } else {
      throw std::runtime_error("Expected ID!");
    }

  } else if (has(CalculatorLexer::READ)) {
    next();
    ASTNode *node = nullptr;
    child = new InputNode(node, _cur.lexeme);
    next();
  } else if (has(CalculatorLexer::INPUT)) {
    next();
    ASTNode *node = nullptr;
    if (has(CalculatorLexer::STRING)) {
      node = new StringNode(_cur);
      next();
    } else {
      if (has(CalculatorLexer::ID)) {
        child = new InputNode(nullptr, _cur.lexeme);
        next();
        return child;
      } else {
        throw std::runtime_error("Expected ID for Input!");
      }
    }

    if (has(CalculatorLexer::SEMI)) {
      next();
    } else {
      throw std::runtime_error("Expected Semicolon!");
    }

    if (has(CalculatorLexer::ID)) {
      child = new InputNode(node, _cur.lexeme);
      next();
    } else {
      throw std::runtime_error("Expected ID!");
    }
  }
  return child;
}

ASTNode *CalculatorParser::parse_expression2(ASTNode *left) {
  if (has(CalculatorLexer::ASSIGN)) {
    next();
    AssignNode *node = new AssignNode();
    node->left(left);
    node->right(parse_expression());
    return node;
  } else if (has(CalculatorLexer::LT)) {
  }

  return parse_sum2(left);
}

ASTNode *CalculatorParser::parse_sum() {
  ASTNode *node = parse_term();
  return parse_sum2(node);
}

ASTNode *CalculatorParser::parse_sum2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::ADD)) {
    next(); // consume ADD
    result = new AddNode();
  } else if (has(CalculatorLexer::SUB)) {
    next(); // consume SUB
    result = new SubtractNode();
  }

  if (result) {
    result->left(left);
    result->right(parse_term());
    return parse_sum2(result);
  }

  return left; // epsilon
}

ASTNode *CalculatorParser::parse_term() {
  ASTNode *node = parse_factor();
  return parse_term2(node);
}

ASTNode *CalculatorParser::parse_term2(ASTNode *left) {
  BinopNode *result = nullptr;

  if (has(CalculatorLexer::MUL)) {
    next(); // consume MUL
    result = new MultiplyNode();
  } else if (has(CalculatorLexer::DIV)) {
    next(); // consume DIV
    result = new DivideNode();
  }

  if (result) {
    result->left(left);
    result->right(parse_term());
    return parse_term2(result);
  }

  return left; // epsilon
}

ASTNode *CalculatorParser::parse_factor() {
  ASTNode *node = parse_unary();
  return parse_factor2(node);
}

ASTNode *CalculatorParser::parse_factor2(ASTNode *left) {
  if (has(CalculatorLexer::POW)) {
    next();
    ASTNode *right = parse_unary();
    PowNode *node = new PowNode();
    node->left(left);
    node->right(right);
    return parse_factor2(node);
  }

  return left;
}

ASTNode *CalculatorParser::parse_unary() {
  if (has(CalculatorLexer::ADD)) {
    next();
    UnaryNode *node = new UnaryNode(parse_expression(), '+');
    return node;
  } else if (has(CalculatorLexer::SUB)) {
    next();
    UnaryNode *node = new UnaryNode(parse_expression(), '-');
    return node;
  } else if (has(CalculatorLexer::HASH)) {
    next();
    HashLength *node = new HashLength(parse_expression());
    return node;
  }

  return parse_access();
}

// <Exponent> ::= INT
//                | REAL
//                | LPAR <Expression> RPAR
//                | < Ref >
ASTNode *CalculatorParser::parse_access() {
  if (has(CalculatorLexer::INT) || has(CalculatorLexer::REAL)) {
    ASTNode *node = new NumberNode(_cur);
    next();
    return node;
  } else if (has(CalculatorLexer::STRING)) {
    ASTNode *node = new StringNode(_cur);
    next();
    return node;
  } else if (has(CalculatorLexer::LT)) {
    next();
    std::vector<ASTNode *> nodes;
    while (!has(CalculatorLexer::GT)) {
      nodes.push_back(parse_access());
    }
    if (has(CalculatorLexer::GT)) {
      next();
    } else {
      throw std::runtime_error("Expected >");
    }
    ASTNode *node = new ArrayNode(nodes);
    return node;
  } else if (has(CalculatorLexer::NEW)) {
    next();
    if (!has(CalculatorLexer::ID)) {
      throw std::runtime_error("Expected ID when creating a new object!");
    }

    std::string id = _cur.lexeme;
    next();
    if (has(CalculatorLexer::LPAREN)) {
      next();

      std::vector<ASTNode *> nodes;
      while (!has(CalculatorLexer::RPAREN)) {
        nodes.push_back(parse_expression());
        if (has(CalculatorLexer::COMMA)) {
          next();
        }
      }

      if (has(CalculatorLexer::RPAREN)) {
        next();
      } else {
        throw std::runtime_error("Expected RPAREN");
      }

      std::string which_constructor =
          "constructor" + std::to_string(nodes.size());
      ASTNode *node = new NewObjectNode(id, nodes, which_constructor);
      return node;
    } else {
      throw std::runtime_error("Expected LPAREN");
    }
  } else if (has(CalculatorLexer::LPAREN)) {
    next();
    ASTNode *node = parse_expression();
    if (!has(CalculatorLexer::RPAREN)) {
      throw std::runtime_error("Expected ')'");
    }
    next();
    return node;
  } else {
    return parse_ref();
  }
}

ASTNode *CalculatorParser::parse_constructor() {
  next();
  if (has(CalculatorLexer::LPAREN)) {
    next();
  } else {
    throw std::runtime_error("Expected LPAREN!");
  }

  std::vector<std::string> ids;
  while (has(CalculatorLexer::ID)) {
    ids.push_back(_cur.lexeme);
    next();
    if (has(CalculatorLexer::COMMA)) {
      next();
    }
  }

  if (has(CalculatorLexer::RPAREN)) {
    next();
  } else {
    throw std::runtime_error("Expected RPAREN!");
  }

  ASTNode *loop = parse_loop();
  std::string id = "constructor" + std::to_string(ids.size());
  FunctionRef *node = new FunctionRef(id, ids, loop);
  return node;
}

ASTNode *CalculatorParser::parse_object_def(std::string &id) {
  if (has(CalculatorLexer::LCLOSE)) {
    next();
  } else {
    throw std::runtime_error("Expected LCLOSE");
  }

  std::vector<std::string> ids;
  std::vector<ASTNode *> function_nodes;
  std::vector<ASTNode *> constructor_nodes;

  while (!has(CalculatorLexer::RCLOSE)) {
    if (has(CalculatorLexer::CONSTRUCTOR)) {
      constructor_nodes.push_back(parse_constructor());
    } else if (has(CalculatorLexer::FUNCTION)) {
      function_nodes.push_back(parse_function_def());
    } else if (has(CalculatorLexer::PIPE)) {
      if (has(CalculatorLexer::PIPE)) {
        next();
      } else {
        throw std::runtime_error("Expected PIPE");
      }
      while (has(CalculatorLexer::ID)) {
        ids.push_back(_cur.lexeme);
        next();
      }
      if (has(CalculatorLexer::PIPE)) {
        next();
      } else {
        throw std::runtime_error("Expected PIPE");
      }
    } else {
      throw std::runtime_error("Invalid Object Statement");
    }
  }

  if (has(CalculatorLexer::RCLOSE)) {
    next();
  } else {
    throw std::runtime_error("Expected RCLOSE");
  }

  ASTNode *node = new ObjectNode(id, ids, function_nodes, constructor_nodes);
  return node;
}

//< Ref >        ::= ID
ASTNode *CalculatorParser::parse_ref() {
  // detect an error
  if (!has(CalculatorLexer::ID)) {
    throw std::runtime_error("Expected ID");
  }

  std::string id = _cur.lexeme;
  next();
  if (has(CalculatorLexer::LPAREN)) {
    next();
    std::vector<ASTNode *> nodes;
    while (!has(CalculatorLexer::RPAREN)) {
      nodes.push_back(parse_expression());
      if (has(CalculatorLexer::COMMA)) {
        next();
      }
    }
    if (has(CalculatorLexer::RPAREN)) {
      next();
    } else {
      throw std::runtime_error("Expected RPAREN");
    }
    id = id + std::to_string(nodes.size());
    std::string dummy = "";
    ASTNode *node = new FunctionCall(id, nodes, dummy);
    return node;
  } else if (has(CalculatorLexer::COLON)) {
    next();
    if (has(CalculatorLexer::LCLOSE)) {
      ASTNode *node = parse_object_def(id);
      return node;
    } else if (has(CalculatorLexer::ID)) {
      std::string id2 = _cur.lexeme;
      next();
      if (has(CalculatorLexer::LPAREN)) {
        next();
        std::vector<ASTNode *> nodes;
        while (!has(CalculatorLexer::RPAREN)) {
          nodes.push_back(parse_expression());
          if (has(CalculatorLexer::COMMA)) {
            next();
          }
        }
        if (has(CalculatorLexer::RPAREN)) {
          next();
        } else {
          throw std::runtime_error("Expected RPAREN");
        }
        id2 = id2 + std::to_string(nodes.size());
        ASTNode *node = new FunctionCall(id2, nodes, id);
        return node;
      }
      ASTNode *node = new RefNode(id2, id);
      return node;
    }
  }
  std::string tmp = "";
  ASTNode *node = new RefNode(id, tmp);
  return node;
}

ASTNode *CalculatorParser::parse_id() {
  if (!has(CalculatorLexer::ID)) {
    throw std::runtime_error("Expected ID");
  }

  std::string dum = "";
  ASTNode *node = new RefNode(_cur.lexeme, dum);
  next();
  return node;
}

ASTNode *CalculatorParser::parse(CalculatorLexer *lexer) {
  _lexer = lexer;
  next();

  ASTNode *result = parse_statements();
  if (_cur.tok != CalculatorLexer::EOI) {
    throw std::runtime_error("Unexpected tokens at the end of expression");
  }
  return result;
}

ASTNode *CalculatorParser::parse_if() {
  if (has(CalculatorLexer::IF)) {
    next();
  } else {
    throw std::runtime_error("Expected IF");
  }

  ASTNode *cond = parse_expression();

  if (has(CalculatorLexer::THEN)) {
    next();
  } else {
    throw std::runtime_error("Expected THEN");
  }

  ASTNode *then = parse_expression();

  IfNode *node = new IfNode();
  node->left(cond);
  node->right(then);

  return node;
}

ASTNode *CalculatorParser::parse_statements() {
  StatementsNode *node = new StatementsNode();

  do {
    node->add_statement(parse_expression());
  } while (!has(CalculatorLexer::EOI));

  return node;
}
