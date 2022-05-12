#include "tupleTypeControler.h"

TupleTypeControler::TupleTypeControler() {}

bool TupleTypeControler::wakeUpOtherClient() {
  std::deque<LindaClient*>::iterator clientIt = clients.begin();
  std::vector<uxp::Tuple>::iterator tupleIt = tuples.begin();
  bool isConditionSatisfied = (*clientIt)->isConditionSatisfied(*tupleIt);
  while (clientIt != clients.end() && !isConditionSatisfied) {
    while (tupleIt != tuples.end() && !isConditionSatisfied) {
      isConditionSatisfied = (*clientIt)->isConditionSatisfied(*tupleIt);
      ++tupleIt;
    }
    if (!isConditionSatisfied) {
      ++clientIt;
      tupleIt = tuples.begin();
    }
  }
  if (clientIt != clients.end()) {
    (*clientIt)->wakeUp();
    return true;
  }
  return false;
}

void TupleTypeControler::addToQue(LindaClient* lindaClient) {
  lockQue();
  clients.push_back(lindaClient);
  unlockQue();
}

void TupleTypeControler::removeFromQue(LindaClient* lindaClient) {
  lockQue();
  std::deque<LindaClient*>::iterator clientIt = clients.begin();
  while (*clientIt != lindaClient && clientIt != clients.end()) {
    ++clientIt;
  }
  if (clientIt != clients.end()) clients.erase(clientIt);
  unlockQue();
}

void TupleTypeControler::lockQue() { clientMtx.lock(); }

void TupleTypeControler::unlockQue() { clientMtx.unlock(); }

void TupleTypeControler::lockTuples() { tuplesMtx.lock(); }

void TupleTypeControler::unlockTuples() { tuplesMtx.unlock(); }

void TupleTypeControler::addTuple(uxp::Tuple& tuple) {
  clientMtx.lock();
  tuplesMtx.lock();
  bool isOtherClientWaked = wakeUpOtherClient();
  tuplesMtx.unlock();
  if (isOtherClientWaked) {
    LindaClientWriter lindaClient = LindaClientWriter();
    addToQue(&lindaClient);
    lindaClient.wait(clientMtx);
    removeFromQue(&lindaClient);
  }
  tuplesMtx.lock();
  tuples.push_back(tuple);
  wakeUpOtherClient();
  clientMtx.unlock();
  tuplesMtx.unlock();
}

std::optional<uxp::Tuple> TupleTypeControler::getTuple(
    const TupleCondition& tupleCond, const Time timeout) {
  clientMtx.lock();
  tuplesMtx.lock();
  bool isOtherClientWaked = wakeUpOtherClient();
  tuplesMtx.unlock();
  LindaClientReader lindaClient = LindaClientReader(tupleCond);
  if (isOtherClientWaked) {
    addToQue(&lindaClient);
    bool wasTimeout = lindaClient.waitFor(clientMtx, timeout);
    removeFromQue(&lindaClient);
    if (wasTimeout) {
      clientMtx.unlock();
      return std::nullopt;
    }
  }

  tuplesMtx.lock();
  std::vector<uxp::Tuple>::iterator tupleIt = tuples.begin();
  bool isConditionSatisfied = lindaClient.isConditionSatisfied(*tupleIt);
  while (tupleIt != tuples.end() && !isConditionSatisfied) {
    isConditionSatisfied = lindaClient.isConditionSatisfied(*tupleIt);
    ++tupleIt;
  }
  uxp::Tuple tuple = *tupleIt;
  tuples.erase(tupleIt);
  wakeUpOtherClient();
  clientMtx.unlock();
  tuplesMtx.unlock();
  return tuple;
}

std::optional<uxp::Tuple> TupleTypeControler::readTuple(
    const TupleCondition& tupleCond, const Time timeout) {
  clientMtx.lock();
  tuplesMtx.lock();
  bool isOtherClientWaked = wakeUpOtherClient();
  tuplesMtx.unlock();
  LindaClientReader lindaClient = LindaClientReader(tupleCond);
  if (isOtherClientWaked) {
    addToQue(&lindaClient);
    lindaClient.waitFor(clientMtx, timeout);
    removeFromQue(&lindaClient);
    addToQue(&lindaClient);
    bool wasTimeout = lindaClient.waitFor(clientMtx, timeout);
    removeFromQue(&lindaClient);
    if (wasTimeout) {
      clientMtx.unlock();
      return std::nullopt;
    }
  }

  tuplesMtx.lock();
  std::vector<uxp::Tuple>::iterator tupleIt = tuples.begin();
  bool isConditionSatisfied = lindaClient.isConditionSatisfied(*tupleIt);
  while (tupleIt != tuples.end() && !isConditionSatisfied) {
    isConditionSatisfied = lindaClient.isConditionSatisfied(*tupleIt);
    ++tupleIt;
  }
  uxp::Tuple tuple = *tupleIt;
  wakeUpOtherClient();
  clientMtx.unlock();
  tuplesMtx.unlock();
  return tuple;
}
