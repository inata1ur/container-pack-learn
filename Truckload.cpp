#include "Truckload.h"

Truckload::Truckload(const Truckload& src)
{
  for (auto& box : src) { addBox(std::make_shared<Box>(box)); }
}

std::ostream& operator<<(std::ostream& os, const Truckload& tr)
{
  const size_t boxesPerLine {5};
  size_t       count {};

  for (auto& box : tr) {
    os << box;
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

Truckload::Iterator& Truckload::Iterator::operator++()
{
  ptr = ptr->pNext;
  return *this;
}

Truckload::Iterator Truckload::Iterator::operator++(int)
{
  auto temp = *this;
  ++(*this);
  return temp;
}

Truckload::Iterator Truckload::Iterator::max_element(Iterator first, Iterator last)
{
  if (first == last) return last;

  auto largest = first;
  for (auto itr = ++first; first != last; ++first)
    if (*largest < *first) largest = first;

  return largest;
}

void Truckload::Iterator::fill(Iterator first, Iterator last, const Value& value)
{
  for (; first != last; ++first) {
    auto package = new Package{std::make_shared<Box>(value)};
    first = Truckload::Iterator(package);
  }
}
