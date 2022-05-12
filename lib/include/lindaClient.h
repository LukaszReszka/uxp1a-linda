#pragma once

#include "conditionalVariable.h"
#include "tupleCondition.h"

using Time = int;

class LindaClient {
 public:
  LindaClient(){};

  inline bool isConditionSatisfied(const uxp::Tuple& tuple) const {
    return condition.checkCondition(tuple);
  };

  void wait(uxp::mutex& mtx) { condVariable.wait(mtx); }

  void waitFor(uxp::mutex& mtx, Time time) { condVariable.waitFor(mtx, time); }

  void wakeUp() { condVariable.notify(); }

 private:
  TupleCondition condition;
  uxp::ConditionalVariable condVariable;
};