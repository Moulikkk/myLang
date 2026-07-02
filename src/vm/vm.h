#pragma once
#include <vector>
#include "../compiler/compiler.h"
using namespace std;

class VM
{
    vector<double> stack;

    public:
    void execute(Chunk chunk);
};