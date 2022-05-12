#pragma once

#include "lindaClient.h"

class LindaClientWriter : public LindaClient {
 public:
  inline bool isConditionSatisfied(const uxp::Tuple& tuple) const {
    return true;
  };
  void wait(uxp::mutex& mtx) { condVariable.wait(mtx); }
};