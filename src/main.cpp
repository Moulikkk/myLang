#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"

using namespace std;

void printAST(ASTNode* node, int indent)
{
    NumberNode* num = dynamic_cast<NumberNode*>(node);

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

int main()
{
    Lexer lexer("12 + 3 * (45 - 6)");

    Parser parser(lexer);

    std::unique_ptr<ASTNode> root = parser.parse();

    printAST(root.get(), 0);

    return 0;
}