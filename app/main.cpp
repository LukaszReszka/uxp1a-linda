#include <iostream>

#include "test.h"

int main() {
  auto test = TestClass();
  std::cout << test.add(1, 2) << std::endl;
  return 0;
}