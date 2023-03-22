//
// Created by 김성민 on 2023/03/09.
//

#include "Ast.h"

#include <iostream>

// Program
Program::Program() {
    statements.clear();
}
std::string Program::TokenLiteral() {
    if (statements.size() > 0) {
        return statements[0]->TokenLiteral();
    } else {
        return "";
    }
}
std::string Program::String() {
    std::string s;
    for (auto it : statements) {
        s += it->String();
    }
    return s;
}



// Identifier Node
std::string Identifier::TokenLiteral() {
    return token.Literal;
}
std::string Identifier::String() {
    return value;
}
void Identifier::expressionNode() {}



// AssignStatement
std::string AssignStatement::TokenLiteral() {
    return token.Literal;
}
std::string AssignStatement::String() {
    std::string s = TokenLiteral() + " " + name->String() + " = ";
    if (value != nullptr) {
        s += value->String() + "\n";
    }

    return s;
}
void AssignStatement::statementNode() {}



// ReturnStatement
std::string ReturnStatement::TokenLiteral() {
    return token.Literal;
}
std::string ReturnStatement::String() {
    std::string s = TokenLiteral() + " ";
    if (ReturnValue != nullptr) {
        s += ReturnValue->String();
    }

    return s;
}
void ReturnStatement::statementNode() {}



// ExpressionStatement
std::string ExpressionStatement::TokenLiteral() {
    return token.Literal;
}
std::string ExpressionStatement::String() {
    if (expression != nullptr) {
        return expression->String();
    }

    return "";
}
void ExpressionStatement::statementNode() {}




