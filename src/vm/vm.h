#pragma once
#include <vector>
#include <map>
#include "../compiler/compiler.h"
using namespace std;

class VM
{
    vector<double> stack;
    map<string, double> variables;

    public:
    void execute(Chunk chunk);
};