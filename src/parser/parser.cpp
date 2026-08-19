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

        return std::make_unique<NumberNode>(value);
    }

    if (curr_Token.type == LPAREN)
    {
        consume(LPAREN);

        unique_ptr<ASTNode> result = parseComparison();

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

    while (curr_Token.type == STAR || curr_Token.type == SLASH)
    {
        TokenType op = curr_Token.type;

        if (op == STAR)
        {
            consume(STAR);
            result = make_unique<BinaryOpNode>("*", move(result), parseFactor());
        }
        else
        {
            consume(SLASH);
            result = make_unique<BinaryOpNode>("/", move(result), parseFactor());
        }
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseExpression()
{
    unique_ptr<ASTNode> result = parseTerm();

    while (curr_Token.type == PLUS || curr_Token.type == MINUS)
    {
        TokenType op = curr_Token.type;

        if (op == PLUS)
        {
            consume(PLUS);
            result = make_unique<BinaryOpNode>("+", move(result), parseTerm());
        }
        else
        {
            consume(MINUS);
            result = make_unique<BinaryOpNode>("-", move(result), parseTerm());
        }
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseComparison()
{
    std::unique_ptr<ASTNode> result = parseExpression();

    while (curr_Token.type == LESS || curr_Token.type == GREATER || curr_Token.type == LESS_EQUAL || curr_Token.type == GREATER_EQUAL || curr_Token.type == EQUAL_EQUAL || curr_Token.type == BANG_EQUAL)
    {
        TokenType op = curr_Token.type;

        if (op == LESS)
        {
            consume(LESS);
            result = std::make_unique<BinaryOpNode>("<", std::move(result), parseExpression());
        }
        else if (op == GREATER)
        {
            consume(GREATER);
            result = std::make_unique<BinaryOpNode>(">", std::move(result), parseExpression());
        }
        else if (op == LESS_EQUAL)
        {
            consume(LESS_EQUAL);
            result = std::make_unique<BinaryOpNode>("<=", std::move(result), parseExpression());
        }
        else if (op == GREATER_EQUAL)
        {
            consume(GREATER_EQUAL);
            result = std::make_unique<BinaryOpNode>(">=", std::move(result), parseExpression());
        }
        else if (op == EQUAL_EQUAL)
        {
            consume(EQUAL_EQUAL);
            result = std::make_unique<BinaryOpNode>("==", std::move(result), parseExpression());
        }
        else
        {
            consume(BANG_EQUAL);
            result = std::make_unique<BinaryOpNode>("!=", std::move(result), parseExpression());
        }
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseAssignment()
{
    unique_ptr<ASTNode> result;

    if (curr_Token.type == IDENTIFIER)
    {
        unique_ptr<ASTNode> variable = make_unique<VariableNode>(curr_Token.value);
        consume(IDENTIFIER);
        consume(EQUAL);
        unique_ptr<ASTNode> value = parseComparison();

        result = make_unique<AssignmentNode>(move(variable), move(value));
    }

    return result;
}

std::unique_ptr<ASTNode> Parser::parseIf()
{
    consume(IF);

    consume(LPAREN);
    std::unique_ptr<ASTNode> condition = parseComparison();
    consume(RPAREN);
    
    consume(LBRACE);

    ProgramNode body;

    while(curr_Token.type != RBRACE)
    {
        body.statements.push_back(parseStatement());
    }

    return std::make_unique<IfNode>(std::move(condition),body);
}

std::unique_ptr<ASTNode> Parser::parseStatement()
{
    if(curr_Token.type == IF)
    {
        return parseIf();
    }
    else if(curr_Token.type == IDENTIFIER )
    {
        if(peek_Token.type == EQUAL)
        {
           return parseAssignment();
        }
        else
        {
            return parseComparison();  
        }   
    }
    else
    {
       return parseComparison();
    }
}

std::unique_ptr<ASTNode> Parser::parse()
{
    std::unique_ptr<ProgramNode> program = std::make_unique<ProgramNode>();

    while (curr_Token.type != END)
    {
        if (curr_Token.type == NEWLINE)
        {
            consume(NEWLINE);
            continue;
        }

        program->statements.push_back(parseStatement());

        if (curr_Token.type == NEWLINE)
        {
            consume(NEWLINE);
        }
    }

    return program;
}
