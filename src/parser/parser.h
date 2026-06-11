#pragma once
#include "../lexer/lexer.h" 

class Parser
{
    Lexer lexer;
    Token curr_Token;

    public: 

    Parser(Lexer &l);

    void advance();

    void consume(TokenType expectedType);

    int parseExpression();

    int parseTerm();
    
    int parseFactor();
 
};

