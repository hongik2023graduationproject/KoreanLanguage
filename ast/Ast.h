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
    virtual std::string Debug() = 0;
};

class Statement : public Node {
public:
};

class Expression : public Node {
public:
};

class Program : public Node {
public:
    std::vector<Statement*> statements;

    Program();
    std::string TokenLiteral() override;
    std::string Debug() override;
};

class Identifier : public Expression {
public:
    Token token; // identifer token
    Token type; // type token
    std::string value;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

class Integer : public Expression {
public:
    Token token;
    long long value;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

class Boolean : public Expression {
public:
    Token token;
    bool value;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

// AssignStatement
class AssignStatement : public Statement {
public:
    Token token; // = token
    Identifier* name; // 좌변
    Expression* value; // 우변
;
    std::string TokenLiteral() override;
    std::string Debug() override;
};









// ExpressionStatement:
class ExpressionStatement : public Statement {
public:
    Token token; // 표현식의 첫 번째 토큰
    Expression* expression;


    std::string TokenLiteral() override;
    std::string Debug() override;
};





// ReturnStatement: 값을 리턴하는 문법
// return <expression> Eof
// 의 형식이다.
class ReturnStatement : public Statement {
public:
    Token token; // return 토큰
    Expression* ReturnValue; // value

    std::string TokenLiteral() override;
    std::string Debug() override;
};

class BlockStatement : public Statement {
public:
    Token token;
    std::vector<Statement*> Statements;

    std::string TokenLiteral() override;
    std::string Debug() override;
};




class PrefixExpression : public Expression {
public:
    Token token;
    std::string Operator; // ISSUE: 소문자 operator는 키워드 겹침
    Expression* Right;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

class InfixExpression : public Expression {
public:
    Token token;
    Expression* Left;
    std::string Operator;
    Expression* Right;

    std::string TokenLiteral() override;
    std::string Debug() override;
};




class IfExpression : public Expression {
public:
    Token token; // if 토큰
    Expression* Condition;
    BlockStatement* Consequence;
    BlockStatement* Alternative;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

class FunctionStatement : public Statement{
public:
    Token token; // fn 토큰
    Identifier* name;
    std::vector<std::pair<Identifier *, Identifier *>> parameters;
    BlockStatement* body;
    Token retType;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

class CallExpression : public Expression{
    Token token;
    Expression* function;
    std::vector<Identifier *> arguments;

    std::string TokenLiteral() override;
    std::string Debug() override;
};

#endif //KOREANLANGUAGE_AST_H
