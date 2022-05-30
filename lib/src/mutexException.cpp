#include "mutexException.h"

#include <map>
#include <string>

using namespace std;

const map<MutexExceptionType, string> mtxExcepMap{
    {CANT_INIT_ATTRIBUTES, "CANNOT INIT MUTEX ATTRIBUTES"},
    {CANT_SET_ATTRIBUTES, "CANNOT SET MUTEX ATTRIBUTES"},
    {CANT_DESTROY_ATTRIBUTES, "CANNOT DESTROY MUTEX ATTRIBUTES"},
    {CANT_DESTROY_MUTEX, "CANNOT DESTROY MUTEX"},
    {LOCK_ERROR, "CANNOT LOCK ON MUTEX"},
    {UNLOCK_ERROR, "CANNOT UNLOCK ON MUTEX"},
    {CANT_INIT_MUTEX, "CANNOT INIT MUTEX"}};

MutexException::MutexException(MutexExceptionType exceptionType) {
  type = exceptionType;
}
const char* MutexException::what() const noexcept {
  return mtxExcepMap.at(type).c_str();
}