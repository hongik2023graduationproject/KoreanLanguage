//
// Created by 김성민 on 2023/03/04.
//

#ifndef KOREANLANGUAGE_REPL_H
#define KOREANLANGUAGE_REPL_H

#include <iostream>
#include <string>
#include <format>

#include "../parser/Parser.h"
#include "../lexer/Lexer.h"

// Read Eval Print Loop
class Repl {
public:
    [[noreturn]] void Run(); // 시작 FN
};


#endif //KOREANLANGUAGE_REPL_H
