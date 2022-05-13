#include "tupleConditionParser.h"

TupleConditionParser::TupleConditionParser(std::string statement) : TupleParser(statement)
{
}


Condition TupleConditionParser::parseSingleCondition()
{
    auto condition = Condition();
    condition.valueType = parseValueType();
    // if(currentCharacter() != ':')
    // throw new Excpetion
    currentIndex++;
    condition.operationType = parseOperationType();
    if(condition.operationType == everything)
        return condition;

    if (condition.valueType == intType)
        condition.value = std::get<u_int32_t>(parseNumber());
    else if (condition.valueType == floatType)
        condition.value = std::get<float>(parseNumber());
    else if (condition.valueType == stringType)
        condition.value = parseString();

    return condition;
}


std::vector<Condition> TupleConditionParser::parseWholeCondition()
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