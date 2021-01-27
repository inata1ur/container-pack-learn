#include "Truckload.h"

Truckload::Truckload(const Truckload& src)
{
  for (auto &box : src) { addBox(box); }
}

std::ostream& operator<<(std::ostream& os, const Truckload& tr)
{
  const size_t boxesPerLine {5};
  size_t       count {};

  for (auto &box : tr) {
    os << *box.get();
    if (!(++count % boxesPerLine)) os << '\n';
  }

  if (count % boxesPerLine) os << '\n';

  return os;
}

void Truckload::addBox(SharedBox pBox)
{
  auto pPackage = new Package {pBox};

  if (pTail)
    pTail->pNext = pPackage;
  else
    pHead = pPackage;

  pTail = pPackage;
}
