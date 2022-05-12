#pragma once
#include "lindaTuple.h"

using Time = int;

class TupleCondition {
 public:
  bool checkCondition(const uxp::Tuple& tpl) const { return true; };
  Time timeout;
  std::string getShortcut() { return "IS"; }
};