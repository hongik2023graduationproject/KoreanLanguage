//
// Created by 김성민 on 2023/03/04.
//

#ifndef KOREANLANGUAGE_LEXER_H
#define KOREANLANGUAGE_LEXER_H


#include <string>
#include <utility>
#include <iostream>

#include "./../token/Token.h"

// Lexer
// 문자열을 한 줄씩 받아 토큰으로 바꿔준다.
class Lexer {
public:
    std::string input; // 입력
    int position; // 지금 읽고 있는 문자의 위치
    int readPosition; // 다음 읽을 문자의 위치
    std::string ch; // 지금 읽고 있는 문자
    TokenFunctions tokenFunctions; // 식별자인지 사전 정의된 토큰인지 확인하는 클래스


    void insert(std::string input); // 문자열 input을 입력
    void readChar(); // 한 문자 읽기
    Token NextToken(); // 다음 토큰을 리턴
    std::string peekChar(); // 다음 문자 확인
    std::string readIdentifier(); // 식별자 읽기
    std::string readNumber(); // 정수 읽기
    int getCharLen(char c); // uft-8 형식의 문자 길이 얻기
};


#endif //KOREANLANGUAGE_LEXER_H
