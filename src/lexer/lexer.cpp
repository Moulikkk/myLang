#include <stdexcept>
#include <cctype>
#include "lexer.h"
using namespace std;

Lexer::Lexer(string s)
{
    input = s;
}

bool Lexer::match(char expected)
{
    if (curr_position + 1 >= input.size())
    {
        return false;
    }

    if (input[curr_position + 1] != expected)
    {
        return false;
    }

    curr_position += 2;
    return true;
}

Token Lexer::nextToken()
{
    while (curr_position < input.size() && input[curr_position] == ' ')
    {
        curr_position++;
    }

    if (curr_position >= input.size())
    {
        Token End;
        End.type = TokenType::END;
        return End;
    }

    if (input[curr_position] == '+')
    {
        curr_position++;
        return {TokenType::PLUS, "+"};
    }

    if (input[curr_position] == '-')
    {
        curr_position++;
        return {TokenType::MINUS, "-"};
    }

    if (input[curr_position] == '*')
    {
        curr_position++;
        return {TokenType::STAR, "*"};
    }

    if (input[curr_position] == '/')
    {
        curr_position++;
        return {TokenType::SLASH, "/"};
    }

    if (input[curr_position] == '(')
    {
        curr_position++;
        return {TokenType::LPAREN, "("};
    }

    if (input[curr_position] == ')')
    {
        curr_position++;
        return {TokenType::RPAREN, ")"};
    }

    if(input[curr_position] == '{')
    {
        curr_position++;
        return {TokenType::LBRACE,"{"};
    }

    if(input[curr_position] == '}')
    {
        curr_position++;
        return {TokenType::LBRACE,"}"};
    }

    if (input[curr_position] == '<')
    {
        if (match('='))
        {
            return {TokenType::LESS_EQUAL, "<="};
        }

        curr_position++;
        return {TokenType::LESS, "<"};
    }

    if (input[curr_position] == '>')
    {
        if (match('='))
        {
            return {TokenType::GREATER_EQUAL, ">="};
        }

        curr_position++;
        return {TokenType::GREATER, ">"};
    }

    if (input[curr_position] == '=')
    {
        if (match('='))
        {
            return {TokenType::EQUAL_EQUAL, "=="};
        }

        curr_position++;
        return {TokenType::EQUAL, "="};
    }

    if (input[curr_position] == '!')
    {
        if (match('='))
        {
            return {TokenType::BANG_EQUAL, "!="};
        }

        throw runtime_error("Unexpected '!'");
    }

    if (isDigit(input[curr_position]))
    {
        Token Number;
        Number.type = TokenType::NUMBER;

        while (curr_position < input.size() && isDigit(input[curr_position]))
        {
            Number.value.push_back(input[curr_position]);
            curr_position++;
        }

        return Number;
    }

    if (isLetter(input[curr_position]) || input[curr_position] == '_')
    {
        Token Variable;
        Variable.type = TokenType::IDENTIFIER;

        while (curr_position < input.size() && isIdentifierChar(input[curr_position]))
        {
            Variable.value.push_back(input[curr_position]);
            curr_position++;
        }

        if(Variable.value == "if")
        {
            Variable.type  = TokenType::IF;
        }

        return Variable;
    }

    if (input[curr_position] == '\n')
    {
        curr_position++;
        return {TokenType::NEWLINE, "\\n"};
    }

    throw runtime_error("Unknown character encountered");
}