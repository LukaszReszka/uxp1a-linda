#pragma once

#include "conditionalVariable.h"
#include "tupleCondition.h"

using Time = int;

class LindaClient {
 public:
  virtual bool isConditionSatisfied(const uxp::Tuple& tuple) const;

  void wakeUp() { condVariable.notify(); }

 protected:
  uxp::ConditionalVariable condVariable;
};