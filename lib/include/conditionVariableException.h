#pragma once
#include <exception>

enum ConditionVariableExceptionType {
  CANT_INIT_ATTRIBUTES,
  CANT_SET_ATTRIBUTES,
  CANT_DESTROY_ATTRIBUTES,
  CANT_DESTROY_CONDITION_VARIABLE,
  WAIT_ERROR,
  UNLOCK_ERROR,
  CANT_INIT_CONDITION_VARIABLE
};

class ConditionVariableException : public std::exception {
 public:
  explicit ConditionVariableException(ConditionVariableExceptionType exceptionType);

  virtual const char* what() const noexcept;

  virtual ~ConditionVariableException() = default;

 private:
  ConditionVariableExceptionType type;
};