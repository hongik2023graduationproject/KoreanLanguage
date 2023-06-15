//
// Created by 김성민 on 2023/03/06.
//

#include "Parser.h"


Program* Parser::ParseProgram() {
    Program* program = new Program; // root node

    while (curToken.Type != Eof) {
        Statement* stmt = parseStatement();
        if (stmt != nullptr) {
            program->statements.push_back(stmt);
        }
    }
    return program;
}

Statement* Parser::parseStatement() {
    if (curToken.Type == INTEGER || curToken.Type == FLOAT || curToken.Type == BOOLEAN) {
        return parseAssignStatement();
    }
//    } else if (curToken.Type == RETURN) {
//        return parseReturnStatement();
//    } else if (curToken.Type == FUNCTION){
//        return parseFunctionStatement();
//    } else {
//        return parseExpressionStatement();
//    }
}

AssignStatement* Parser::parseAssignStatement() {
    AssignStatement *stmt = new AssignStatement();

    if (!curTokenIs(INTEGER) && curTokenIs(FLOAT) && curTokenIs(BOOLEAN)) {
        // error
    }
    Identifier* ident = new Identifier;
    ident->type = curToken;
    nextToken();
    checkSpace();


    ident->token = curToken;
    ident->value = curToken.Literal;
    stmt->name = ident;
    nextToken();
    checkSpace();

    stmt->token = curToken; // =
    nextToken();
    checkSpace();


    stmt->value = parseExpression(LOWEST);

    // TODO: 이 구문에 대해 어떻게 개선해야할까
    while (!curTokenIs(Eof)) {
        nextToken();
    }


    return stmt;
}

Expression* Parser::parseExpression(int precedence) {
    if (prefixParseFns.find(curToken.Type) == prefixParseFns.end()) { // identifier 포함
        noPrefixParseFnError(curToken.Type);
        return nullptr;
    }

    auto prefix = prefixParseFns.find(curToken.Type)->second;
    Expression* leftExp = (this->*prefix)();

    while (!peekTokenIs(Eof) && precedence < peekPrecedence()) {
        if (infixParseFns.find(peekToken.Type) == infixParseFns.end()) {
            return leftExp;
        }
        auto infix = infixParseFns.find(peekToken.Type)->second;

        nextToken();

        leftExp = (this->*infix)(leftExp);
    }

    return leftExp;
}





































Expression* Parser::parseIdentifier() {
    Identifier* identifier = new Identifier;
    identifier->token = curToken;
    identifier->value = curToken.Literal;

    return identifier;
}
Expression* Parser::parseBoolean() {
    Boolean* ret = new Boolean;
    ret->token = curToken;
    ret->value = curTokenIs(TRUE);

    return ret;
}
Expression* Parser::parseIntegerLiteral() {
    Integer* lit = new Integer;
    lit->token = curToken;
    try {
        lit->value = stoi(curToken.Literal);
    } catch(std::out_of_range &expn){
        this->errors.emplace_back(expn.what());
    }
    // string to integer처리 중 발생하는 에러처리 필요 -> std::exception 이용
    return lit;
}
Expression* Parser::parsePrefixExpression() {
    PrefixExpression* expression = new PrefixExpression;
    expression->token = curToken;
    expression->Operator = curToken.Literal;

    nextToken();
    expression->Right = parseExpression(PREFIX);

    return expression;
}











