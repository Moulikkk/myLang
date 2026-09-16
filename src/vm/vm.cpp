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
    else if(chunk.code[ip] == OP_JUMP)
    {
      ip++;
      int destination = chunk.code[ip];
      ip = destination;
    }
    else if(chunk.code[ip] == OP_JUMP_IF_FALSE)
    {
      double condition = stack.back();
      stack.pop_back();

      ip++;

      int destination = chunk.code[ip];

      if(!condition)
      {
        ip = destination;
      }
      else
      {
        ip++;
      }
    }
    else if (chunk.code[ip] == OP_STORE)
    {
      double value = stack.back();
      stack.pop_back();

      ip++;
      int index = chunk.code[ip];

      string name = chunk.variables[index];

      if (callStack.empty())
      {
        variables[name] = value;
      }
      else
      {
        callStack.back().variables[name] = value;
      }

      ip++;
    }
    else if (chunk.code[ip] == OP_LOAD)
    {
      ip++;
      int index = chunk.code[ip];

      string name = chunk.variables[index];

      if (callStack.empty())
      {
        stack.push_back(variables[name]);
      }
      else
      {
        stack.push_back(callStack.back().variables[name]);
      }

      ip++;
    }
    else if (chunk.code[ip] == OP_CALL)
    {
      ip++;

      int functionIndex = chunk.code[ip];

      FunctionInfo function = chunk.functions[functionIndex];

      CallFrame frame;

      frame.returnAddress = ip + 1;

      for (int i = function.parameterCount - 1; i >= 0; i--)
      {
        double argument = stack.back();
        stack.pop_back();

        frame.variables[function.parameters[i]] = argument;
      }

      callStack.push_back(frame);

      ip = function.address;
    }
    else if (chunk.code[ip] == OP_RETURN)
    {
      double returnValue = stack.back();
      stack.pop_back();

      int returnAddress = callStack.back().returnAddress;

      callStack.pop_back();

      stack.push_back(returnValue);

      ip = returnAddress;
    }
    else if (chunk.code[ip] == OP_PRINT)
    {
      cout << stack.back() << endl;
      stack.pop_back();
      ip++;
    }
    else if (chunk.code[ip] == OP_HALT)
    {
      return;
    }
    else
    {
      throw runtime_error("Unknown opcode");
    }
  }
}