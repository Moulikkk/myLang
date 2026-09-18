#include <iostream>
#include <fstream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "compiler/compiler.h"
#include "vm/vm.h"

using namespace std;

// only for debugging
void printAST(ASTNode* node, int indent)
{
    NumberNode* num = dynamic_cast<NumberNode*>(node);

    if(node == nullptr)
    {
        return;
    }

    if (num != nullptr)
    {
        for (int i = 0; i < indent; i++)
        {
            cout << "  ";
        }

        cout << "NUMBER: " << num->value << endl;
        return;
    }

    BinaryOpNode* bin = dynamic_cast<BinaryOpNode*>(node);

    if (bin != nullptr)
    {
        for (int i = 0; i < indent; i++)
        {
            cout << "  ";
        }

        cout << "OP: " << bin->op << endl;

        printAST(bin->left.get(), indent + 1);
        printAST(bin->right.get(), indent + 1);
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Usage: neos <file.ns>" << endl;
        return 1;
    }

    ifstream file(argv[1]);

    if (!file.is_open())
    {
        cout << "Error: could not open file '" << argv[1] << "'" << endl;
        return 1;
    }

    string source(istreambuf_iterator<char>(file), {});

    Lexer lexer(source);
    Parser parser(lexer);
    Compiler compiler;
    VM vm;

    Chunk chunk = compiler.run(parser.parse());
    vm.execute(chunk);

    return 0;
}