//
// Created by 김성민 on 2023/04/16.
//

#ifndef KOREANLANGUAGE_EVALUATOR_H
#define KOREANLANGUAGE_EVALUATOR_H

#include "../ast/Ast.h"
#include "../object/Object.h"


class Evaluator {
public:
    Object::Object* Eval(Node* node);
};


#endif //KOREANLANGUAGE_EVALUATOR_H
