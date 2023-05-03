//
// Created by 김성민 on 2023/04/16.
//

#include "Evaluator.h"

Object::Object* Evaluator::Eval(Node* node) {
    if (typeid(node) == typeid(IntegerLiteral)) {
        IntegerLiteral* temp = dynamic_cast<IntegerLiteral*>(node);
        Object::Integer* integer = new Object::Integer;
        integer->Value = temp->value;
        return integer;
    }


    return nullptr;
}
