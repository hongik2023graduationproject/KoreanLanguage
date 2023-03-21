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


class prefixParseFn {
    void func();
};

class infixParseFn {
    void func();
};

class Parser {
public:
    Lexer& lexer;
    std::vector<std::string> errors;

    Token curToken;
    Token peekToken;

    std::map<TokenType, prefixParseFn> prefixParseFns;
    std::map<TokenType, infixParseFn> infixParseFns;

    // 생성자
    Parser(Lexer& lexer) : lexer(lexer) {
        errors.clear();

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
    EQUALS,
    LESSGREATER,
    SUM,
    PRODUCT,
    PREFIX,
    CALL,
};



#endif //KOREANLANGUAGE_PARSER_H
