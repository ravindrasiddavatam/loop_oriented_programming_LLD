#include "stop_node.h"
#include "iostream"

const char *StopException::what() { return "Loopless stop encountered."; }

ASTResult StopNode::eval(RefEnv *env) { throw StopException(); }