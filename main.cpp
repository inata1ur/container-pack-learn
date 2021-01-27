#include "Truckload.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>

inline unsigned random(size_t count)
{
  return 1 + static_cast<unsigned>(std::rand() / (RAND_MAX / count + 1));
}

inline SharedBox randomBox()
{
  const size_t dimLimit {99};
  return std::make_shared<Box>(random(dimLimit), random(dimLimit), random(dimLimit));
}

int main()
{
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  Truckload load1;

  const size_t boxCount {20};
  for (size_t i {}; i < boxCount; ++i) load1.addBox(randomBox());

  std::cout << "The first list:\n";
  std::cout << load1 << std::endl;

  Truckload copy{load1};
  std::cout << "The copy list:\n";
  std::cout << copy << std::endl;

  auto max = std::max_element(copy.begin(), copy.end());

  std::cout << *(*max).get() << std::endl;
}
