//
// Created by 김성민 on 2023/03/06.
//

#ifndef KOREANLANGUAGE_PARSER_H
#define KOREANLANGUAGE_PARSER_H

#include "../lexer/Lexer.h"
#include "../ast/Ast.h"

class Parser {
public:
    Lexer lexer;
    Token curToken;
    Token peekToken;

    Parser(Lexer &Lexer);
    Token nextToken();
    Program* ParseProgram();
};



#endif //KOREANLANGUAGE_PARSER_H
