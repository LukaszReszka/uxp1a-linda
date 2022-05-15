#pragma once
#include <deque>
#include <map>
#include <optional>
#include <vector>

#include "lindaClient.h"
#include "lindaClientReader.h"
#include "lindaClientWriter.h"
#include "lindaTuple.h"
#include "tupleCondition.h"

using Time = int;

class TupleTypeControler {
 public:
  TupleTypeControler();
  TupleTypeControler(const TupleTypeControler&) = delete;
  TupleTypeControler(TupleTypeControler&&) = delete;
  
  void operator=(const TupleTypeControler&) = delete;
  void operator=(TupleTypeControler&&) = delete;

  void addTuple(uxp::Tuple& tuple);
  std::optional<uxp::Tuple> getTuple(const TupleCondition& tupleCond,
                                     const Time timeout);
  std::optional<uxp::Tuple> readTuple(const TupleCondition& tupleCond,
                                      const Time timeout);

 private:
  std::vector<uxp::Tuple> tuples;
  uxp::mutex tuplesMtx;
  std::deque<LindaClient*> clients;
  uxp::mutex clientMtx;
  bool wakeUpOtherClient();
  void addToQue(LindaClient* lindaClient);
  void removeFromQue(LindaClient* lindaClient);
  void lockQue();
  void unlockQue();
  void lockTuples();
  void unlockTuples();
};