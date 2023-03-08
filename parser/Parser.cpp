//
// Created by 김성민 on 2023/03/06.
//

#include "Parser.h"

Parser::Parser(Lexer &lexer) {
    this->lexer = lexer;
    nextToken();
    nextToken();
}

Token Parser::nextToken() {
    curToken = peekToken;
    peekToken = nextToken();
}

Program* Parser::ParseProgram() {
    return nullptr;
}

