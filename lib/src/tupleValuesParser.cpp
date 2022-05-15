#include "tupleValuesParser.h"
#include "parserException.h"

TupleValuesParser::TupleValuesParser(std::string statement) : TupleParser(statement)
{
}

SingleTupleValue TupleValuesParser::parseSingleValue()
{
    SingleTupleValue tupleValue;
    auto valueType = parseValueType();
    while (skipWhites())
        ;
    if (currentCharacter() != '=')
        throw new ParserException(NO_EQUAL_SIGN);
    currentIndex++;
    while (skipWhites())
        ;
    return parseValue(valueType);
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