#include "compiler.h"
#include <iostream>
using namespace std;

void Compiler::compile(ASTNode* node)
{
    if(node == nullptr)
    {
        return;
    }

    NumberNode* num = dynamic_cast<NumberNode*>(node);

    if(num != nullptr)
    {
        chunk.constants.push_back(num->value);
        int index = chunk.constants.size() - 1;
        chunk.code.push_back(OP_PUSH);
        chunk.code.push_back(index);
    }

    BinaryOpNode* bin = dynamic_cast<BinaryOpNode*>(node);

    if(bin != nullptr)
    {
        compile(bin->left.get());
        compile(bin->right.get());

       if(bin->op == "+")
       {
            chunk.code.push_back(OP_ADD);
       }
       else if(bin->op == "-")
       {
            chunk.code.push_back(OP_SUB);
       }
       else if(bin->op == "*")
       {
            chunk.code.push_back(OP_MUL);
       }
       else if(bin->op == "/")
       {
            chunk.code.push_back(OP_DIV);
       }
       else
       {
         cout << "Error -> unkown operator - \"" << bin->op << "\"";
       }
    }
}

Chunk Compiler::run(unique_ptr<ASTNode> root)
{
    chunk = Chunk();
    compile(root.get());
    chunk.code.push_back(OP_PRINT);
    chunk.code.push_back(OP_HALT);

    return chunk;
}