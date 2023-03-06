//
// Created by 김성민 on 2023/03/04.
//

#include "Lexer.h"
#include <string>

Token newToken(TokenType tokenType, std::string ch);
bool isLetter(char ch);
bool isDigit(char ch);

void Lexer::insert(std::string s) {
    input = s;
    readPosition = position = 0;
    ch = input[readPosition];
    readPosition++;
};

void Lexer::readChar() {
    if (int(input.length()) <= readPosition) {
        ch = 0;
    } else {
        ch = input[readPosition];
    }
    position = readPosition;
    readPosition++;
}

Token Lexer::NextToken() {
    Token tok;

    skipWhitespace();

    switch (ch) {
        case '=':
            if (peekChar() == '=') {
                char c = ch;
                readChar();
                tok = newToken(EQ, std::string(1, c) + std::string(1, ch));
            } else {
                tok = newToken(ASSIGN, std::string(1, ch));
            }
            break;
        case '+':
            tok = newToken(PLUS, std::string(1, ch));
            break;
        case '-':
            tok = newToken(MINUS, std::string(1, ch));
            break;
        case '*':
            tok = newToken(ASTERISK, std::string(1, ch));
            break;
        case '/':
            tok = newToken(SLASH, std::string(1, ch));
            break;
        case '!':
            if (peekChar() == '=') {
                char c = ch;
                readChar();
                tok = newToken(NOT_EQ, std::string(1, c) + std::string(1, ch));
            } else {
                tok = newToken(BANG, std::string(1, ch));
            }
            break;
        case '<':
            tok = newToken(LT, std::string(1, ch));
            break;
        case '>':
            tok = newToken(GT, std::string(1, ch));
            break;
        case ',':
            tok = newToken(COMMA, std::string(1, ch));
            break;
        case ';':
            tok = newToken(SEMICOLON, std::string(1, ch));
            break;
        case '(':
            tok = newToken(LPAREN, std::string(1, ch));
            break;
        case ')':
            tok = newToken(RPAREN, std::string(1, ch));
            break;
        case '{':
            tok = newToken(LBRACE, std::string(1, ch));
            break;
        case '}':
            tok = newToken(RBRACE, std::string(1, ch));
            break;

        default:
            if (isLetter(ch)) {
                std::string literal = readIdentifier();
                tok = newToken(tokenFunctions.LookupIdent(literal), literal);
                return tok;
            } else if (isDigit(ch)) {
                tok = newToken(정수, readNumber());
                return tok;
            } else {
                tok = newToken(ILLEGAL, std::string(1, ch));
            }
            break;
    }

    readChar();
    return tok;
}

Token newToken(TokenType tokenType, std::string ch) {
    Token tok;
    tok.Type = tokenType;
    tok.Literal = ch;
    return tok;
}

std::string Lexer::readIdentifier() {
    int p = position;
    while (isLetter(ch)) {
        readChar();
    }

    return input.substr(p, position - p);
}

std::string Lexer::readNumber() {
    int p = position;
    while (isDigit(ch)) {
        readChar();
    }
    return input.substr(p, position - p);
}

void Lexer::skipWhitespace() {
    while (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r')
        readChar();
}

char Lexer::peekChar() {
    if (readPosition >= input.length()) {
        return 0;
    } else {
        return input[readPosition];
    }
}

bool isLetter(char ch) {
    return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') || ch == '_';
}

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}