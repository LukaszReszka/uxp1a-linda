#pragma once

#include "conditionVariable.h"
#include "tupleCondition.h"

using Time = int;

class LindaClient {
 public:
  virtual ~LindaClient() = default;
  virtual bool isConditionSatisfied(const uxp::Tuple& tuple) const = 0;

  void wakeUp() { condVariable.notify(); }

 protected:
  uxp::ConditionVariable condVariable;
};