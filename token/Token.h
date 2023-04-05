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
const TokenType 알수없음 = "알수없음"; // 알 수 없음
const TokenType Eof = "EOF"; // End Of FIle

// 이름 + 리터럴
const TokenType 이름 = "이름";
const TokenType 정수 = "정수";

// 연산자
const TokenType 대입 = "대입"; // =
const TokenType 더하기 = "더하기"; // +
const TokenType 빼기 = "빼기"; // -
const TokenType 곱하기 = "곱하기"; // *
const TokenType 나누기 = "나누기"; // /
const TokenType BANG = "BANG"; // !

const TokenType 같다 = "같다"; // ==
const TokenType 다르다 = "다르다"; // !=

// 비교 연산자
const TokenType 작다 = "작다"; // <
const TokenType 크다 = "크다"; // >

// 특수 문자
const TokenType COMMA = "COMMA"; // ,
const TokenType SEMICOLON = "SEMICOLON"; // ;

// 괄호
const TokenType LPAREN = "LPAREN"; // (
const TokenType RPAREN = "RPAREN"; // )
const TokenType LBRACE = "LBRACE"; // {
const TokenType RBRACE = "RBRACE"; // }

// 예약어
const TokenType 함수 = "함수";
const TokenType LET = "LET";
const TokenType TRUE = "TRUE";
const TokenType FALSE = "FALSE";
const TokenType 만약 = "만약";
const TokenType 아니면 = "아니면";
const TokenType RETURN = "RETURN";

// space
const TokenType 공백 = "공백";
const TokenType 탭 = "탭";
const TokenType NL = "NEWLINE";

class TokenFunctions {
public:
    std::map<std::string, TokenType> keywords = {
            {"함수",     함수},
            {"let",    LET},
            {"true",   TRUE},
            {"false",  FALSE},
            {"만약",     만약},
            {"아니면",    아니면},
            {"return", RETURN},
    };

    TokenType LookupIdent(const std::string& ident) {
        if (keywords.find(ident) != keywords.end()) {
            return keywords.find(ident)->second;
        }
        return 이름;
    }
};


#endif //KOREANLANGUAGE_TOKEN_H
