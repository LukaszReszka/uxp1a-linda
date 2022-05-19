#pragma once
#include <string>
#include <variant>
#include <vector>


using SingleTupleValue = std::variant<std::string, u_int32_t, float>;
using TupleValues = std::vector<SingleTupleValue>;

namespace uxp {
class Tuple {
 public:
  Tuple(TupleValues values){this->values = values;};
  std::string getPatternShortcut();
  inline const TupleValues& getValues() const { return values; }

 private:
  TupleValues values;
};
}  // namespace uxp