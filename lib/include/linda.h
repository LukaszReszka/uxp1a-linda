#pragma once
#include <map>
#include <optional>
#include <string>

#include "lindaTuple.h"
#include "mutex.h"
#include "tupleCondition.h"
#include "tupleTypeControler.h"

class Linda {
 public:
  Linda();
  void output(uxp::Tuple &&);
  std::optional<uxp::Tuple> input(const TupleCondition &, Time);
  std::optional<uxp::Tuple> read(const TupleCondition &, Time);

 private:
  std::map<std::string, TupleTypeControler> tupleSpace;
  mutable uxp::mutex mtx;

  void createNewTupleTypeControler(const std::string &tuplePattern);
  bool checkIfTupleSpaceInMap(const std::string &tuplePattern) const;
};