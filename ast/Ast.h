//
// Created by 김성민 on 2023/03/09.
//

#ifndef KOREANLANGUAGE_AST_H
#define KOREANLANGUAGE_AST_H

#include "../token/Token.h"
#include <vector>
#include <string>

// interface
class Node {
public:
    std::string TokenLiteral();
};

class StatementNode : public Node {
public:
    std::string TokenLiteral();
    void statementNode();
};

class ExpressionNode : public Node {
public:
    std::string TokenLiteral();
    void expressionNode();
};




// Node 구현체

// root Node
class Program : public Node {
public:
    std::vector<StatementNode> statements;

    Program();
    std::string TokenLiteral();
};

class IdentifierNode : public ExpressionNode {
public:
    Token token;
    std::string value;

    IdentifierNode(Token token, std::string value) : token(token), value(value) {};
    std::string TokenLiteral();
    void expressionNode();
};

// <identifier> = <expression>
class AssignStatementNode : public StatementNode {
public:
    Token token;
    IdentifierNode* name;
    ExpressionNode* value;

    std::string TokenLiteral();
    void expressionNode();
};

#endif //KOREANLANGUAGE_AST_H
