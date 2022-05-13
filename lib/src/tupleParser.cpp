#include "tupleParser.h"
#include <cmath>

TupleParser::TupleParser(std::string statement)
{
    // if(statement.length <= 0)
    // throw new Excpetion
    this->statement = statement + '|';
    initValueTypeMap();
    initOperationTypeMap();
}

std::string TupleParser::parseString()
{
    // if (currentCharacter() != '"')
    //  throw new Excpetion
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
        currentIndex++;

        itOperationType = operationTypeMap.find(operation);
        if (itOperationType != operationTypeMap.end())
            return itOperationType->second;
        // else
        // throw new Excpetion
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
    // else
    // throw new Excpetion
}

std::variant<u_int32_t, float> TupleParser::parseNumber()
{
    // if(!isdigit(currentCharacter()))
    // throw new Excpetion

    u_int32_t int_part = 0;
    int_part += (u_int32_t)(currentCharacter() - '0');
    currentIndex++;
    while (isdigit(currentCharacter()))
    {
        u_int32_t digit = (u_int32_t)(currentCharacter() - '0');
        if ((int_part < 214748364) || (int_part == 214748364 && digit <= 7))
            int_part = int_part * 10 + digit;
        // else
        // throw new Excpetion
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
            // else
            // throw new Excpetion

            decimal_places++;
            currentIndex++;
        }
        return int_part + fraction_part / (float)pow(10, decimal_places);
    }
    return int_part;

    // else
    // throw new Excpetion
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
    // if(currentIndex == statement.length()-1)
    // throw new Excpetion
}