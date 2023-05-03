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
const TokenType ILLEGAL = "ILLEGAL"; // 알 수 없음
const TokenType Eof = "EOF"; // End Of FIle

const TokenType IDENTIFIER = "IDENTIFIER";

const TokenType INTEGER = "INTEGER";
const TokenType FLOAT = "FLOAT";
const TokenType BOOLEAN = "BOOLEAN";

// 연산자
// 사칙연산
const TokenType PLUS = "PLUS"; // +
const TokenType MINUS = "MINUS"; // -
const TokenType ASTERISK = "ASTERISK"; // *
const TokenType SLASH = "SLASH"; // /
const TokenType DOUBLESLASH = "DOUBLESLASH"; // //
const TokenType PERCENT = "PERCENT"; // %

// 등호 및 대입
const TokenType ASSIGN = "ASSIGN"; // =
const TokenType EQ = "EQ"; // ==
const TokenType NOT_EQ = "NOT_EQ"; // !=
const TokenType LT = "LT"; // <
const TokenType GT = "GT"; // >
const TokenType LE = "LE"; // <=
const TokenType GE = "GE"; // >=

// 비트 연산
const TokenType AND = "AND"; // &
const TokenType DOUBLEAND = "DOUBLEAND"; // &&
const TokenType OR = "OR"; // |
const TokenType DOUBLEOR = "DOUBLEOR"; // ||
const TokenType BANG = "BANG"; // !
const TokenType CIRCUMFLEX = "CIRCUMFLEX"; // ^
const TokenType TILDE = "TILDE"; // ~
const TokenType SHIFTLEFT = "SHIFTLEFT"; // <<
const TokenType SHIFTRIGHT = "SHIFTRIGHT"; // >>


// 특수 문자
const TokenType COMMA = "COMMA"; // ,
const TokenType SEMICOLON = "SEMICOLON"; // ;

// 괄호
const TokenType LPAREN = "LPAREN"; // (
const TokenType RPAREN = "RPAREN"; // )
const TokenType LBRACE = "LBRACE"; // {
const TokenType RBRACE = "RBRACE"; // }

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
    };

    TokenType LookupIdent(const std::string& ident) {
        if (keywords.find(ident) != keywords.end()) {
            return keywords.find(ident)->second;
        }
        return IDENTIFIER;
    }
};


#endif //KOREANLANGUAGE_TOKEN_H
