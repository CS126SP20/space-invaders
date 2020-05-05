// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_INVADER_H
#define FINALPROJECT_INVADER_H

#include <spaceinvaders/collidable.h>
#include "spaceinvaders/player.h"

namespace spaceinvaders {


class Invader : public Collidable {
 public:
  Invader(const cinder::vec2 &initial_location);

  /**
   * Moves the invader by a specified x and y position.
   *
   * @param x the number of pixels to move in the x direction.
   * @param y the number of pixels to move in the y direction.
   */
  void Move(float x, float y);

  auto GetPosition() const -> const cinder::vec2 & override;

  /**
   * Checks whether the invader is alive.
   *
   * @return whether the invader is alive.
   */
  auto IsAlive() const -> bool;

  void OnCollide(Collidable &other) override;

  /**
   * Makes the invader alive and sets its location.
   */
  void MakeAlive() {
    is_alive_ = true;
    location_ = initial_position_;
  };

 private:
  const cinder::vec2 initial_position_;
  cinder::vec2 location_;
  bool is_alive_ = false;

 public:
  constexpr static float kWidth = 10;
  constexpr static float kHeight = 16;
};
}

#endif  // FINALPROJECT_INVADER_H
