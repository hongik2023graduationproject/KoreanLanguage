//
// Created by 김성민 on 2023/03/06.
//

#include "Parser.h"
#include "../ast/Ast.h"
#include "../lexer/Lexer.h"

// Parser
void Parser::nextToken() {
    curToken = peekToken;
    peekToken = lexer.NextToken();
}

Program* Parser::ParseProgram() {
    Program* program = new Program; // root node

    while (curToken.Type != Eof) {
        StatementNode* stmt = parseStatement();
        if (stmt != nullptr) {
            program->statements.push_back(*stmt);
        }
        nextToken();
    }
    return program;
}




StatementNode* Parser::parseStatement() {
    if (curToken.Type == identifier && peekToken.Type == EQ) {
        return parseAssignStatement();
    } else {
        return nullptr;
    }
}

AssignStatementNode* Parser::parseAssignStatement() {
    AssignStatementNode *stmt = new AssignStatementNode;

    stmt->token = peekToken; // =

    stmt->name = new IdentifierNode(curToken, curToken.Literal);

    nextToken();

    // TODO: EOF을 만날 때까지 표현식을 건너뛴다.
    while (curTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}



bool Parser::expectPeek(TokenType t) {
    if (peekToken.Type == t) {
        nextToken();
        return true;
    } else {
        return false;
    }
}

bool Parser::curTokenIs(TokenType t) {
    return curToken.Type == t;
}

bool Parser::peekTokenIs(TokenType t) {
    return peekToken.Type == t;
}