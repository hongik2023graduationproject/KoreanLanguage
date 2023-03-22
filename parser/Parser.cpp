//
// Created by 김성민 on 2023/03/06.
//

#include "Parser.h"
#include "../ast/Ast.h"
#include "../lexer/Lexer.h"

#include <iostream>

// Parser
void Parser::nextToken() {
    std::cout << "Debug: nextToken" << '\n';
    curToken = peekToken;
    peekToken = lexer.NextToken();
}

Program* Parser::ParseProgram() {
    Program* program = new Program; // root node

    while (curToken.Type != Eof) {
        Statement* stmt = parseStatement();

        if (stmt != nullptr) {
            program->statements.push_back(*stmt);
        }


        std::cout << "추가정보: " << stmt->token.Type << ' ' << stmt->token.Literal << '\n';

        // TODO: 임시로 if문 적용
        if (peekTokenIs(Eof)) {
            break;
        }

        nextToken(); // 마지막 토큰인 Eof 이후에 실행되면 SIGTRAP 오류
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
    std::cout << "DEBUG parseExpressionStatement: " << curToken.Literal << '\n';
    stmt->token = curToken;
    std::cout << "추가정보: " << stmt->token.Type << ' ' << stmt->token.Literal << '\n';
    stmt->expression = parseExpression(LOWEST); // expression parsing

    std::cout << "추가정보: " << stmt->token.Type << ' ' << stmt->token.Literal << '\n';

    // TODO: 우리는 Eof로 처리하므로 다음 토큰이 Eof가 아니라면 에러 처리를 해야한다.
    //      -식별자만 한 줄에 주어질 경우 에러로 처리하지 않으려면 에러처리를 안해도 될 거 같다.

    while (!peekTokenIs(Eof)) {
        nextToken();
    }

    std::cout << "추가정보: " << stmt->token.Type << ' ' << stmt->token.Literal << '\n';
    return stmt;
}

Expression* Parser::parseExpression(int precedence) {
    if (prefixParseFns.find(curToken.Type) == prefixParseFns.end())
        return nullptr;

    auto prefix = prefixParseFns.find(curToken.Type)->second;

    Expression* leftExp = (this->*prefix)();

    return leftExp;
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