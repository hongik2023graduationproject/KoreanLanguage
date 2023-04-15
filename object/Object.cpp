//
// Created by 김성민 on 2023/04/16.
//

#include "Object.h"

// Integer
ObjectType Integer::Type() {
    return INTEGER_OBJ;
}

std::string Integer::Inspect() {
    return std::to_string(Value);
}


// Boolean
ObjectType Boolean::Type() {
    return BOOLEAN_OBJ;
}

std::string Boolean::Inspect() {
    return (Value ? "True" : "False");
}


