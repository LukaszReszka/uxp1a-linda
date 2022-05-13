#include "tupleValuesParser.h"

TupleValuesParser::TupleValuesParser(std::string statement) : TupleParser(statement)
{
}


SingleTupleValue TupleValuesParser::parseSingleValue()
{
    SingleTupleValue tupleValue;
    auto valueType = parseValueType();
    while (skipWhites());
    // if(currentCharacter() != '=')
    // throw new Excpetion
    currentIndex++;
    while (skipWhites());
    if (valueType == intType)
        tupleValue = std::get<u_int32_t>(parseNumber());
    else if (valueType == floatType)
        tupleValue = std::get<float>(parseNumber());
    else if (valueType == stringType)
        tupleValue = parseString();

    return tupleValue;
}


TupleValues TupleValuesParser::parseAllValues()
{
    currentIndex = -1;
    auto tupleValues = std::vector<SingleTupleValue>();
    SingleTupleValue singleTupleValue;
    do
    {
        currentIndex++;
        while (skipWhites())
            ;
        singleTupleValue = parseSingleValue();
        tupleValues.push_back(singleTupleValue);
        while (skipWhites())
            ;
    } while (currentCharacter() == ',');
    return tupleValues;
}