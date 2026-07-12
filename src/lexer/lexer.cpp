#include <stdexcept>
#include "lexer.h"
using namespace std;

//helper functions
bool isLetter(char c)
{   
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool isDigit(char c)
{
    return ((c >= '0') && (c <= '9'));
}

bool isIdentifierChar(char c)
{
    return (isLetter(c) || isDigit(c) || c == '_');
}
//helper function

Lexer::Lexer(string s)
{
    input = s;
}
Token Lexer::nextToken()
{

    if(curr_position >= input.size())
    {
        Token End;
        End.type = TokenType::END;

        return End;
    }
    
    while(curr_position < input.size() && input[curr_position] == ' ')
    {
        curr_position++;
    }

    if(curr_position >= input.size())
    {
        Token End;
        End.type = TokenType::END;

        return End;
    }
    else if(input[curr_position] == '+')
    {
        Token Addition;
        Addition.type = TokenType::PLUS;
        Addition.value = "+";
        curr_position++;

        return Addition;
    }
    else if(input[curr_position] == '-')
    {
        Token Subtract;
        Subtract.type = TokenType::MINUS;
        Subtract.value = "-";
        curr_position++;

        return Subtract;
    }
    else if(input[curr_position] == '*')
    {
        Token Multiply;
        Multiply.type = TokenType::STAR;
        Multiply.value = "*";
        curr_position++;

        return Multiply;
    }
    else if(input[curr_position] == '/')
    {
        Token Divide;
        Divide.type = TokenType::SLASH;
        Divide.value = "/";
        curr_position++;

        return Divide;
    }
    else if(isDigit(input[curr_position]))
    {
        Token Number;
        Number.type = TokenType::NUMBER;

        while(curr_position < input.size() && isDigit(input[curr_position]))
        {
            Number.value.push_back(input[curr_position]);
            curr_position++;
        }
        return Number;
    }
    else if(input[curr_position] == '(')
    {
        Token Left;
        Left.type = TokenType::LPAREN;
        Left.value = "(";
        curr_position++;

        return Left;
    }
    else if(input[curr_position] == ')')
    {
        Token Right;
        Right.type = TokenType::RPAREN;
        Right.value = ")";
        curr_position++;

        return Right;
    }
    else if(isLetter(input[curr_position]) || input[curr_position] == '_')
    {
        Token Variable;
        Variable.type = TokenType::IDENTIFIER;
        while(curr_position < input.size() && (isIdentifierChar(input[curr_position])))
        {
            Variable.value.push_back(input[curr_position]);
            curr_position++;
        }
        return Variable;
    }
    else if(input[curr_position] == '=')
    {
        Token equal;
        equal.type = TokenType::EQUAL;
        equal.value = "=";
        curr_position++;

        return equal;
    }
    else
    {
        throw std::runtime_error("Unknown character encountered");
    }
}