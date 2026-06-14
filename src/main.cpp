#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"

using namespace std;

int main()
{
    Lexer lexer("12 + 3 * (45 - 6)");

    Parser parser(lexer);

    int result = parser.parse();

    cout << "Result: " << result << endl;

    return 0;
}