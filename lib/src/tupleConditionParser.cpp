#include "tupleConditionParser.h"

TupleConditionParser::TupleConditionParser(std::string statement) : TupleParser(statement)
{
}


Condition TupleConditionParser::parseSingleCondition()
{
    auto condition = Condition();
    condition.valueType = parseValueType();
    while (skipWhites());
    // if(currentCharacter() != ':')
    // throw new Excpetion
    currentIndex++;
    condition.operationType = parseOperationType();
    while (skipWhites());
    if(condition.operationType == everything)
        return condition;

    condition.value = parseValue(condition.valueType);

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