#pragma once
#include <vector>
#include "../parser/parser.h"
using namespace std;

enum OpCode
{
    OP_PUSH,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_LESS,
    OP_GREATER,
    OP_LESS_EQUAL,
    OP_GREATER_EQUAL,
    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_STORE,
    OP_LOAD,
    OP_PRINT,
    OP_HALT
};

struct Chunk
{
    vector<int> code;
    vector<double> constants;
    vector<string> variables;
};

class Compiler
{
    Chunk chunk;
    void compile(ASTNode *node);
    int getVariableIndex(const string &name);

public:
    Chunk run(unique_ptr<ASTNode> root);
};