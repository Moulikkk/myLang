#include <stdexcept>
#include "lexer.h"
using namespace std;

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
    else if(input[curr_position] >= '0' && input[curr_position] <= '9' )
    {
        Token Number;
        Number.type = TokenType::NUMBER;

        while(curr_position < input.size() && input[curr_position] >= '0' && input[curr_position] <= '9')
        {
            Number.value.push_back(input[curr_position]);
            curr_position++;
        }
        return Number;
    }
    else if(input[curr_position] == '(')
    {
        Token Left;
        Left.type = LPAREN;
        Left.value = "(";
        curr_position++;

        return Left;
    }
    else if(input[curr_position] == ')')
    {
        Token Right;
        Right.type = RPAREN;
        Right.value = ")";
        curr_position++;

        return Right;
    }
    else
    {
        throw std::runtime_error("Unknown character encountered");
    }
}