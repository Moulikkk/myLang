#include <iostream>
#include "lexer.h"
using namespace std;

int main(void)
{
    Lexer l("12 + 3 * (45 - 6)");
    Token curr_Token = l.nextToken();

    while(curr_Token.type != TokenType::END)
    {
        switch (curr_Token.type)
        {
            case TokenType::NUMBER:
                cout << "[TokenType: NUMBER]  Value: " << curr_Token.value << endl;
                break;
            case TokenType::PLUS:
                cout << "[TokenType: PLUS]    Value: " << curr_Token.value << endl;
                break;
            case TokenType::MINUS:
                cout << "[TokenType: MINUS]   Value: " << curr_Token.value << endl;
                break;
            case TokenType::STAR:
                cout << "[TokenType: STAR]    Value: " << curr_Token.value << endl;
                break;
            case TokenType::SLASH:
                cout << "[TokenType: SLASH]   Value: " << curr_Token.value << endl;
                break;
            case TokenType::LPAREN:
                cout << "[TokenType: LPAREN]  Value: " << curr_Token.value << endl;
                break;
            case TokenType::RPAREN:
                cout << "[TokenType: RPAREN]  Value: " << curr_Token.value << endl;
                break;
            case TokenType::END:
                cout << "[TokenType: END]" << endl;
                break;
            default:
                cout << "[TokenType: UNKNOWN] Value: " << curr_Token.value << endl;
                break;
        }

        curr_Token = l.nextToken();
    }

    return 0;
}
