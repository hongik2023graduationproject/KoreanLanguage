//
// Created by 김성민 on 2023/04/16.
//

#include "Evaluator.h"

Object::Object* Evaluator::Eval(Node* node) {
    if (typeid(node) == typeid(IntegerLiteral)) {
        Object::Integer* integer = new Object::Integer;
//        integer->Value = node->value;
        return integer;
    }


    return nullptr;
}
