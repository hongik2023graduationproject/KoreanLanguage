//
// Created by 김성민 on 2023/04/16.
//

#ifndef KOREANLANGUAGE_OBJECT_H
#define KOREANLANGUAGE_OBJECT_H

#include <string>

#define ObjectType std::string

const ObjectType INTEGER_OBJ = "INTEGER";
const ObjectType BOOLEAN_OBJ = "BOOLEAN";

class Object {
public:
    ObjectType Type();
    std::string Inspect();
};


class Integer : public Object {
public:
    int Value;

    ObjectType Type();
    std::string Inspect();
};

class Boolean : public Object {
public:
    bool Value;

    ObjectType Type();
    std::string Inspect();
};


#endif //KOREANLANGUAGE_OBJECT_H
