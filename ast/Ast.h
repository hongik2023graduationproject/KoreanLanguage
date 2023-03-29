//
// Created by 김성민 on 2023/03/09.
//

#ifndef KOREANLANGUAGE_AST_H
#define KOREANLANGUAGE_AST_H

#include <string>
#include <vector>

#include "../token/Token.h"

// interface
class Node {
public:
    Token token;

    virtual std::string TokenLiteral() = 0;
    virtual std::string String() = 0; // Debug, 출력을 확인하는 용도이므로 최종 단계 전까지 삭제 금지
};

class Statement : public Node {
public:
    virtual void statementNode() = 0;
};

class Expression : public Node {
public:
    virtual void expressionNode() = 0;
};




// Program: 전체 프로그램의 root 노드이다.
// statements 백터에 프로그램을 파싱해서 순서대로 저장한다.
class Program : public Node {
public:
    std::vector<Statement*> statements;

    Program();
    std::string TokenLiteral() override;
    std::string String() override;
};


// Identifier: 식별자, 표현식이다.
class Identifier : public Expression {
public:
    Token token;
    std::string value;

    std::string TokenLiteral() override;
    std::string String() override;
    void expressionNode() override;
};


// ExpressionStatement:
class ExpressionStatement : public Statement {
public:
    Token token; // 표현식의 첫 번째 토큰
    Expression* expression;


    std::string TokenLiteral() override;
    std::string String() override;
    void statementNode() override;
};

// AssignStatement: 값을 변수에 할당하는 문법
// <IDENTIFIER> = <expression> Eof
// 의 형식이다.
class AssignStatement : public Statement {
public:
    Token token; // = 토큰을 저장한다.
    Identifier* name; // 좌변
    Expression* value; // 우변


    std::string TokenLiteral() override;
    std::string String() override;
    void statementNode() override;
};


// ReturnStatement: 값을 리턴하는 문법
// return <expression> Eof
// 의 형식이다.
class ReturnStatement : public Statement {
public:
    Token token; // return 토큰
    Expression* ReturnValue; // value

    std::string TokenLiteral() override;
    std::string String() override;
    void statementNode() override;
};


class IntegerLiteral : public Expression {
public:
    Token token;
    int value;

    std::string TokenLiteral() override;
    std::string String() override;
    void expressionNode() override;
};


class PrefixExpression : public Expression {
public:
    Token token;
    std::string Operator; // ISSUE: 소문자 operator는 키워드 겹침
    Expression* Right;

    std::string TokenLiteral() override;
    std::string String() override;
    void expressionNode() override;
};

class InfixExpression : public Expression {
public:
    Token token;
    Expression* Left;
    std::string Operator;
    Expression* Right;

    std::string TokenLiteral() override;
    std::string String() override;
    void expressionNode() override;
};

class Boolean : public Expression {
public:
    Token token;
    bool value;

    std::string TokenLiteral() override;
    std::string String() override;
    void expressionNode() override;
};

class BlockStatement : public Statement {
public:
    Token token;
    std::vector<Statement*> Statements;

    std::string TokenLiteral() override;
    std::string String() override;
    void statementNode() override;
};

class IfExpression : public Expression {
public:
    Token token; // if 토큰
    Expression* Condition;
    BlockStatement* Consequence;
    BlockStatement* Alternative;

    std::string TokenLiteral() override;
    std::string String() override;
    void expressionNode() override;
};



#endif //KOREANLANGUAGE_AST_H
