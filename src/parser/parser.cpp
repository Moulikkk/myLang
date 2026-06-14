#include <stdexcept>
#include <string>
#include "parser.h"

Parser::Parser(Lexer &l) : lexer(l)
{
    curr_Token = lexer.nextToken();
}

void Parser::advance()
{
    curr_Token = lexer.nextToken();
}

void Parser::consume(TokenType expectedType)
{
    if (curr_Token.type != expectedType)
    {
        throw std::runtime_error("Unexpected token");
    }

    advance();
}

int Parser::parseFactor()
{
    if (curr_Token.type == NUMBER)
    {
        int value = std::stoi(curr_Token.value);
        consume(NUMBER);
        return value;
    }

    if (curr_Token.type == LPAREN)
    {
        consume(LPAREN);

        int value = parseExpression();

        consume(RPAREN); 

        return value;
    }

    throw std::runtime_error("Expected number or '('");
}

int Parser::parseTerm()
{
    int result = parseFactor();

    while (curr_Token.type == STAR ||curr_Token.type == SLASH)
    {
        TokenType op = curr_Token.type;

        if (op == STAR)
        {
            consume(STAR);
            result *= parseFactor();
        }
        else
        {
            consume(SLASH);
            result /= parseFactor();
        }   
    }

    return result;
}

int Parser::parseExpression()
{
    int result = parseTerm();

    while (curr_Token.type == PLUS ||curr_Token.type == MINUS)
    {
        TokenType op = curr_Token.type;

        if (op == PLUS)
        {
            consume(PLUS);
            result += parseTerm();
        }
        else 
        {
            consume(MINUS);
            result -= parseTerm();
        }
    }

    return result;
}


int Parser::parse()
{
    int result = parseExpression();

    if (curr_Token.type != END)
    {
        throw std::runtime_error("Unexpected token after expression");
    }

    return result;
}