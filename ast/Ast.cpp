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
std::string Program::Debug() {
    std::string s;
    for (auto it : statements) {
        s += it->Debug() + " ";
    }
    return s;
}


// Identifier
std::string Identifier::TokenLiteral() {
    return token.Literal;
}
std::string Identifier::Debug() {
    return "(" + type.Literal + ")" + value;
}

// INTEGER
std::string Integer::TokenLiteral() {
    return token.Literal;
}
std::string Integer::Debug() {
    return std::to_string(value);
}

// Boolean
std::string Boolean::TokenLiteral() {
    return token.Literal;
}
std::string Boolean::Debug() {
    return std::to_string(value);
}

// AssignStatement
std::string AssignStatement::TokenLiteral() {
    return token.Literal;
}
std::string AssignStatement::Debug() {
    return std::string(name->Debug() + " " + TokenLiteral() + " " + value->Debug() + "\n");
}












// ReturnStatement
std::string ReturnStatement::TokenLiteral() {
    return token.Literal;
}
std::string ReturnStatement::Debug() {
    std::string s = TokenLiteral() + " ";
    if (ReturnValue != nullptr) {
        s += ReturnValue->Debug();
    }

    return s;
}



// ExpressionStatement
std::string ExpressionStatement::TokenLiteral() {
    return token.Literal;
}
std::string ExpressionStatement::Debug() {
    if (expression != nullptr) {
        return expression->Debug();
    }

    return "";
}





// PrefixExpression
std::string PrefixExpression::TokenLiteral() {
    return token.Literal;
}
std::string PrefixExpression::Debug() {
    return "(" + Operator + Right->Debug() + ")";
}



// InfixExpression
std::string InfixExpression::TokenLiteral() {
    return token.Literal;
}
std::string InfixExpression::Debug() {
    return "(" + Left->Debug() + " " + Operator + " " + Right->Debug() + ")";
}





// BlockStatement
std::string BlockStatement::TokenLiteral() {
    return token.Literal;
}
std::string BlockStatement::Debug() {
    std::string s;
    for (auto it : Statements) {
        s += it->Debug();
    }
    return s;
}

// IfExpression
std::string IfExpression::TokenLiteral() {
    return token.Literal;
}
std::string IfExpression::Debug() {
    std::string s;
    s += "if" + Condition->Debug() + " " + Consequence->Debug();

    if (Alternative != nullptr) {
        s += "else " + Alternative->Debug();
    }

    return s;
}

std::string FunctionStatement::TokenLiteral() {
    return token.Literal;
}

std::string FunctionStatement::Debug() {
    std::string s = "Function " + name->Debug() + " (";
    for(auto it : parameters){
        s.append(it.first->Debug());
        s.push_back(' ');
        s.append(it.second->Debug());
        s.append(", ");
    }
    s.append(")\n Return Type :" + retType.Literal + "\n");
    s.append(body->Debug());
    return s;
}

