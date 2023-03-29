//
// Created by 김성민 on 2023/03/04.
//

#ifndef KOREANLANGUAGE_TOKEN_H
#define KOREANLANGUAGE_TOKEN_H

#include <string>
#include <map>

#define TokenType std::string

struct Token {
    TokenType Type; // 토큰 타입
    std::string Literal; // 토큰
};


// TokenType
// TODO: TokenType도 하나로 묶어서 관리하면 좋을 거 같습니다.
const TokenType ILLEGAL = "ILLEGAL"; // 알 수 없음
const TokenType Eof = "EOF"; // End Of FIle

// IDENTIFIER + 리터럴
const TokenType IDENTIFIER = "IDENTIFIER";
const TokenType INTEGER = "INTEGER";

// 연산자
const TokenType ASSIGN = "ASSIGN"; // =
const TokenType PLUS = "PLUS"; // +
const TokenType MINUS = "MINUS"; // -
const TokenType ASTERISK = "ASTERISK"; // *
const TokenType SLASH = "SLASH"; // /
const TokenType BANG = "BANG"; // !

const TokenType EQ = "EQ"; // ==
const TokenType NOT_EQ = "NOT_EQ"; // !=

// 비교 연산자
const TokenType LT = "LT"; // <
const TokenType GT = "GT"; // >

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
const TokenType LET = "LET";
const TokenType TRUE = "TRUE";
const TokenType FALSE = "FALSE";
const TokenType IF = "IF";
const TokenType ELSE = "ELSE";
const TokenType RETURN = "RETURN";

// space
const TokenType SPACE = "SPACE";
const TokenType TAB = "TAB";
const TokenType NL = "NEWLINE";

class TokenFunctions {
public:
    std::map<std::string, TokenType> keywords = {
            {"함수", FUNCTION},
            {"let", LET},
            {"true", TRUE},
            {"false", FALSE},
            {"만약", IF},
            {"아니면", ELSE},
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
