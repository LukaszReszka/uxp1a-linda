#pragma once
#include "lindaTuple.h"
#include "tupleParser.h"
#include <map>

class TupleCondition{
public:
    TupleCondition(){}; /// nie wiem czemu
    TupleCondition(std::vector<Condition> statement);
    bool checkCondition(const uxp::Tuple& tpl);
    std::string getShortcut(); 

private:
    bool checkSingleCondition(std::variant<std::string, u_int32_t, float> singleValue, Condition singleCondition);
    std::vector<Condition> statement; 

};
