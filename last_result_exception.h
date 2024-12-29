#include "ast_node.h"
#include <exception>

class LastResultException : public std::exception {
public:
  LastResultException(const ASTResult &last_result)
      : _last_result(last_result) {}

  const char *what() const noexcept override { return "Stopexception"; }

  ASTResult last_result() const { return _last_result; }

private:
  ASTResult _last_result;
};
