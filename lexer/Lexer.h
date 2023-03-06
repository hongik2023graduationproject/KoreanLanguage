//
// Created by 김성민 on 2023/03/04.
//

#ifndef KOREANLANGUAGE_LEXER_H
#define KOREANLANGUAGE_LEXER_H

#include <string>
#include "./../token/Token.h"

class Lexer {
public:
    std::string input; // 입력
    int position; // 지금 읽고 있는 문자의 위치
    int readPosition; // 다음 읽을 문자의 위치
    char ch; // 지금 읽고 있는 문자
    TokenFunctions tokenFunctions;

    void insert(std::string input); // 문자열 input을 입력
    void readChar(); // 한 문자 읽기
    Token NextToken(); // 다음 토큰을 리턴
    char peekChar(); // 다음 문자 확인
    std::string readIdentifier();
    std::string readNumber();
    void skipWhitespace();
};


#endif //KOREANLANGUAGE_LEXER_H
