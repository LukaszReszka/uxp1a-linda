#pragma once
#include <string>
#include <variant>
#include <vector>


using SingleTupleValue = std::variant<std::string, u_int32_t, float>;
using TupleValues = std::vector<SingleTupleValue>;

namespace uxp {
class Tuple {
 public:
  explicit Tuple(TupleValues &vals){
    values = std::move(vals);
  };
  std::string getPatternShortcut();
  inline const TupleValues& getValues() const { return values; }

 private:
  TupleValues values;
};
}  // namespace uxp