#include "lop_lexer.h"
#include "lop_parser.h"
#include "ref_env.h"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  CalculatorLexer lexer;
  CalculatorParser parser;
  std::string input, line;
  input = "";
  RefEnv global;

  if (argc == 2) {
    std::ifstream file(argv[1]);
    while (getline(file, line)) {
      input += line + " ";
    }
    lexer.input(input);
    ASTNode *tree = parser.parse(&lexer);
    ASTResult result = tree->eval(&global);
    file.close();
  } else {
    for (;;) {
      // get a line of input
      std::cout << "> ";
      std::getline(std::cin, input);
      if (!std::cout)
        break;

      // set the input string to scan
      lexer.input(input);
      ASTNode *tree = parser.parse(&lexer);
      ASTResult result = tree->eval(&global);
      delete tree;

      // print the result
      if (result.type == ASTResult::INT) {
        std::cout << result.parent_union.value.i << std::endl;
      } else if (result.type == ASTResult::REAL) {
        std::cout << result.parent_union.value.r << std::endl;
      } else if (result.type == ASTResult::STRING) {
        std::cout << *result.parent_union.value.s;
      }
    }
  }
}