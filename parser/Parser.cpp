//
// Created by 김성민 on 2023/03/06.
//

#include "Parser.h"


// Parser

Expression* Parser::parseIdentifier() {
    Identifier* identifier = new Identifier;
    identifier->token = curToken;
    identifier->value = curToken.Literal;
    return identifier;
}
Expression* Parser::parseIntegerLiteral() {
    IntegerLiteral* lit = new IntegerLiteral;
    lit->token = curToken;
    try{
        lit->value = stoi(curToken.Literal);
    }catch(std::out_of_range &expn){
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

Expression* Parser::parseBoolean() {
    Boolean* ret = new Boolean;
    ret->token = curToken;
    ret->value = curTokenIs(TRUE);

    return ret;
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
    expression->token = curToken;

    // TODO: 나중에 문법 명세의 조건에 따라 수정해야함
    if (!expectPeek(LPAREN)) {
        return nullptr;
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

    if (!expectPeek(LBRACE)) {
        return nullptr;
    }

    expression->Alternative = parseBlockStatement();

    return expression;
}


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

Program* Parser::ParseProgram() {
    Program* program = new Program; // root node

    while (curToken.Type != Eof) {
        Statement* stmt = parseStatement();

        if (stmt != nullptr) {
            program->statements.push_back(stmt);
        }


        // TODO: 임시로 if문 적용, 어떻게 처리해야할 지 모르곘다.
        if (peekTokenIs(Eof)) {
            break;
        }

        nextToken(); // 마지막 토큰인 Eof 이후에 실행되면 SIGTRAP 오류
    }

    return program;
}


Statement* Parser::parseStatement() {
    if (curToken.Type == 이름 && peekToken.Type == 대입) {
        return parseAssignStatement();
    } else if (curToken.Type == RETURN) {
        return parseReturnStatement();
    } else {
        return parseExpressionStatement();
    }
}

AssignStatement* Parser::parseAssignStatement() {
    AssignStatement *stmt = new AssignStatement;

    stmt->name = new Identifier;
    // TODO: 생성자 만들어서 코드 정리하기
    stmt->name->token = curToken;
    stmt->name->value = curToken.Literal;

    nextToken();
    stmt->token = curToken; // =


    // TODO: EOF을 만날 때까지 표현식을 건너뛴다.
    //      -우항은 아직 패스
    while (!curTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}


ReturnStatement* Parser::parseReturnStatement() {
    ReturnStatement* stmt = new ReturnStatement;
    stmt->token = curToken; // return 토큰

    // TODO: EOF을 만날 때까지 표현식을 건너뛴다.
    //      -우항은 아직 패스
    while (curTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}

ExpressionStatement* Parser::parseExpressionStatement() {
    ExpressionStatement* stmt = new ExpressionStatement;
    stmt->token = curToken;
    stmt->expression = parseExpression(LOWEST); // expression parsing


    // TODO: 우리는 Eof로 처리하므로 다음 토큰이 Eof가 아니라면 에러 처리를 해야한다.
    //      -식별자만 한 줄에 주어질 경우 에러로 처리하지 않으려면 에러처리를 안해도 될 거 같다.

    while (!peekTokenIs(Eof)) {
        nextToken();
    }

    return stmt;
}

Expression* Parser::parseExpression(int precedence) {
    if (prefixParseFns.find(curToken.Type) == prefixParseFns.end()) {
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

std::vector<std::string> Parser::Errors() {
    return errors;
}

void Parser::peekError(TokenType t) {
    std::string msg = "예상 토큰은 " + t + "입니다. 하지만 실제 토큰은 " + peekToken.Type + "입니다.\n";
    errors.push_back(msg);
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