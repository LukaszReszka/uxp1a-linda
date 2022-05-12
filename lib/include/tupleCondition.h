#pragma once
#include "lindaTuple.h"
#include <map>

enum ValueType
{
    stringType,
    intType,
    floatType
};

enum OperationType
{
    equal,
    less,
    less_equal,
    greater,
    greater_equal,
    everything
};

struct Condition
{
    ValueType valueType;
    OperationType operationType;
    std::variant<std::string, u_int32_t, float> value;
};

class TupleCondition{
public:
    TupleCondition(){};
    TupleCondition(std::string statement);
    bool checkCondition(const uxp::Tuple& tpl);
    std::string getShortcut(); 

private:
    bool checkSingleCondition(std::variant<std::string, u_int32_t, float> singleValue, Condition singleCondition);
    std::vector<Condition> parseWholeCondition();
    Condition parseSingleCondition();
    std::string parseString();
    std::variant<u_int32_t, float> parseNumber();
    void initValueTypeMap();
    void initOperationTypeMap();
    char currentCharacter();
    void checkIfEnd();
    OperationType parseOperationType();
    ValueType parseValueType();
    std::string stringEscaping();
    bool skipWhites();
    std::map<std::string, ValueType> valueTypeMap;
    std::map<std::string, OperationType> operationTypeMap;
    std::string statement;
    std::vector<Condition> parsedStatement; 
    uint currentIndex;
};
