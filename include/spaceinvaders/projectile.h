// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_PROJECTILE_H
#define FINALPROJECT_PROJECTILE_H

#include "spaceinvaders/collidable.h"
#include "cinder/app/AppBase.h"

namespace spaceinvaders {

class Projectile : public Collidable {
 public:
  constexpr static float kHeight = 20;
  constexpr static float kWidth = 6;

  enum class Type { Rectangle, Lightning, Knife };

  enum class Direction { Up = -1, Down = 1 };

  Projectile(const cinder::vec2 &position, Type type, Direction direction);
  void Update();
  void OnCollide(Collidable &other) override;
  void Destroy();

  const cinder::vec2 &GetPosition() const;
  Type GetType() const;
  bool IsActive() const;
  Direction GetDirection() const;

  int GetID() const;

 private:
  cinder::vec2 position_;
  Type type_;
  Direction direction_;
  bool is_active_ = true;
  int id_;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_PROJECTILE_H
