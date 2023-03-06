#include <iostream>
#include <vector>
#include "repl/Repl.h"
#include "token/Token.h"
#include "lexer/Lexer.h"

using namespace std;

void lexer_test();

int main() {
    Repl repl;
    repl.Run();

//    lexer_test();

    return 0;
}


void lexer_test() {
    string input = "let five = 5;"
                   "let ten = 10;";
//                   "let add = fn(x, y) {"
//                   "    x + y;"
//                   "};"
//                   "let result = add(five, ten);";

    vector<pair<string, TokenType>> tests = {
            {LET, "let"},
            {식별자, "five"},
            {ASSIGN, "="},
            {정수, "5"},
            {SEMICOLON, ";"},
            {LET, "let"},
            {식별자, "ten"},
            {ASSIGN, "="},
            {정수, "10"},
            {SEMICOLON, ";"},
            {EOFi, ""},
    };

    Lexer lexer;
    lexer.insert(input);

    for (int i = 0, p = 0; p < int(input.length()); ++i, ++p) {
        Token tok = lexer.NextToken();
//        cout << i << ", " << p << ": ";
        if (tok.Type != tests[i].first) {
            cout << "토큰 타입 오류. 예상 토큰: " << tests[i].first << " 실제 토큰: " << tok.Type << '\n';
        }
        if (tok.Literal != tests[i].second) {
            cout << "리터럴 오류. 예상: " << tests[i].second << " 실제: " << tok.Literal << '\n';
        }
        p = lexer.position;
    }
}