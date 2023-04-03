cmake_minimum_required(VERSION 3.21)
project(KoreanLanguage)

set(CMAKE_CXX_STANDARD 23)

include_directories(ast)
include_directories(lexer)
include_directories(parser)
include_directories(repl)
include_directories(token)

add_executable(KoreanLanguage
        ast/Ast.cpp
        ast/Ast.h
        lexer/Lexer.cpp
        lexer/Lexer.h
        parser/Parser.cpp
        parser/Parser.h
        repl/Repl.cpp
        repl/Repl.h
        token/Token.h
        main.cpp)
