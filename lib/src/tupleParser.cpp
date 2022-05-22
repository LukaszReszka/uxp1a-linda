#include "tupleParser.h"
#include "parserException.h"
#include <cmath>

TupleParser::TupleParser(std::string statement)
{
    if (statement.length() <= 0)
        throw ParserException(EMPTY_TUPLE_CONSTRUCTOR);
    this->statement = statement + '|';
    initValueTypeMap();
    initOperationTypeMap();
}

std::string TupleParser::parseString()
{
    if (currentCharacter() != '"')
        throw ParserException(NO_QUOTE_IN_STRING);
    std::string value = "";
    currentIndex++;
    while (currentCharacter() != '"')
    {
        checkIfEnd();
        if (currentCharacter() == '!')
            value += stringEscaping();
        else
        {
            value.push_back(currentCharacter());
            currentIndex++;
        }
    }
    currentIndex++;
    return value;
}

std::string TupleParser::stringEscaping()
{
    std::string value = "";
    currentIndex++;
    if (currentCharacter() == '"')
    {
        value.push_back('"');
        currentIndex++;
    }
    else
    {
        value.push_back('!');
        if (currentCharacter() != '!')
        {
            checkIfEnd();
            value.push_back(currentCharacter());
            currentIndex++;
        }
    }
    return value;
}

OperationType TupleParser::parseOperationType()
{
    if (!isdigit(currentCharacter()) && currentCharacter() != '\"')
    {
        std::string operation(1, currentCharacter());
        auto itOperationType = operationTypeMap.find(operation);
        OperationType operationType;
        if (itOperationType != operationTypeMap.end())
            operationType = itOperationType->second;

        currentIndex++;
        if (operationType == everything)
            return operationType;
        operation.push_back(currentCharacter());

        itOperationType = operationTypeMap.find(operation);
        if (itOperationType != operationTypeMap.end())
        {
            currentIndex++;
            return itOperationType->second;
        }
        return operationType;
    }
    else
        return equal;
}

ValueType TupleParser::parseValueType()
{
    std::string value = "";
    value.push_back(currentCharacter());
    currentIndex++;
    while (isalpha(currentCharacter()))
    {
        value.push_back(currentCharacter());
        currentIndex++;
    }
    auto itValueType = valueTypeMap.find(value);
    if (itValueType != valueTypeMap.end())
        return itValueType->second;
    else
        throw ParserException(UNKNOWN_VALUETYPE);
}

SingleTupleValue TupleParser::parseValue(ValueType valueType)
{
    SingleTupleValue tupleValue;
    while (skipWhites())
        ;
    if (valueType == intType)
        tupleValue = std::get<u_int32_t>(parseNumber());
    else if (valueType == floatType)
    {
        auto val = parseNumber();
        if (val.index() == 0)
            tupleValue = (float)std::get<u_int32_t>(val);
        else
            tupleValue = std::get<float>(val);
    }
    else if (valueType == stringType)
        tupleValue = parseString();

    return tupleValue;
}

std::variant<u_int32_t, float> TupleParser::parseNumber()
{
    if (!isdigit(currentCharacter()))
        throw ParserException(NO_DIGIT_IN_NUMBER);

    u_int32_t int_part = 0;
    int_part += (u_int32_t)(currentCharacter() - '0');
    currentIndex++;
    while (isdigit(currentCharacter()))
    {
        u_int32_t digit = (u_int32_t)(currentCharacter() - '0');
        if ((int_part < 214748364) || (int_part == 214748364 && digit <= 7))
            int_part = int_part * 10 + digit;
        else
            throw ParserException(INT_OVERFLOW);
        currentIndex++;
    }
    if (currentCharacter() == '.')
    {
        currentIndex++;
        u_int32_t fraction_part = 0;
        u_int32_t decimal_places = 0;
        while (isdigit(currentCharacter()))
        {
            u_int32_t digit = (u_int32_t)(currentCharacter() - '0');
            if ((fraction_part < 214748364) || (fraction_part == 214748364 && digit < 7))
                fraction_part = fraction_part * 10 + digit;
            else
                throw ParserException(INT_OVERFLOW);

            decimal_places++;
            currentIndex++;
        }
        return int_part + fraction_part / (float)pow(10, decimal_places);
    }
    return int_part;
}

bool TupleParser::skipWhites()
{
    if (isspace(currentCharacter()))
    {
        currentIndex++;
        return true;
    }
    return false;
}

char TupleParser::currentCharacter()
{
    return statement.at(currentIndex);
}

void TupleParser::initValueTypeMap()
{
    valueTypeMap.insert(std::make_pair<std::string, ValueType>("integer", intType));
    valueTypeMap.insert(std::make_pair<std::string, ValueType>("float", floatType));
    valueTypeMap.insert(std::make_pair<std::string, ValueType>("string", stringType));
}

void TupleParser::initOperationTypeMap()
{
    operationTypeMap.insert(std::make_pair<std::string, OperationType>(">", greater));
    operationTypeMap.insert(std::make_pair<std::string, OperationType>(">=", greater_equal));
    operationTypeMap.insert(std::make_pair<std::string, OperationType>("<", less));
    operationTypeMap.insert(std::make_pair<std::string, OperationType>("<=", less_equal));
    operationTypeMap.insert(std::make_pair<std::string, OperationType>("*", everything));
}

void TupleParser::checkIfEnd()
{
    if (currentIndex == statement.length() - 1)
        throw ParserException(ETX_IN_STRING);
}