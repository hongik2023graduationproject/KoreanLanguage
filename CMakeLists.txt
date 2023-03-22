cmake_minimum_required(VERSION 3.21)
project(KoreanLanguage)

set(CMAKE_CXX_STANDARD 23)

add_executable(KoreanLanguage main.cpp repl/Repl.cpp repl/Repl.h lexer/Lexer.cpp lexer/Lexer.h token/Token.h parser/Parser.cpp parser/Parser.h ast/Ast.cpp ast/Ast.h)
