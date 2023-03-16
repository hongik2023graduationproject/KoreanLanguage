//
// Created by 김성민 on 2023/03/06.
//

#ifndef KOREANLANGUAGE_PARSER_H
#define KOREANLANGUAGE_PARSER_H

#include "../lexer/Lexer.h"
#include "../ast/Ast.h"

class Parser {
public:
    Lexer& lexer;
    Token curToken;
    Token peekToken;

    // 생성자
    Parser(Lexer& lexer) : lexer(lexer) {
        nextToken();
        nextToken();
    };

    // 다음 토큰을 lexer로부터 읽어온다.
    void nextToken();

    Program* ParseProgram();
    StatementNode* parseStatement();
    AssignStatementNode* parseAssignStatement();

    bool expectPeek(TokenType t);
    bool curTokenIs(TokenType t);
    bool peekTokenIs(TokenType t);
};


#endif //KOREANLANGUAGE_PARSER_H
