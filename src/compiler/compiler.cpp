#include "compiler.h"
#include <iostream>
using namespace std;

// helper function
int Compiler::getVariableIndex(const string &name)
{
    int index = -1;

    for (int i = 0; i < chunk.variables.size(); i++)
    {
        if (name == chunk.variables[i])
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        chunk.variables.push_back(name);
        index = chunk.variables.size() - 1;
    }

    return index;
}
// helper function

void Compiler::compile(ASTNode *node)
{
    if (node == nullptr)
    {
        return;
    }

    ProgramNode *program = dynamic_cast<ProgramNode *>(node);
    NumberNode *num = dynamic_cast<NumberNode *>(node);
    BinaryOpNode *bin = dynamic_cast<BinaryOpNode *>(node);
    VariableNode *var = dynamic_cast<VariableNode *>(node);
    AssignmentNode *assign = dynamic_cast<AssignmentNode *>(node);
    IfNode *ifNode = dynamic_cast<IfNode *>(node);
    WhileNode *whileNode = dynamic_cast<WhileNode *>(node);

    if (program != nullptr)
    {
        for (int i = 0; i < program->statements.size(); i++)
        {
            compile(program->statements[i].get());
        }
        return;
    }

    else if (num != nullptr)
    {
        chunk.constants.push_back(num->value);

        int index = chunk.constants.size() - 1;

        chunk.code.push_back(OP_PUSH);
        chunk.code.push_back(index);

        return;
    }

    else if (bin != nullptr)
    {
        compile(bin->left.get());
        compile(bin->right.get());

        if (bin->op == "+")
        {
            chunk.code.push_back(OP_ADD);
        }
        else if (bin->op == "-")
        {
            chunk.code.push_back(OP_SUB);
        }
        else if (bin->op == "*")
        {
            chunk.code.push_back(OP_MUL);
        }
        else if (bin->op == "/")
        {
            chunk.code.push_back(OP_DIV);
        }
        else if (bin->op == "<")
        {
            chunk.code.push_back(OP_LESS);
        }
        else if (bin->op == ">")
        {
            chunk.code.push_back(OP_GREATER);
        }
        else if (bin->op == "<=")
        {
            chunk.code.push_back(OP_LESS_EQUAL);
        }
        else if (bin->op == ">=")
        {
            chunk.code.push_back(OP_GREATER_EQUAL);
        }
        else if (bin->op == "==")
        {
            chunk.code.push_back(OP_EQUAL);
        }
        else if (bin->op == "!=")
        {
            chunk.code.push_back(OP_NOT_EQUAL);
        }
        else
        {
            throw std::runtime_error("Unknown operator: " + bin->op);
        }

        return;
    }

    else if (var != nullptr)
    {
        int index = getVariableIndex(var->variableName);

        chunk.code.push_back(OP_LOAD);
        chunk.code.push_back(index);

        return;
    }

    else if (assign != nullptr)
    {
        compile(assign->right.get());

        VariableNode *variable = dynamic_cast<VariableNode *>(assign->left.get());

        int index = getVariableIndex(variable->variableName);

        chunk.code.push_back(OP_STORE);
        chunk.code.push_back(index);

        return;
    }

    else if (ifNode != nullptr)
    {
        compile(ifNode->condition.get());

        chunk.code.push_back(OP_JUMP_IF_FALSE);

        int jumpIfFalsePosition = chunk.code.size();

        chunk.code.push_back(0);

        compile(ifNode->body.get());

        if (ifNode->elseBranch != nullptr)
        {
            chunk.code.push_back(OP_JUMP);

            int jumpPosition = chunk.code.size();

            chunk.code.push_back(0);

            chunk.code[jumpIfFalsePosition] = chunk.code.size();

            compile(ifNode->elseBranch.get());

            chunk.code[jumpPosition] = chunk.code.size();
        }
        else
        {
            chunk.code[jumpIfFalsePosition] = chunk.code.size();
        }

        return;
    }

    else if (whileNode != nullptr)
    {
        int loopStart = chunk.code.size();

        compile(whileNode->condition.get());

        chunk.code.push_back(OP_JUMP_IF_FALSE);

        int jumpIfFalsePosition = chunk.code.size();

        chunk.code.push_back(0);

        compile(whileNode->body.get());

        chunk.code.push_back(OP_JUMP);

        chunk.code.push_back(loopStart);

        chunk.code[jumpIfFalsePosition] = chunk.code.size();

        return;
    }

    throw std::runtime_error("Unknown AST node");
}

Chunk Compiler::run(unique_ptr<ASTNode> root)
{
    chunk = Chunk();
    compile(root.get());
    chunk.code.push_back(OP_HALT);

    return chunk;
}