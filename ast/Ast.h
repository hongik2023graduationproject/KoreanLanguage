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
    std::string String(); // Debug, 출력을 확인하는 용도이므로 최종 단계 전까지 삭제 금지
};

class Statement : public Node {
public:
    std::string TokenLiteral();
    std::string String();
    void statementNode();
};

class Expression : public Node {
public:
    std::string TokenLiteral();
    std::string String();
    void expressionNode();
};




// Program: 전체 프로그램의 root 노드이다.
// statements 백터에 프로그램을 파싱해서 순서대로 저장한다.
class Program : public Node {
public:
    std::vector<Statement> statements;

    Program();
    std::string TokenLiteral();
    std::string String();
};


// Identifier: 식별자, 표현식이다.
class Identifier : public Expression {
public:
    Token token;
    std::string value;

    std::string TokenLiteral();
    std::string String();
    void expressionNode();
};


// ExpressionStatement:
class ExpressionStatement : public Statement {
public:
    Token token; // 표현식의 첫 번째 토큰
    Expression* expression;


    std::string TokenLiteral();
    std::string String();
    void statementNode();
};

// AssignStatement: 값을 변수에 할당하는 문법
// <IDENTIFIER> = <expression> Eof
// 의 형식이다.
class AssignStatement : public Statement {
public:
    Token token; // = 토큰을 저장한다.
    Identifier* name; // 좌변
    Expression* value; // 우변


    std::string TokenLiteral();
    std::string String();
    void statementNode();
};


// ReturnStatement: 값을 리턴하는 문법
// return <expression> Eof
// 의 형식이다.
class ReturnStatement : public Statement {
public:
    Token token; // return 토큰
    Expression* ReturnValue; // value

    std::string TokenLiteral();
    std::string String();
    void statementNode();
};




#endif //KOREANLANGUAGE_AST_H
