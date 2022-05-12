#pragma once
#include <deque>
#include <map>
#include <vector>

#include "lindaClient.h"
#include "lindaTuple.h"
#include "mutex"
#include "tupleCondition.h"

using Time = int;

class TupleTypeControler {
 public:
  TupleTypeControler();
  bool checkOperations();
  void addToQue(LindaClient& lindaClient);
  void removeFromQue(LindaClient& lindaClient);
  void lockQue();
  void unlockQue();
  void lockTuples();
  void unlockTuples();
  bool wakeUpOtherClient();
  void addTuple(uxp::Tuple& tuple);
  uxp::Tuple getTuple(const TupleCondition& tupleCond, const Time timeout);
  uxp::Tuple readTuple(const TupleCondition& tupleCond, const Time timeout);

 private:
  std::vector<uxp::Tuple> tuples;
  uxp::mutex tuplesMtx;
  std::deque<LindaClient> clients;
  uxp::mutex clientMtx;
  int tupleKey;
};