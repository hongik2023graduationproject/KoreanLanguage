//
// Created by 김성민 on 2023/03/06.
//

#ifndef KOREANLANGUAGE_PARSER_H
#define KOREANLANGUAGE_PARSER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "../lexer/Lexer.h"
#include "../ast/Ast.h"

class Parser {
public:
    Lexer& lexer;
    std::vector<std::string> errors;

    Token curToken;
    Token peekToken;

    // 우선 순위
    // TODO: 나중에 enum class로 변경이 가능하다면 변경하기
    enum precedence {
        LOWEST,
        EQUALS, // ==
        LESSGREATER, // >, <
        SUM, // +
        PRODUCT, // *
        PREFIX, // -X, !X
        CALL, // myFunc(X)
    };

    std::map<TokenType, int> precedences = {
            {같다,  EQUALS},
            {다르다, EQUALS},
            {작다,  LESSGREATER},
            {크다,  LESSGREATER},
            {더하기, SUM},
            {빼기,  SUM},
            {나누기, PRODUCT},
            {곱하기, PRODUCT},
    };

    // 전위, 중위 연산자 부분
    using prefixParseFn = Expression* (Parser::*)();
    using infixParseFn =  Expression* (Parser::*)(Expression*);
    std::map<TokenType, prefixParseFn> prefixParseFns;
    std::map<TokenType, infixParseFn> infixParseFns;

    Expression* parseIdentifier();
    Expression* parseIntegerLiteral();
    Expression* parsePrefixExpression();
    Expression* parseInfixExpression(Expression* left);
    Expression* parseBoolean();
    Expression* parseGroupedExpression();
    Expression* parseIfExpression();
    BlockStatement* parseBlockStatement();

    // 생성자
    Parser(Lexer& lexer) : lexer(lexer) {
        errors.clear();
        prefixParseFns.clear();
        infixParseFns.clear();

        registerPrefix(이름, &Parser::parseIdentifier);
        registerPrefix(정수, &Parser::parseIntegerLiteral);
        registerPrefix(BANG, &Parser::parsePrefixExpression);
        registerPrefix(빼기, &Parser::parsePrefixExpression);
        registerPrefix(TRUE, &Parser::parseBoolean);
        registerPrefix(FALSE, &Parser::parseBoolean);
        registerPrefix(LPAREN, &Parser::parseGroupedExpression);
        registerPrefix(만약, &Parser::parseIfExpression);

        registerInfix(더하기, &Parser::parseInfixExpression);
        registerInfix(빼기, &Parser::parseInfixExpression);
        registerInfix(나누기, &Parser::parseInfixExpression);
        registerInfix(곱하기, &Parser::parseInfixExpression);
        registerInfix(같다, &Parser::parseInfixExpression);
        registerInfix(다르다, &Parser::parseInfixExpression);
        registerInfix(작다, &Parser::parseInfixExpression);
        registerInfix(크다, &Parser::parseInfixExpression);


        nextToken();
        nextToken();
    };

    // 다음 토큰을 lexer로부터 읽어온다.
    void nextToken();

    Program* ParseProgram();
    Statement* parseStatement();
    Expression* parseExpression(int precedence);
    AssignStatement* parseAssignStatement();
    ReturnStatement* parseReturnStatement();
    ExpressionStatement* parseExpressionStatement();

    bool expectPeek(TokenType t);
    bool curTokenIs(TokenType t);
    bool peekTokenIs(TokenType t);

    std::vector<std::string> Errors();
    void peekError(TokenType t);

    void registerPrefix(TokenType tokenType, prefixParseFn fn) {
        prefixParseFns.insert({tokenType, fn});
    };
    void registerInfix(TokenType tokenType, infixParseFn fn) {
        infixParseFns.insert({tokenType, fn});
    }

    void noPrefixParseFnError(TokenType t);

    int peekPrecedence();
    int curPrecedence();
};



#endif //KOREANLANGUAGE_PARSER_H
