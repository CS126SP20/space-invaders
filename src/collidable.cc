//
// Created by Saurav Raghavendra on 4/28/2020.
//

#include "spaceinvaders/collidable.h"

namespace spaceinvaders {
Collidable::Collidable(float x1, float y1, float x2, float y2)
    : x1_(x1),
      y1_(y1),
      x2_(x2),
      y2_(y2),
      width_(abs(x2 - x1)),
      height_(abs(y2 - y1)) {}

auto Collidable::TryCollideWith(Collidable &other) -> bool {
  if (GetBox().intersects(other.GetBox())) {
    OnCollide(other);
    other.OnCollide(*this);
    return true;
  }
  return false;
}

cinder::Rectf Collidable::GetBox() const {
  return {GetPosition().x - (width_ / 2.0f), GetPosition().y - (height_ / 2.0f),
          GetPosition().x + (width_ / 2.0f),
          GetPosition().y + (height_ / 2.0f)};
}
}  // namespace spaceinvaders