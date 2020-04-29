//
// Created by Saurav Raghavendra on 4/28/2020.
//

#include "spaceinvaders/invader.h"

namespace spaceinvaders {
using cinder::vec2;

Invader::Invader(const cinder::vec2 &initial_location, Type type)
    : Collidable(kWidth, kHeight),
      initial_position_(initial_location),
      location_(initial_location),
      type_(type) {}

void Invader::Move(float x, float y) {
  location_ += vec2{x, y};
}

const vec2 &Invader::GetPosition() const {
  return location_;
}

bool Invader::IsAlive() const {
  return is_alive_;
}

Invader::Type Invader::GetType() const {
  return type_;
}

void Invader::OnCollide([[maybe_unused]] Collidable &other) {
  is_alive_ = false;
}
}  // namespace spaceinvaders