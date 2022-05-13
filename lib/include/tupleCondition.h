#pragma once
#include "lindaTuple.h"
#include "tupleParser.h"
#include <map>

class TupleCondition{
public:
    TupleCondition(){}; /// nie wiem czemu
    TupleCondition(std::vector<Condition> statement);
    bool checkCondition(const uxp::Tuple& tpl) const;
    std::string getShortcut() const; 

private:
    bool checkSingleCondition(std::variant<std::string, u_int32_t, float> singleValue, Condition singleCondition) const;
    std::vector<Condition> statement; 

};
