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

  /**
   * The possible directions that a projectile can go.
   */
  enum class Direction { Up = -1, Down = 1 };

  Projectile(const cinder::vec2 &position, Direction direction);

  /**
   * Updates the position of the projectile.
   */
  void Update();

  void OnCollide(Collidable &other) override;

  const cinder::vec2 &GetPosition() const;

  /**
   * Destroys the projectile.
   */
  void Destroy();

  /**
   * Determines whether the projectile has collided with something.
   *
   * @return false if the projectile has collided, true otherwise.
   */
  auto IsActive() const -> bool;

  /**
   * Gets the ID of the projectile.
   *
   * @return the ID of the projectile.
   */
  auto GetID() const -> int;

 private:
  cinder::vec2 position_;
  Direction direction_;
  bool is_active_ = true;
  int id_;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_PROJECTILE_H
