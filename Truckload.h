// Truckload.h
#ifndef TRUCKLOAD_H
#define TRUCKLOAD_H
#include "Box.h"
#include <iterator>
#include <memory>

using SharedBox = std::shared_ptr<Box>;

class Truckload
{
private:
  class Package
  {
  public:
    SharedBox pBox;
    Package*  pNext;

    Package(SharedBox pb) : pBox {pb}, pNext {nullptr} {}
    ~Package() { delete pNext; }
  };

  Package* pHead {};
  Package* pTail {};

public:
  Truckload(const Truckload& src);
  Truckload() = default;
  Truckload(SharedBox pBox) { pHead = pTail = new Package {pBox}; }
  ~Truckload() { delete pHead; }

  Truckload(Truckload&&) = delete;

  Truckload& operator=(const Truckload&) = delete;
  Truckload& operator=(Truckload&&) = delete;

  friend std::ostream& operator<<(std::ostream& os, const Truckload& tr);

  void addBox(SharedBox pBox);
  // bool removeBox(SharedBox boxToRemove);
  // void listBoxes() const;

  class Iterator
  {
  public:
    friend class Truckload;
    using Pointer = Package*;
    using Value   = SharedBox;

  private:
    Pointer ptr;

    Iterator(Pointer ptr) : ptr {ptr} {}

  public:
    Iterator() : ptr {nullptr} {}

    bool   operator==(const Iterator& itr) const { return ptr == itr.ptr; }
    bool   operator!=(const Iterator& itr) const { return ptr != itr.ptr; }
    Value& operator*() const { return ptr->pBox; }

    Iterator& operator++()
    {
      ptr = ptr->pNext;
      return *this;
    }

    Iterator operator++(int)
    {
      auto temp = *this;
      ++(*this);
      return temp;
    }

    Iterator max_element(Iterator first, Iterator last)
    {
      if (first == last) return last;

      auto largest = first;
      for (auto itr = ++first; first != last; ++first)
        if (largest.ptr->pBox < first.ptr->pBox) largest = first;


      return largest;
    }
  };

  Iterator begin() const { return Iterator {pHead}; }
  Iterator end() const { return Iterator {pTail->pNext}; }
};

#endif /* TRUCKLOAD_H */
