#include "linda.h"

#include <algorithm>
#include <string>
#include <tuple>

#include "mutexException.h"

using namespace std;

Linda::Linda() {}

void Linda::output(uxp::Tuple&& tuple) {
  string pattern = tuple.getPatternShortcut();
  try {
    if (!checkIfTupleSpaceInMap(pattern)) {
      createNewTupleTypeControler(pattern);
    }
    TupleTypeControler& controller = tupleSpace.at(pattern);
    controller.addTuple(tuple);
  } catch (MutexException e) {
    // TODO
  }
}

optional<uxp::Tuple> Linda::input(const TupleCondition& tupleCondition,
                                  Time timeout) {
  string pattern = tupleCondition.getShortcut();
  try {
    if (!checkIfTupleSpaceInMap(pattern)) {
      createNewTupleTypeControler(pattern);
    }
    TupleTypeControler& controller = tupleSpace.at(pattern);
    return controller.getTuple(tupleCondition, timeout);
  } catch (MutexException e) {
    // TODO
  }
}

optional<uxp::Tuple> Linda::read(const TupleCondition& tupleCondition,
                                 Time timeout) {
  string pattern = tupleCondition.getShortcut();
  try {
    if (!checkIfTupleSpaceInMap(pattern)) {
      createNewTupleTypeControler(pattern);
    }
    TupleTypeControler& controller = tupleSpace.at(pattern);
    return controller.readTuple(tupleCondition, timeout);
  } catch (MutexException e) {
    // TODO
  }
}

void Linda::createNewTupleTypeControler(const std::string& tuplePattern) {
  mtx.lock();
  tupleSpace[tuplePattern];
  mtx.unlock();
}

bool Linda::checkIfTupleSpaceInMap(const string& tupleShortcut) const {
  if (tupleSpace.find(tupleShortcut) != tupleSpace.end()) return true;
  return false;
}