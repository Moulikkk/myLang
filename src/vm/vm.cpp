#include "vm.h"
#include <iostream>
using namespace std;

void VM::execute(Chunk chunk)
{
  int ip = 0;

  while (ip < chunk.code.size())
  {
    if (chunk.code[ip] == OP_PUSH)
    {
      ip++;
      stack.push_back(chunk.constants[chunk.code[ip]]);
      ip++;
    }
    else if (chunk.code[ip] == OP_ADD)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left + right);
      ip++;
    }
    else if (chunk.code[ip] == OP_SUB)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left - right);
      ip++;
    }
    else if (chunk.code[ip] == OP_MUL)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left * right);
      ip++;
    }
    else if (chunk.code[ip] == OP_DIV)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left / right);
      ip++;
    }
    else if (chunk.code[ip] == OP_LESS)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left < right);
      ip++;
    }
    else if (chunk.code[ip] == OP_GREATER)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left > right);
      ip++;
    }
    else if (chunk.code[ip] == OP_LESS_EQUAL)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left <= right);
      ip++;
    }
    else if (chunk.code[ip] == OP_GREATER_EQUAL)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left >= right);
      ip++;
    }
    else if (chunk.code[ip] == OP_EQUAL)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left == right);
      ip++;
    }
    else if (chunk.code[ip] == OP_NOT_EQUAL)
    {
      double right = stack.back();
      stack.pop_back();

      double left = stack.back();
      stack.pop_back();

      stack.push_back(left != right);
      ip++;
    }
    else if (chunk.code[ip] == OP_STORE)
    {
      double value = stack.back();
      stack.pop_back();

      ip++;
      int index = chunk.code[ip];

      string name = chunk.variables[index];
      variables[name] = value;

      ip++;
    }
    else if (chunk.code[ip] == OP_LOAD)
    {
      ip++;
      int index = chunk.code[ip];

      string name = chunk.variables[index];
      stack.push_back(variables[name]);

      ip++;
    }
    else if (chunk.code[ip] == OP_PRINT)
    {
      cout << stack.back();
      ip++;
    }
    else if (chunk.code[ip] == OP_HALT)
    {
      return;
    }
    else
    {
      throw std::runtime_error("Unknown opcode");
    }
  }
}