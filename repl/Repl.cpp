//
// Created by 김성민 on 2023/03/04.
//

#include "Repl.h"
#include "../lexer/Lexer.h"
#include <iostream>

void Repl::Run() {
    std::cout << "한국어 프로그래밍 언어 프로잭트" << '\n';
    std::cout << "제작: ezeun, jh-lee-kor, tolelom" << '\n';

    Lexer lexer;

    while (true) {
        std::string s;
        std::cout << ">>> ";
        getline(std::cin, s);

        lexer.insert(s);
        std::cout << lexer.position << ' ' << lexer.readPosition << ' ' << lexer.ch << '\n';

        while (lexer.position < lexer.input.length()) {
            Token tok = lexer.NextToken();
            std::cout << "Token Type: " << tok.Type << ", Token Literal: " << tok.Literal << '\n';
        }


        std::cout << s << '\n';
    }
}