#pragma once

#include "tupleCondition.h"
#include "conditionalVariable.h"

class LindaClient{
public:
    LindaClient(){};

    inline bool isConditionSatisfied(const uxp::Tuple& tuple) {return condition.checkCondition(tuple);};

private:
    TupleCondition condition;
    uxp::ConditionalVariable condVariable;
};