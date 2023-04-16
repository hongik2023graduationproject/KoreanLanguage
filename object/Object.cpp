//
// Created by 김성민 on 2023/04/16.
//

#include "Object.h"

// Integer
ObjectType Object::Integer::Type() {
    return INTEGER_OBJ;
}

std::string Object::Integer::Inspect() {
    return std::to_string(Value);
}


// Boolean
ObjectType Object::Boolean::Type() {
    return BOOLEAN_OBJ;
}

std::string Object::Boolean::Inspect() {
    return (Value ? "true" : "false");
}


// Null
ObjectType Object::Null::Type() {
    return NULL_OBJ;
}

std::string Object::Null::Inspect() {
    return "null";
}


