#include "conditionVariable.h"

#include <time.h>

#include <iostream>

#include "conditionVariableException.h"

uxp::ConditionVariable::ConditionVariable() {
  if (pthread_cond_init(&conditionVariable, NULL) != 0)
    throw ConditionVariableException(CANT_INIT_CONDITION_VARIABLE);
}

uxp::ConditionVariable::~ConditionVariable() noexcept(false) {
  try {
    if (pthread_cond_destroy(&conditionVariable) != 0)
      throw ConditionVariableException(CANT_DESTROY_CONDITION_VARIABLE);
  } catch (ConditionVariableException& excp) {
    std::cerr << excp.what() << std::endl;
  }
}

void uxp::ConditionVariable::wait(uxp::mutex& mutex) {
  if (pthread_cond_wait(&conditionVariable, &mutex.mtx) != 0)
    throw ConditionVariableException(WAIT_ERROR);
}

bool uxp::ConditionVariable::waitFor(uxp::mutex& mtx, Time timeInSec) {
  clock_gettime(CLOCK_REALTIME, &ts);
  ts.tv_sec += timeInSec;
  int result = pthread_cond_timedwait(&conditionVariable, &mtx.mtx, &ts);
  if (result == 0) {
    return false;
  } else if (result == ETIMEDOUT) {
    return true;
  } else {
    throw ConditionVariableException(WAIT_ERROR);
  }
}

void uxp::ConditionVariable::notify() {
  if (pthread_cond_signal(&conditionVariable) != 0)
    throw ConditionVariableException(UNLOCK_ERROR);
}