#include "parserException.h"

#include <map>
#include <string>

using namespace std;

const map<ParserExceptionType, string> parserExcepMap{
    {UNKNOWN_VALUETYPE, "THERE IS UNKNOWN VALUE TYPE"},
    {NO_COLON, "EXPECTED COLON"},
    {EMPTY_CONDITION, "GIVEN CONDITION STRING IS EMPTY"},
    {EMPTY_TUPLE_CONSTRUCTOR, "GIVEN TUPLE CONSTRUCTOR IS EMPTY"},
    {NO_QUOTE_IN_STRING, "QUOTE WAS EXPECTED"},
    {ETX_IN_STRING, "UNCLOSED STRING, ETX IN STRING"},
    {NO_DIGIT_IN_NUMBER, "EXPECTED DIGIT, BUT GIVEN CHAR WASNT DIGIT"},
    {INT_OVERFLOW, "GIVEN NUMBER IS TOO BIG"},
    {NO_EQUAL_SIGN, "EXPECTED EQUAL SIGN"}

};

ParserException::ParserException(ParserExceptionType exceptionType) {
  type = exceptionType;
}
const char* ParserException::what() const noexcept {
  return parserExcepMap.at(type).c_str();
}