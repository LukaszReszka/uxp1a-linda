#include "tupleValuesParser.h"
#include "parserException.h"

TupleValuesParser::TupleValuesParser(std::string statement) : TupleParser(statement)
{
}

SingleTupleValue TupleValuesParser::parseSingleValue()
{
    SingleTupleValue tupleValue;
    if(currentCharacter() == '|')
        throw ParserException(EXPECTED_NEXT_STATEMENT);
    auto valueType = parseValueType();
    while (skipWhites())
        ;
    if (currentCharacter() != '=')
        throw ParserException(NO_EQUAL_SIGN);
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
    if(currentCharacter() != '|')
        throw ParserException(WRONG_SYNTAX);
    return tupleValues;
}