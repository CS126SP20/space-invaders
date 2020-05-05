// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/projectile.h"

namespace spaceinvaders {

using cinder::app::getWindowHeight;

Projectile::Projectile(const cinder::vec2 &position,
                       Direction direction)
    : position_(position),
      Collidable(position.x - (kWidth / 2.0f), position.y - (kHeight / 2.0f),
                 position.x + (kWidth / 2.0f), position.y + (kHeight / 2.0f)),
      direction_(direction) {
  static int ID = 0;
  id_ = ID++;
}

void Projectile::Update() {
  float speed = 5 * static_cast<float>(direction_);
  position_.y += speed;
  if (position_.y <= 0 ||
      position_.y >= static_cast<float>(getWindowHeight())) {
    Destroy();
  }
}

void Projectile::OnCollide([[maybe_unused]] Collidable &other) { Destroy(); }

void Projectile::Destroy() { is_active_ = false; }

const cinder::vec2 &Projectile::GetPosition() const { return position_; }

auto Projectile::IsActive() const -> bool { return is_active_; }

auto Projectile::GetID() const -> int { return id_; }
}  // namespace spaceinvaders