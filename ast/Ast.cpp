//
// Created by 김성민 on 2023/03/09.
//

#include "Ast.h"

// Program
std::string Program::TokenLiteral() {
    if (Statements.size() > 0) {
        return Statements[0].TokenLiteral();
    } else {
        return "";
    }
}

// Identifier Node
std::string IdentifierNode::TokenLiteral() {
    return token.Literal;
}
void IdentifierNode::expressionNode() {}

