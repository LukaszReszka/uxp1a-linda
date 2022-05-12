#include "linda.h"

#include <algorithm>
#include <string>
#include <tuple>

using namespace std;

Linda::Linda() {}

void Linda::output(uxp::Tuple&& tuple) {
  string pattern = tuple.getPatternShortcut();
  if (!checkIfTupleSpaceInMap(pattern)) {
    createNewTupleTypeControler(pattern);
  }
  TupleTypeControler& controller = tupleSpace.at(pattern);
  controller.addTuple(tuple);
}

optional<uxp::Tuple> Linda::input(const TupleCondition& tupleCondition,
                                  Time timeout) {
  string pattern = tupleCondition.getShortcut();
  if (!checkIfTupleSpaceInMap(pattern)) {
    createNewTupleTypeControler(pattern);
  }
  TupleTypeControler& controller = tupleSpace.at(pattern);
  return controller.getTuple(tupleCondition, timeout);
}

optional<uxp::Tuple> Linda::read(const TupleCondition& tupleCondition,
                                 Time timeout) {
  string pattern = tupleCondition.getShortcut();
  if (!checkIfTupleSpaceInMap(pattern)) {
    createNewTupleTypeControler(pattern);
  }
  TupleTypeControler& controller = tupleSpace.at(pattern);
  return controller.readTuple(tupleCondition, timeout);
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