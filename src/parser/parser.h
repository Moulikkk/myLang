#pragma once
#include "../lexer/lexer.h"
#include <memory>
#include <vector>

struct ASTNode
{
    virtual ~ASTNode() = default;
};

struct NumberNode : ASTNode
{
    double value;

    NumberNode(double number)
    {
        value = number;
    }
};

struct BinaryOpNode : ASTNode
{
    string op;
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    BinaryOpNode(string s, unique_ptr<ASTNode> l, unique_ptr<ASTNode> r) : op(s), left(move(l)), right(move(r))
    {
    }
};

struct VariableNode : ASTNode
{
    string variableName;

    VariableNode(string s) : variableName(s)
    {
    }
};

struct AssignmentNode : ASTNode
{
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    AssignmentNode(unique_ptr<ASTNode> l, unique_ptr<ASTNode> r) : left(move(l)), right(move(r))
    {
    }
};

struct ProgramNode : ASTNode
{
    vector<unique_ptr<ASTNode>> statements;
};

struct IfNode : ASTNode
{
    unique_ptr<ASTNode> condition;
    unique_ptr<ProgramNode> body;

    IfNode(unique_ptr<ASTNode> c,  unique_ptr<ProgramNode>b) : condition(move(c)), body(move(b))
    {
        
    }
};

class Parser
{
    Lexer lexer;
    Token curr_Token;
    Token peek_Token;

public:
    Parser(Lexer &l);

    void advance();

    void consume(TokenType expectedType);

    std::unique_ptr<ASTNode> parseExpression();

    std::unique_ptr<ASTNode> parseTerm();

    std::unique_ptr<ASTNode> parseFactor();

    std::unique_ptr<ASTNode> parseAssignment();

    std::unique_ptr<ASTNode> parseComparison();

    std::unique_ptr<ASTNode> parseIf();

    std::unique_ptr<ASTNode> parseStatement();

    std::unique_ptr<ASTNode> parse();
};
