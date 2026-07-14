#pragma once
#include <string>
using namespace std;

enum TokenType
{
    NUMBER,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    LPAREN,
    RPAREN,
    IDENTIFIER,
    NEWLINE,
    END,
    EQUAL
};


struct Token
{
    TokenType type;
    string value; 
};


class Lexer
{
    string input;
    int curr_position = 0;

    public:
    Lexer(string s);
    Token nextToken();

};
