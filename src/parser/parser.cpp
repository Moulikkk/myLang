#include <stdexcept>
#include <string>
#include "parser.h"

Parser::Parser(Lexer &l) : lexer(l)
{
    curr_Token = lexer.nextToken();
    peek_Token = lexer.nextToken();
}

void Parser::advance()
{
    curr_Token = peek_Token;
    peek_Token = lexer.nextToken();
}

void Parser::consume(TokenType expectedType)
{
    if (curr_Token.type != expectedType)
    {
        throw std::runtime_error("Unexpected token");
    }

    advance();
}

std::unique_ptr<ASTNode> Parser::parseFactor()
{
    if (curr_Token.type == NUMBER)
    {
        int value = std::stoi(curr_Token.value);
        consume(NUMBER);
        
        return  std::make_unique<NumberNode>(value);
    }

    if (curr_Token.type == LPAREN)
    {
        consume(LPAREN);

       unique_ptr<ASTNode> result = parseExpression();

        consume(RPAREN); 

        return result;
    }

    if (curr_Token.type == IDENTIFIER)
    {   
        string value = curr_Token.value;
        consume(IDENTIFIER);
        return std::make_unique<VariableNode>(value);

    }

    throw std::runtime_error("Expected number or '('");
}

std::unique_ptr<ASTNode> Parser::parseTerm()
{
   unique_ptr<ASTNode> result = parseFactor();

    while (curr_Token.type == STAR ||curr_Token.type == SLASH)
    {
        TokenType op = curr_Token.type;

        if (op == STAR)
        {
            consume(STAR);
            result =  make_unique<BinaryOpNode>("*",move(result),parseFactor());
        }
        else
        {
            consume(SLASH);
            result = make_unique<BinaryOpNode>("/",move(result),parseFactor());
        }   
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseExpression()
{
    unique_ptr<ASTNode> result = parseTerm();

    while (curr_Token.type == PLUS ||curr_Token.type == MINUS)
    {
        TokenType op = curr_Token.type;

        if (op == PLUS)
        {
            consume(PLUS);
            result = make_unique<BinaryOpNode>("+",move(result),parseTerm());
        }
        else 
        {
            consume(MINUS);
             result = make_unique<BinaryOpNode>("-",move(result),parseTerm());
        }
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseAssignment()
{
    unique_ptr<ASTNode> result;

    if(curr_Token.type == IDENTIFIER)
    {
        unique_ptr<ASTNode> variable = make_unique<VariableNode>(curr_Token.value);
        consume(IDENTIFIER);
        consume(EQUAL);
        unique_ptr<ASTNode> value = parseExpression();

        result = make_unique<AssignmentNode>(move(variable),move(value));
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parse()
{   
    unique_ptr<ASTNode> result;

    if (curr_Token.type == IDENTIFIER && peek_Token.type == EQUAL)
    {
        result =  parseAssignment();    
    }
    else
    {
        result = parseExpression();
    }

    if (curr_Token.type != END)
    {
        throw std::runtime_error("Unexpected token");
    }
    
    return result;
}
