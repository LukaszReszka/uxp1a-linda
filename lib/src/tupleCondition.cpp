#include "tupleCondition.h"
#include <cmath>

TupleCondition::TupleCondition(std::string statement)
{
    this->statement = statement + '|';
    initValueTypeMap();
    initOperationTypeMap();
    parsedStatement = parseWholeCondition();
}

std::string TupleCondition::getShortcut()
{
    std::string shortcut = "";
    for (int i = 0; i < parsedStatement.size(); i++)
    {
        switch (parsedStatement[i].valueType)
        {
        case intType:
            shortcut.push_back('I');
            break;
        case floatType:
            shortcut.push_back('F');
            break;
        case stringType:
            shortcut.push_back('S');
            break;
        //default:
        //  throw new Excpetion
        };
    }
    return shortcut;
}

    bool TupleCondition::checkCondition(const uxp::Tuple &tpl)
    {
        auto values = tpl.getValues();
        for (int i = 0; i < parsedStatement.size(); i++)
            if (!checkSingleCondition(values[i], parsedStatement[i]))
                return false;
        return true;
    }

    bool TupleCondition::checkSingleCondition(std::variant<std::string, u_int32_t, float> singleValue, Condition singleCondition)
    {
        switch (singleCondition.operationType)
        {
        case equal:
            return singleCondition.value == singleValue;
        case less:
            return singleCondition.value > singleValue;
        case greater:
            return singleCondition.value < singleValue;
        case less_equal:
            return singleCondition.value >= singleValue;
        case greater_equal:
            return singleCondition.value <= singleValue;
        case everything:
            return true;
        default:
            return false;
        }
    }

    Condition TupleCondition::parseSingleCondition()
    {
        auto condition = Condition();
        condition.valueType = parseValueType();
        // if(currentCharacter() != ':')
        // throw new Excpetion
        currentIndex++;
        condition.operationType = parseOperationType();

        if (condition.valueType == intType && condition.operationType != everything)
            condition.value = std::get<u_int32_t>(parseNumber());
        else if (condition.valueType == floatType && condition.operationType != everything)
            condition.value = std::get<float>(parseNumber());
        else if (condition.valueType == stringType && condition.operationType != everything)
            condition.value = parseString();

        return condition;
    }

    std::string TupleCondition::parseString()
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

    std::string TupleCondition::stringEscaping()
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

    OperationType TupleCondition::parseOperationType()
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

    ValueType TupleCondition::parseValueType()
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

    std::variant<u_int32_t, float> TupleCondition::parseNumber()
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

    std::vector<Condition> TupleCondition::parseWholeCondition()
    {
        currentIndex = -1;
        // if(statement.length <= 0)
        // throw new Excpetion
        auto conditionVector = std::vector<Condition>();
        Condition condition;
        do
        {
            currentIndex++;
            while (skipWhites())
                ;
            condition = parseSingleCondition();
            conditionVector.push_back(condition);
            while (skipWhites())
                ;
        } while (currentCharacter() == ',');
        return conditionVector;
    }

    bool TupleCondition::skipWhites()
    {
        if (isspace(currentCharacter()))
        {
            currentIndex++;
            return true;
        }
        return false;
    }

    char TupleCondition::currentCharacter()
    {
        return statement.at(currentIndex);
    }

    void TupleCondition::initValueTypeMap()
    {
        valueTypeMap.insert(std::make_pair<std::string, ValueType>("integer", intType));
        valueTypeMap.insert(std::make_pair<std::string, ValueType>("float", floatType));
        valueTypeMap.insert(std::make_pair<std::string, ValueType>("string", stringType));
    }

    void TupleCondition::initOperationTypeMap()
    {
        operationTypeMap.insert(std::make_pair<std::string, OperationType>(">", greater));
        operationTypeMap.insert(std::make_pair<std::string, OperationType>(">=", greater_equal));
        operationTypeMap.insert(std::make_pair<std::string, OperationType>("<", less));
        operationTypeMap.insert(std::make_pair<std::string, OperationType>("<=", less_equal));
        operationTypeMap.insert(std::make_pair<std::string, OperationType>("*", everything));
    }

    void TupleCondition::checkIfEnd()
    {
        // if(currentIndex == statement.length()-1)
        // throw new Excpetion
    }