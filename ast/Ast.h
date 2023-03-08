//
// Created by 김성민 on 2023/03/09.
//

#ifndef KOREANLANGUAGE_AST_H
#define KOREANLANGUAGE_AST_H

#include "../token/Token.h"
#include <vector>
#include <string>


class Node {
public:
    virtual std::string TokenLiteral() = 0;
};

class StatementNode : public Node {
public:
    virtual void statementNode() = 0;
};

class ExpressionNode : public Node {
public:
    virtual void expressionNode() = 0;
};

class Program : public Node {
public:
    std::string TokenLiteral();
    std::vector<StatementNode> Statements;
};

class IdentifierNode : public ExpressionNode {
public:
    Token token;
    std::string value;

    std::string TokenLiteral();
    void expressionNode();
};


#endif //KOREANLANGUAGE_AST_H
