// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/invader.h"

namespace spaceinvaders {
using cinder::vec2;

Invader::Invader(const cinder::vec2 &initial_location)
    : initial_position_(initial_location),
      Collidable(initial_location.x - (kWidth / 2.0f),
                 initial_location.y - (kHeight / 2.0f),
                 initial_location.x + (kWidth / 2.0f),
                 initial_location.y + (kHeight / 2.0f)),
      location_(initial_location)
      {}

void Invader::Move(float x, float y) {
  location_.x += x;
  location_.y += y;
}

const vec2 &Invader::GetPosition() const { return location_; }

bool Invader::IsAlive() const { return is_alive_; }

void Invader::OnCollide([[maybe_unused]] Collidable &other) {
  is_alive_ = false;
}

}  // namespace spaceinvaders