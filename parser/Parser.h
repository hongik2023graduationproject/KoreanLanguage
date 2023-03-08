//
// Created by 김성민 on 2023/03/06.
//

#ifndef KOREANLANGUAGE_PARSER_H
#define KOREANLANGUAGE_PARSER_H
#include "../lexer/Lexer.h"

class Parser {
public:
    Token peekToken();
    Token nextToken();

};



#endif //KOREANLANGUAGE_PARSER_H
