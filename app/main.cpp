#include <iostream>

#include "test.h"
#include "linda.h"

int main() {
  Linda linda = Linda();
  auto test = TestClass();
  std::cout << test.add(1, 2) << std::endl;
  return 0;
}