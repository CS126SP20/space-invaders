//
// Created by Saurav Raghavendra on 4/28/2020.
//

#include "spaceinvaders/collidable.h"

namespace spaceinvaders {
Collidable::Collidable(float x1, float y1, float x2, float y2)
    : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

bool Collidable::TryCollideWith(Collidable &other) {
  if (GetBox().intersects(other.GetBox())) {
    OnCollide(other);
    other.OnCollide(*this);
    return true;
  }
  return false;
}

cinder::Rectf Collidable::GetBox() const {
  return {x1_, y1_, x2_, y2_};
}
}  // namespace spaceinvaders