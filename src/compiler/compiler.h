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
    OP_PRINT,
    OP_HALT
};

struct Chunk
{
    vector<int> code;
    vector<double> constants;
};

class Compiler
{
    Chunk chunk;
    void compile(ASTNode* node);

    public:
    Chunk run(unique_ptr<ASTNode> root);
};