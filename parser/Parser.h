//
// Created by 김성민 on 2023/03/06.
//

#ifndef KOREANLANGUAGE_PARSER_H
#define KOREANLANGUAGE_PARSER_H

#include "../lexer/Lexer.h"
#include "../ast/Ast.h"

#include <vector>
#include <string>
#include <map>
#include <iostream>


class Parser {
public:
    Lexer& lexer;
    std::vector<std::string> errors;

    Token curToken;
    Token peekToken;


    // 전위, 중위 연산자 부분
    using prefixParseFn = Expression* (Parser::*)();
    typedef Expression* (Parser::*infixParseFn)();
    std::map<TokenType, prefixParseFn> prefixParseFns;
    std::map<TokenType, infixParseFn> infixParseFns;

    Expression* parseIdentifier() {
        Identifier* identifier = new Identifier;
        identifier->token = curToken;
        identifier->value = curToken.Literal;
        std::cout << "DEBUG parseIdentifier "  << identifier->String() << '\n';
        return identifier;
    }


    // 생성자
    Parser(Lexer& lexer) : lexer(lexer) {
        errors.clear();
        prefixParseFns.clear();
        infixParseFns.clear();

        registerPrefix(IDENTIFIER, &Parser::parseIdentifier);

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
};


// 우선 순위
enum precedence {
    LOWEST,
    EQUALS, // ==
    LESSGREATER, // >, <
    SUM, // +
    PRODUCT, // *
    PREFIX, // -X, !X
    CALL, // myFunc(X)
};



#endif //KOREANLANGUAGE_PARSER_H
