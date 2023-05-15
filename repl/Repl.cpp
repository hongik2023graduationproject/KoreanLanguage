//
// Created by 김성민 on 2023/03/04.
//

#include "Repl.h"


// TODO: repl에서 read해 parsing 및 lexer만 구현이 되어 있는 상태
//     - 추가로 구현이 진행됨에 따라 변경이 필요
[[noreturn]] void Repl::Run() {
    std::cout << "한국어 프로그래밍 언어 프로젝트" << '\n';
    std::cout << "제작: ezeun, jh-lee-kor, tolelom" << '\n';

    while (true) {
        std::string s;
        std::cout << ">>> ";
        getline(std::cin, s);

        // lexing
        Lexer* lexer = new Lexer;
        lexer->insert(s);

        /*
       // Lexer test code
        for ( ; lexer->position < lexer->input.size(); ) {
            Token t = lexer->NextToken();
            std::cout << "Token Type: " << t.Type << ", Token Literal: " << t.Literal << '\n';
        }
        */
        // parsing
        Parser* parser = new Parser(*lexer);
        Program* program = parser->ParseProgram(); // program은 parsing된 프로그램의 root node


        // if exist error
        if (parser->Errors().size() != 0) {
            for (auto it : parser->Errors()) {
                std::cout << it << '\n';
            }
        } else {
          std::cout << program->String() << '\n';
        }
        // TODO: 매 입력 라인마다 new, delete를 하는 게 맞는지 생각해보기
        delete program;
        delete parser;
        delete lexer;
    }
}