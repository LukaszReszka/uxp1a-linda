#include "conditionVariableException.h"

#include <map>
#include <string>

using namespace std;

const map<ConditionVariableExceptionType, string> mtxExcepMap{
    {CANT_INIT_ATTRIBUTES, "CANNOT INIT CONDITION_VARIABLE ATTRIBUTES"},
    {CANT_SET_ATTRIBUTES, "CANNOT SET CONDITION_VARIABLE ATTRIBUTES"},
    {CANT_DESTROY_ATTRIBUTES, "CANNOT DESTROY CONDITION_VARIABLE ATTRIBUTES"},
    {CANT_DESTROY_CONDITION_VARIABLE, "CANNOT DESTROY CONDITION_VARIABLE"},
    {WAIT_ERROR, "CANNOT WAIT ON CONDITION_VARIABLE"},
    {UNLOCK_ERROR, "CANNOT UNLOCK ON CONDITION_VARIABLE"},
    {CANT_INIT_CONDITION_VARIABLE, "CANNOT INIT CONDITION_VARIABLE"}};

ConditionVariableException::ConditionVariableException(ConditionVariableExceptionType exceptionType) {
  type = exceptionType;
}
const char* ConditionVariableException::what() const noexcept {
  return mtxExcepMap.at(type).c_str();
}