ReturnStatement* Parser::parseReturnStatement() {
    ReturnStatement* stmt = new ReturnStatement;
    stmt->token = curToken; // return 토큰
    nextToken();

    stmt->ReturnValue = parseExpression(LOWEST);
    while (curTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}

FunctionStatement * Parser::parseFunctionStatement() {
    // 'fn' <type> <ident> '(' <param> ')' ['->' <type>] { block }
    FunctionStatement *lit = new FunctionStatement;
    lit->token = curToken; // fn

    // Type Assignment
    nextToken();
    lit->retType = curToken; // return type

    nextToken();
//    lit->name = (Identifier *) parseIdentifier(); // ident

    nextToken();
    if (curToken.Type != LPAREN) {
        return nullptr; // Error
    }

    nextToken();
    parseFunctionParameters(lit->parameters);


    if (peekToken.Type == RARROW){
        nextToken();
        nextToken();
//        lit->retType = (Identifier *)parseIdentifier(); // Type 처리 : 일단은 Identifier 로 넘기자
    }

    if (!expectPeek(LBRACE)){
        return nullptr; // Error
    }

    lit->body = parseBlockStatement();

    return lit;
}

void Parser::parseFunctionParameters(std::vector<std::pair<Identifier *, Identifier *>> & parameters){
    if (peekToken.Type == RPAREN){
        return;
    }


    Identifier* paramType = new Identifier;
    Identifier* paramName = new Identifier;
    paramType->token = curToken;
    paramType->value = curToken.Literal;

    nextToken();
    paramName->token = curToken;
    paramName->value = curToken.Literal;
    parameters.emplace_back(paramType, paramName);

    while (peekToken.Type == COMMA){
        nextToken();
        nextToken();
        paramType = new Identifier;
        paramType->token = curToken;
        paramType->value = curToken.Literal;

        nextToken();
        paramName = new Identifier;
        paramName->token = curToken;
        paramName->value = curToken.Literal;

        parameters.emplace_back(paramType, paramName);
    }

    if (!expectPeek(RPAREN)){
        // Todo : 에러 처리, null 반환 불가능 -> bool 반환하여 false면 caller에서 null반환 하도록 하자!
        return;
    }
};
















Expression* Parser::parseInfixExpression(Expression* left) {
    InfixExpression* expression = new InfixExpression;
    expression->token = curToken;
    expression->Operator = curToken.Literal;
    expression->Left = left;

    int precedence = curPrecedence();
    nextToken();
    expression->Right = parseExpression(precedence);

    return expression;
}



Expression* Parser::parseGroupedExpression() {
    nextToken();

    Expression* exp = parseExpression(LOWEST);

    if (!expectPeek(RPAREN)) {
        return nullptr;
    }

    return exp;
}

Expression* Parser::parseIfExpression() {
    IfExpression* expression = new IfExpression;
    expression->token = curToken; // if

    if (!expectPeek(LPAREN)) {
        return nullptr; // Error로 처리해야 하는지?
    }

    nextToken();

    expression->Condition = parseExpression(LOWEST);

    if (!expectPeek(RPAREN)) {
        return nullptr;
    }

    if (!expectPeek(LBRACE)) {
        return nullptr;
    }

    expression->Consequence = parseBlockStatement();

    if (curToken.Type == RBRACE) { // expectPeek 오류로 인해 수정, 위의 함수 반환 후 curToken이 RBRACE임
        return nullptr;
    }

    // todo : else token 없이 바로 alternative 진행중인 코드 수정

    // TODO: Alternative가 parseBlockStatement가 맞는지... 재귀적으로 구성할 꺼면 If Expression이 적절해보임
    expression->Alternative = parseBlockStatement();

    return expression;
}


// Thinking: parseBlockStatement 내부에서 {} 을 처리하자. (나중엔 들여쓰기)
BlockStatement* Parser::parseBlockStatement() {
    BlockStatement* block = new BlockStatement;
    block->token = curToken;
    block->Statements.clear();

    nextToken();

    while (!curTokenIs(RBRACE) && !curTokenIs(Eof)) {
        Statement* stmt = parseStatement();
        if (stmt != nullptr) {
            block->Statements.push_back(stmt);
        }
        nextToken();
    }

    return block;
}

void Parser::nextToken() {
    curToken = peekToken;
    peekToken = lexer.NextToken();
}






ExpressionStatement* Parser::parseExpressionStatement() {
    ExpressionStatement* stmt = new ExpressionStatement;
    stmt->token = curToken;
    stmt->expression = parseExpression(LOWEST); // expression parsing


    // TODO: 우리는 Eof로 처리하므로 다음 토큰이 Eof가 아니라면 에러 처리를 해야한다.
    //      -식별자만 한 줄에 주어질 경우 에러로 처리하지 않으려면 에러처리를 안해도 될 거 EQ.

    while (!peekTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}



bool Parser::expectPeek(TokenType t) {
    if (peekToken.Type == t) {
        nextToken();
        return true;
    } else {
        peekError(t);
        return false;
    }
}

bool Parser::curTokenIs(TokenType t) {
    return curToken.Type == t;
}

bool Parser::peekTokenIs(TokenType t) {
    return peekToken.Type == t;
}



void Parser::noPrefixParseFnError(std::string t) {
    errors.push_back("no prefix parse function for " + t + " found.");
}


int Parser::curPrecedence() {
    // TODO: find 함수를 두 번 사용해서 비효율적 나중에 수정하기
   if (precedences.find(curToken.Type) != precedences.end()) {
       return precedences.find(curToken.Type)->second;
   }
   return LOWEST;
}

int Parser::peekPrecedence() {
    // TODO: find 함수를 두 번 사용해서 비효율적 나중에 수정하기
    if (precedences.find(peekToken.Type) != precedences.end()) {
        return precedences.find(peekToken.Type)->second;
    }
    return LOWEST;
}

void Parser::checkSpace() {
    if (!curTokenIs(SPACE)) {
        // error
    }
    nextToken();
}


// errors
std::vector<std::string> Parser::Errors() {
    return errors;
}

void Parser::peekError(TokenType t) {
    std::string msg = "예상 토큰은 " + t + "입니다. 하지만 실제 토큰은 " + peekToken.Type + "입니다.\n";
    errors.push_back(msg);
}

void Parser::makeError(TokenType t) {
    std::string msg = "예상 토큰은 " + t + "입니다. 하지만 실제 토큰은 " + peekToken.Type + "입니다.\n";
}