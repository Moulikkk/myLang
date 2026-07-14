#include "compiler.h"
#include <iostream>
using namespace std;

//helper function
int Compiler::getVariableIndex(const string& name)
{
    int index = -1;

    for(int i = 0; i < chunk.variables.size();i++)
    {
       if(name == chunk.variables[i])
        {
            index  = i;
            break;
        }
    }

    if(index == -1)
    {
        chunk.variables.push_back(name);
        index = chunk.variables.size()-1;
    }

    return index;
}
//helper function

void Compiler::compile(ASTNode* node)
{
    if(node == nullptr)
    {
        return;
    }

    ProgramNode* program = dynamic_cast<ProgramNode*>(node);
    NumberNode* num = dynamic_cast<NumberNode*>(node);
    BinaryOpNode* bin = dynamic_cast<BinaryOpNode*>(node);
    VariableNode* var = dynamic_cast<VariableNode*>(node);
    AssignmentNode* assign = dynamic_cast<AssignmentNode*>(node);

    if (program != nullptr)
    {
        for (int i = 0; i < program->statements.size(); i++)
        {
            compile(program->statements[i].get());
        }
        return;
    }

    if(num != nullptr)
    {
        chunk.constants.push_back(num->value);
        int index = chunk.constants.size() - 1;
        chunk.code.push_back(OP_PUSH);
        chunk.code.push_back(index);
        return;
    }
    else if(bin != nullptr)
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
       return;
    }
    else if(var != nullptr)
    {
        int index = getVariableIndex(var->variableName);

        chunk.code.push_back(OP_LOAD);
        chunk.code.push_back(index);
        return;
    }
    else if(assign != nullptr)
    {
        compile(assign->right.get());
        VariableNode* var = dynamic_cast<VariableNode*>(assign->left.get());

        int index = getVariableIndex(var->variableName);
        chunk.code.push_back(OP_STORE);
        chunk.code.push_back(index);
        return;
    }
    else
    {
        throw std::runtime_error("Unknown AST node");
    }
   
}



Chunk Compiler::run(unique_ptr<ASTNode> root)
{
    chunk = Chunk();
    compile(root.get());
    chunk.code.push_back(OP_HALT);

    return chunk;
}