#pragma once

#include "lindaClient.h"

class LindaClientReader : public LindaClient {
 public:
  LindaClientReader(const TupleCondition& tupleCond) { condition = tupleCond; }

  inline bool isConditionSatisfied(const uxp::Tuple& tuple) const {
    return condition.checkCondition(tuple);
  };

  void waitFor(uxp::mutex& mtx, Time time) { condVariable.waitFor(mtx, time); }

 private:
  TupleCondition condition;
};