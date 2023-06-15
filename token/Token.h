//
// Created by 김성민 on 2023/03/04.
//

#ifndef KOREANLANGUAGE_TOKEN_H
#define KOREANLANGUAGE_TOKEN_H

#include <string>
#include <map>

#define TokenType std::string

class Token {
public:
    TokenType Type; // 토큰 타입
    std::string Literal; // 토큰
};


// TokenType
// check -> Lexer에 적용된 토큰
const TokenType ILLEGAL = "ILLEGAL"; // 알 수 없음
const TokenType Eof = "EOF"; // End Of FIle

const TokenType IDENTIFIER = "IDENTIFIER";

const TokenType INTEGER = "INTEGER";
const TokenType FLOAT = "FLOAT";
const TokenType BOOLEAN = "BOOLEAN";

// 연산자
// 사칙연산
const TokenType PLUS = "PLUS"; // + check
const TokenType MINUS = "MINUS"; // - check
const TokenType ASTERISK = "ASTERISK"; // * check
const TokenType SLASH = "SLASH"; // / check
const TokenType DOUBLESLASH = "DOUBLESLASH"; // // check
const TokenType PERCENT = "PERCENT"; // % check

// 등호 및 대입
const TokenType ASSIGN = "ASSIGN"; // = check
const TokenType EQ = "EQ"; // == check
const TokenType NOT_EQ = "NOT_EQ"; // != check
const TokenType LT = "LT"; // < check
const TokenType GT = "GT"; // > check
const TokenType LE = "LE"; // <= check
const TokenType GE = "GE"; // >= check

// 비트 연산
const TokenType AND = "AND"; // & check
const TokenType DOUBLEAND = "DOUBLEAND"; // && check
const TokenType OR = "OR"; // | check
const TokenType DOUBLEOR = "DOUBLEOR"; // || check
const TokenType BANG = "BANG"; // ! check
const TokenType CIRCUMFLEX = "CIRCUMFLEX"; // ^ check
const TokenType TILDE = "TILDE"; // ~ check
const TokenType SHIFTLEFT = "SHIFTLEFT"; // << check
const TokenType SHIFTRIGHT = "SHIFTRIGHT"; // >> check

// arrow
const TokenType RARROW = "RARROW"; // ->

// 특수 문자
const TokenType COMMA = "COMMA"; // , check
const TokenType SEMICOLON = "SEMICOLON"; // ; check

// 괄호
const TokenType LPAREN = "LPAREN"; // ( check
const TokenType RPAREN = "RPAREN"; // ) check
const TokenType LBRACE = "LBRACE"; // { check
const TokenType RBRACE = "RBRACE"; // } check

// 예약어
const TokenType FUNCTION = "FUNCTION";
const TokenType CLASS = "CLASS";
const TokenType FOR = "FOR";
const TokenType WHILE = "WHILE";
const TokenType TRUE = "TRUE";
const TokenType FALSE = "FALSE";
const TokenType IF = "IF";
const TokenType ELSE = "ELSE";
const TokenType RETURN = "RETURN";



// space
const TokenType SPACE = "SPACE";
const TokenType TAB = "TAB";
const TokenType NEWLINE = "NEWLINE";

class TokenFunctions {
public:
    std::map<std::string, TokenType> keywords = {
            {"fn",     FUNCTION},
            {"class", CLASS},
            {"for", FOR},
            {"while", WHILE},
            {"true",   TRUE},
            {"false",  FALSE},
            {"if",     IF},
            {"else",    ELSE},
            {"return", RETURN},
            {"int", INTEGER},
            {"float", FLOAT},
            {"bool", BOOLEAN},
    };

    TokenType LookupIdent(const std::string& ident) {
        if (keywords.find(ident) != keywords.end()) {
            return keywords.find(ident)->second;
        }
        return IDENTIFIER;
    }
};


#endif //KOREANLANGUAGE_TOKEN_H
