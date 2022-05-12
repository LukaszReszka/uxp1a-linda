#pragma once

#include "conditionalVariable.h"
#include "tupleCondition.h"

using Time = int;

class LindaClient {
 public:
  virtual ~LindaClient() = 0;
  virtual bool isConditionSatisfied(const uxp::Tuple& tuple) const = 0;

  void wakeUp() { condVariable.notify(); }

 protected:
  uxp::ConditionalVariable condVariable;
};