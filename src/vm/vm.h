#pragma once
#include <vector>
#include <map>
#include "../compiler/compiler.h"
using namespace std;

struct CallFrame
{
    int returnAddress;
    map<string, double> variables;
};

class VM
{
    vector<double> stack;
    map<string, double> variables;
    vector<CallFrame> callStack;

public:
    void execute(Chunk chunk);
};