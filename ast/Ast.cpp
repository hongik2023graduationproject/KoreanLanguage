//
// Created by 김성민 on 2023/03/09.
//

#include "Ast.h"


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
    std::string s = name->String() + " " + TokenLiteral() + " = ";
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


// IntegerLiteral
// 정수
std::string IntegerLiteral::TokenLiteral() {
    return token.Literal;
}
std::string IntegerLiteral::String() {
    return token.Literal;
}
void IntegerLiteral::expressionNode() {}


// PrefixExpression
std::string PrefixExpression::TokenLiteral() {
    return token.Literal;
}
std::string PrefixExpression::String() {
    return "(" + Operator + Right->String() + ")";
}
void PrefixExpression::expressionNode() {}



// InfixExpression
std::string InfixExpression::TokenLiteral() {
    return token.Literal;
}
std::string InfixExpression::String() {
    return "(" + Left->String() + " " + Operator + " " + Right->String() + ")";
}
void InfixExpression::expressionNode() {}


// Boolean
std::string Boolean::TokenLiteral() {
    return token.Literal;
}
std::string Boolean::String() {
    return token.Literal;
}
void Boolean::expressionNode() {}


// BlockStatement
std::string BlockStatement::TokenLiteral() {
    return token.Literal;
}
std::string BlockStatement::String() {
    std::string s;
    for (auto it : Statements) {
        s += it->String();
    }
    return s;
}
void BlockStatement::statementNode() {}

// IfExpression
std::string IfExpression::TokenLiteral() {
    return token.Literal;
}
std::string IfExpression::String() {
    std::string s;
    s += "if" + Condition->String() + " " + Consequence->String();

    if (Alternative != nullptr) {
        s += "else " + Alternative->String();
    }

    return s;
}
void IfExpression::expressionNode() {}

