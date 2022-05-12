#pragma once
#include "lindaTuple.h"


class TupleCondition{
public:
    bool checkCondition(const uxp::Tuple& tpl) const {return true;};
    std::string getShortcut(){return "IS";}
};