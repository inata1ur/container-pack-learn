// Box.h
// Defines Box class
#ifndef BOX_H
#define BOX_H
#include <iomanip>
#include <ostream>

class Box
{
private:
  double length {1.0};
  double width {1.0};
  double height {1.0};

public:
  Box(double lv, double wv, double hv) : length {lv}, width {wv}, height {hv} {}
  Box() = default;
  Box(const Box& box) : length {box.length}, width {box.width}, height {box.height} {}

  double volume() const { return length * width * height; }

  // auto operator<=>(const Box& box) const { return this->volume() < box.volume(); }
  bool operator<(const Box& box) { return this->volume() < box.volume(); }

  friend std::ostream& operator<<(std::ostream& os, const Box& box)
  {
    os << " Box(" << std::setw(2) << box.length << ',' << std::setw(2) << box.width << ','
       << std::setw(2) << box.height << ')';
    return os;
  }
};

#endif /* BOX_H */
