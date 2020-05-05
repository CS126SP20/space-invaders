// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_INVADERMANAGER_H
#define FINALPROJECT_INVADERMANAGER_H

#include <cstdlib>
#include <utility>
#include <vector>

#include "animationrenderer.h"
#include "cinder/Rand.h"
#include "cinder/app/App.h"
#include "cinder/app/AppBase.h"
#include "cinder/gl/draw.h"
#include "spaceinvaders/invader.h"
#include "spaceinvaders/projectile.h"

namespace spaceinvaders {
using CollisionResult = std::pair<int, std::vector<cinder::vec2>>;

class InvaderManager {
 public:
  InvaderManager();

  /**
   * Attempts to move the invaders a single step.
   */
  void TryStepInvaders();

  /**
   * Draws the invaders to the screen
   */
  void DrawInvaders();

  /**
   * Checks for collisions with projectiles and gets the result of each
   * collision.
   *
   * @param projectiles the vector of projectiles to collide with.
   * @return a CollisionResult containing a score and vector of invader
   * positions.
   */
  auto TryCollideWithProjectiles(std::vector<Projectile> &projectiles)
      -> CollisionResult;

  /**
   * Chooses a random invader and gets its lowest point to shoot from.
   *
   * @param random the random object to use.
   * @return the lowest point of a random invader.
   */
  auto GetRandomLowestInvaderPoint(cinder::Rand &random) -> cinder::vec2;

  /**
   * Adds all the invaders to the screen.
   *
   */
  void InitAddInvader();

  /**
   * Checks if all invaders were added.
   *
   * @return whether all the invaders were added.
   */
  auto AreInvadersAlive() const -> bool;

  /**
   * Gets whether the current game is over.
   *
   * @return whether the current game is over.
   */
  auto GetGameOver() -> bool { return is_game_over_; }

 private:
  /**
   * Updates the amount of time in between each step based on number of invaders
   * still alive.
   */
  void UpdateStepDelay();

  /**
   * Checks the position of a specific invader.
   *
   * @param invader the invader to check.
   * @return whether the invader is inside or outside the bounds.
   */
  auto TestInvaderPosition(const Invader &invader) -> bool;

  std::vector<Invader> invaders_;
  cinder::Timer step_timer_;
  std::chrono::seconds step_gap_;
  spaceinvaders::AnimationRenderer invader_renderer_;
  unsigned alive_invaders_;

  bool has_all_invaders_been_added_ = false;

  bool is_moving_left = false;
  bool move_down_ = false;
  bool is_game_over_ = false;

  int init_x_ = 0;
  int init_y_ = 4;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_INVADERMANAGER_H
