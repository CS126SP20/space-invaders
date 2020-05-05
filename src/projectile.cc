// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/projectile.h"

namespace spaceinvaders {

using cinder::app::getWindowHeight;

Projectile::Projectile(const cinder::vec2 &position, Type type,
                       Direction direction)
    : position_(position),
      Collidable(position.x - (kWidth / 2.0f), position.y - (kHeight / 2.0f),
                 position.x + (kWidth / 2.0f), position.y + (kHeight / 2.0f)),
      type_(type),
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

bool Projectile::IsActive() const { return is_active_; }

Projectile::Direction Projectile::GetDirection() const { return direction_; }

int Projectile::GetID() const { return id_; }
}  // namespace spaceinvaders