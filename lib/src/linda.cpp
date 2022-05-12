#include "linda.h"

#include <algorithm>
#include <tuple>

using namespace std;

Linda::Linda() {}

void Linda::output(uxp::Tuple &&tuple) {}

optional<uxp::Tuple> Linda::input(const TupleCondition &, Time) { return nullopt; }
optional<uxp::Tuple> Linda::read(const TupleCondition &, Time) { return nullopt; }

void Linda::createNewTupleTypeControler(const std::string &tuplePattern) {
  mtx.lock();
  tupleSpace[tuplePattern];
  mtx.unlock();
}
bool Linda::checkIfTupleSpaceInMap(const string &tupleShortcut) const {
  if (tupleSpace.find(tupleShortcut) != tupleSpace.end()) return true;
  return false;
}