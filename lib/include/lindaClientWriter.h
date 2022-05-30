#pragma once

#include "lindaClient.h"

class LindaClientWriter : public LindaClient {
 public:
  virtual ~LindaClientWriter() = default;
  inline bool isConditionSatisfied(const uxp::Tuple& tuple) const {
    return true;
  };

  void wait(uxp::Mutex& mtx) { condVariable.wait(mtx); }
};