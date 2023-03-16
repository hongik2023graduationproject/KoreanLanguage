//
// Created by 김성민 on 2023/03/09.
//

#include "Ast.h"

// StatementNode
std::string StatementNode::TokenLiteral() {
    return "";
}



// Program
Program::Program() {
    statements.clear();
}

std::string Program::TokenLiteral() {
    if (statements.size() > 0) {
        return statements[0].TokenLiteral();
    } else {
        return "";
    }
}

// Identifier Node
std::string IdentifierNode::TokenLiteral() {
    return token.Literal;
}
void IdentifierNode::expressionNode() {}

