//
// Created by 김성민 on 2023/03/04.
//

#include "Lexer.h"
#include <string>
#include <utility>
#include <iostream>


bool isLetter(const std::string& ch);
bool isDigit(const std::string& ch);
Token newToken(TokenType tokenType, std::string ch);


void Lexer::insert(std::string s) {
    input = std::move(s);
    readPosition = position = 0;
    readChar();
};

void Lexer::readChar() {
    if (int(input.length()) <= readPosition) {
        ch = std::string(1, EOF);
    } else {
        int charLen = getCharLen(input[readPosition]);
        ch = input.substr(readPosition, charLen);
        readPosition += charLen - 1;
    }
    position = readPosition;
    readPosition++;
}

Token Lexer::NextToken() {
    Token tok;

    skipWhitespace();

    if (ch == "=") {
        if (peekChar() == "=") {
            std::string c = ch;
            readChar();
            tok = newToken(EQ, c + ch);
        } else {
            tok = newToken(ASSIGN, ch);
        }
    } else if (ch == "+") {
        tok = newToken(PLUS, ch);
    } else if (ch == "-") {
        tok = newToken(MINUS, ch);
    } else if (ch == "*") {
        tok = newToken(ASTERISK, ch);
    } else if (ch == "/") {
        tok = newToken(SLASH, ch);
    } else if (ch == "!") {
        if (peekChar() == "=") {
            std::string c = ch;
            readChar();
            tok = newToken(NOT_EQ, c + ch);
        } else {
            tok = newToken(BANG, ch);
        }
    } else if (ch == "<") {
        tok = newToken(LT, ch);
    } else if (ch == ">") {
        tok = newToken(GT, ch);
    } else if (ch == ",") {
        tok = newToken(COMMA, ch);
    } else if (ch == ";") {
        tok = newToken(SEMICOLON, ch);
    } else if (ch == "(") {
        tok = newToken(LPAREN, ch);
    } else if (ch == ")") {
        tok = newToken(RPAREN, ch);
    } else if (ch == "{") {
        tok = newToken(LBRACE, ch);
    } else if (ch == "}") {
        tok = newToken(RBRACE, ch);
    } else if (ch == std::string(1, EOF)) {
        tok = newToken(Eof, "");
    } else {
        if (isLetter(ch)) {
            std::string literal = readIdentifier();
            tok = newToken(tokenFunctions.LookupIdent(literal), literal);
            return tok;
        } else if (isDigit(ch)) {
            tok = newToken(INTEGER, readNumber());
            return tok;
        } else {
            tok = newToken(ILLEGAL, ch);
        }
    }


    readChar();
    return tok;
}



std::string Lexer::readIdentifier() {
    int p = position - (int)ch.length() + 1;
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
    while (ch == " " || ch == "\t" || ch == "\n" || ch == "\r") {
        readChar();
    }
}

std::string Lexer::peekChar() {
    if (readPosition >= input.length()) {
        return std::string(1, EOF);
    } else {
        int charLen = getCharLen(input[readPosition]);
        return input.substr(readPosition, charLen);
    }
}

bool isLetter(const std::string& ch) {
    if ((int)ch.length() == 1)
        return ("a" <= ch && ch <= "z") || ("A" <= ch && ch <= "Z") || ch == "_";
    else if ((int)ch.length() == 3)
        return ("가" <= ch && ch <= "핳");
    return false;
}

bool isDigit(const std::string& ch) {
    return ("0" <= ch && ch <= "9");
}

int Lexer::getCharLen(const char c) {
    int ret = 0;
    if (c & 0x80) {
        ret++;
        if (c & 0x40) {
            ret++;
            if (c & 0x20) {
                ret++;
                if (c & 0x10) {
                    ret++;
                }
            }
        }
    }
    if (ret == 0)
        return 1;
    else
        return ret;
}



Token newToken(TokenType tokenType, std::string ch) {
    return Token { std::move(tokenType), std::move(ch) };
}