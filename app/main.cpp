#include <iostream>
#include "linda.h"
#include "tupleConditionParser.h"
#include "tupleValuesParser.h"

int main() {
  auto condParser = TupleConditionParser(std::string("string:\"dd\", integer:*, float:*"));
  auto valParser = TupleValuesParser(std::string("string = \"dd\", integer  = 123, float =1.1 , float =1.1"));
  auto a = TupleCondition(condParser.parseWholeCondition());
  std::vector<std::variant<std::string, u_int32_t, float>> vec = valParser.parseAllValues();


  
  std::cout << a.checkCondition(uxp::Tuple(vec));
  std::cout << a.getShortcut();
  std::cout << uxp::Tuple(vec).getPatternShortcut();
  return 0;
}