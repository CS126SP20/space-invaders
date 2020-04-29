//
// Created by Saurav Raghavendra on 4/28/2020.
//

#include "spaceinvaders/collidable.h"

namespace spaceinvaders {
Collidable::Collidable(float width, float height) : size_(width, height) {}

bool Collidable::TryCollideWith(Collidable &other) {
  if (GetBox().intersects(other.GetBox())) {
    OnCollide(other);
    other.OnCollide(*this);
    return true;
  }
  return false;
}

cinder::RectT<float> Collidable::GetBox() const {
  return {GetPosition().x, GetPosition().y, size_.x, size_.y};
}
}  // namespace spaceinvaders