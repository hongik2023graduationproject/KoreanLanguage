//
// Created by 김성민 on 2023/03/06.
//

#include "Parser.h"
#include "../ast/Ast.h"
#include "../lexer/Lexer.h"

#include <iostream>

// Parser
void Parser::nextToken() {
    curToken = peekToken;
    peekToken = lexer.NextToken();
}

Program* Parser::ParseProgram() {
    Program* program = new Program; // root node

    while (curToken.Type != Eof) {
        std::cout << curToken.Type << ' ' << peekToken.Type << '\n'; // debug

        Statement* stmt = parseStatement();

        if (stmt != nullptr) {
            program->statements.push_back(*stmt);
        }
        nextToken();
    }
    return program;
}


Statement* Parser::parseStatement() {
    if (curToken.Type == IDENTIFIER && peekToken.Type == ASSIGN) {
        return parseAssignStatement();
    } else if (curToken.Type == RETURN) {
        return parseReturnStatement();
    } else {
        return parseExpressionStatement();
    }
}

Expression* Parser::parseExpression(int precedence) {
    if (prefixParseFns.find(curToken.Type) == prefixParseFns.end())
        return nullptr;

    prefixParseFn prefix = prefixParseFns.find(curToken.Type)->second;


}

AssignStatement* Parser::parseAssignStatement() {
    AssignStatement *stmt = new AssignStatement;

    stmt->name = new Identifier;
    // TODO: 생성자 만들어서 코드 정리하기
    stmt->name->token = curToken;
    stmt->name->value = curToken.Literal;

    nextToken();
    stmt->token = curToken; // =


    // TODO: EOF을 만날 때까지 표현식을 건너뛴다.
    //      -우항은 아직 패스
    while (curTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}


ReturnStatement* Parser::parseReturnStatement() {
    ReturnStatement* stmt = new ReturnStatement;
    stmt->token = curToken; // return 토큰

    // TODO: EOF을 만날 때까지 표현식을 건너뛴다.
    //      -우항은 아직 패스
    while (curTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}

ExpressionStatement* Parser::parseExpressionStatement() {
    ExpressionStatement* stmt = new ExpressionStatement;
    stmt->token = curToken;
    stmt->expression = parseExpression(LOWEST); // expression parsing

    // TODO: 우리는 Eof로 처리하므로 다음 토큰이 Eof가 아니라면 에러 처리를 해야한다.
    if (peekTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}



bool Parser::expectPeek(TokenType t) {
    if (peekToken.Type == t) {
        nextToken();
        return true;
    } else {
        peekError(t);
        return false;
    }
}

bool Parser::curTokenIs(TokenType t) {
    return curToken.Type == t;
}

bool Parser::peekTokenIs(TokenType t) {
    return peekToken.Type == t;
}

std::vector<std::string> Parser::Errors() {
    return errors;
}

void Parser::peekError(TokenType t) {
    std::string msg = "예상 토큰은 " + t + "입니다. 하지만 실제 토큰은 " + peekToken.Type + "입니다.\n";
    errors.push_back(msg);
}