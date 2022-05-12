#pragma once

#include "lindaClient.h"

class LindaClientReader : public LindaClient {
 public:
  virtual ~LindaClientReader() = default;
  LindaClientReader(const TupleCondition& tupleCond) { condition = tupleCond; }

  inline bool isConditionSatisfied(const uxp::Tuple& tuple) const {
    return condition.checkCondition(tuple);
  };

  bool waitFor(uxp::mutex& mtx, Time time) {
    condVariable.waitFor(mtx, time);
    return false;
  }

 private:
  TupleCondition condition;
};