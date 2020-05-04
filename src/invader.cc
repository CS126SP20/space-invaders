//
// Created by Saurav Raghavendra on 4/28/2020.
//

#include "spaceinvaders/invader.h"

namespace spaceinvaders {
using cinder::vec2;

Invader::Invader(const cinder::vec2 &initial_location, Type type)
    : initial_position_(initial_location),
      Collidable(initial_location.x - kWidth,
                 initial_location.y - kHeight,
                 initial_location.x + kWidth,
                 initial_location.y + kHeight),
      location_(initial_location),
      type_(type) {}

void Invader::Move(float x, float y) {
  location_.x += x;
  location_.y += y;
}

const vec2 &Invader::GetPosition() const { return location_; }

bool Invader::IsAlive() const { return is_alive_; }

Invader::Type Invader::GetType() const { return type_; }

void Invader::OnCollide([[maybe_unused]] Collidable &other) {
  is_alive_ = false;
}

}  // namespace spaceinvaders