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

class TupleParser
{
public:    
    TupleParser(std::string statement); 
    virtual ~TupleParser(){};

protected:
    std::string parseString();
    std::variant<u_int32_t, float> parseNumber();
    char currentCharacter();
    void checkIfEnd();
    OperationType parseOperationType();
    ValueType parseValueType();
    std::string stringEscaping();
    bool skipWhites();
    std::string statement;
    uint currentIndex;
    std::map<std::string, ValueType> valueTypeMap;
    std::map<std::string, OperationType> operationTypeMap;
    void initValueTypeMap();
    void initOperationTypeMap();

};