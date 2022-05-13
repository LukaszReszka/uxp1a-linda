#include <iostream>
#include "linda.h"
#include "test.h"
#include "tupleConditionParser.h"

int main() {
  auto parser = TupleConditionParser(std::string("string:>=\"atring\", integer:<=125, float:*"));
  auto a = TupleCondition(parser.parseWholeCondition());
  std::vector<std::variant<std::string, u_int32_t, float>> vec = std::vector<std::variant<std::string, u_int32_t, float>>();
  vec.push_back(std::string("dd"));
  vec.push_back((u_int32_t)124);
  vec.push_back((float)1.1);
  vec.push_back((float)1.1);

  
  std::cout << a.checkCondition(uxp::Tuple(vec));
  std::cout << a.getShortcut();
  std::cout << uxp::Tuple(vec).getPatternShortcut();
  return 0;
}