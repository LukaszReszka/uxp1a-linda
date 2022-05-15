#pragma once
#include <exception>

enum ParserExceptionType {
  UNKNOWN_VALUETYPE,
  NO_COLON,
  EMPTY_CONDITION,
  EMPTY_TUPLE_CONSTRUCTOR,
  NO_QUOTE_IN_STRING,
  ETX_IN_STRING,
  NO_DIGIT_IN_NUMBER,
  INT_OVERFLOW,
  NO_EQUAL_SIGN
};

class ParserException : public std::exception {
 public:
  explicit ParserException(ParserExceptionType exceptionType);

  virtual const char* what() const noexcept;

  virtual ~ParserException() = default;

 private:
  ParserExceptionType type;
};