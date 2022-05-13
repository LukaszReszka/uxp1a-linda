#pragma once
#include <string>
#include <variant>
#include <vector>

using TupleValues = std::vector<std::variant<std::string, u_int32_t, float>>;

namespace uxp {
class Tuple {
 public:
  Tuple(std::vector<std::variant<std::string, u_int32_t, float>> values){this->values = values;};
  std::string getPatternShortcut();
  inline const TupleValues& getValues() const { return values; }

 private:
  TupleValues values;
};
}  // namespace uxp