#pragma once
#include <string>
#include <variant>
#include <vector>

using TupleValues = std::vector<std::variant<std::string, u_int32_t, float>>;

namespace uxp {
class Tuple {
 public:
  Tuple();
  std::string getPatternShortcut() const { return "IS"; };
  inline const TupleValues& getValues() const { return values; }

 private:
  TupleValues values;
};
}  // namespace uxp