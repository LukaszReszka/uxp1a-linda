#include <iostream>
#include "linda.h"
#include "tupleConditionParser.h"
#include "tupleValuesParser.h"

int main() {
  auto condParser = TupleConditionParser(std::string("string:\"dd\", integer:*, float:*"));
  auto valParser = TupleValuesParser(std::string("string = \"dd\", integer  = 123, float =1.1 , float =1.1"));
  auto tupleCondition = TupleCondition(condParser.parseWholeCondition());
  auto tuple = uxp::Tuple(valParser.parseAllValues());


  
  std::cout << tupleCondition.checkCondition(tuple) << std::endl;
  std::cout << tupleCondition.getShortcut() << std::endl;
  std::cout << tuple.getPatternShortcut() << std::endl;
  return 0;
}