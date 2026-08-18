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
    LESS,
    GREATER,
    LESS_EQUAL,
    GREATER_EQUAL,
    EQUAL_EQUAL,
    BANG_EQUAL,
    IDENTIFIER,
    IF,
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
    bool match(char expected);
};

// helper functions

inline bool isLetter(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

inline bool isDigit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

inline bool isIdentifierChar(char c)
{
    return (isLetter(c) || isDigit(c) || c == '_');
}

// helper function
