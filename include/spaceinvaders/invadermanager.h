// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_INVADERMANAGER_H
#define FINALPROJECT_INVADERMANAGER_H

#include <cstdlib>
#include <utility>
#include <vector>

#include "animationrenderer.h"
#include "cinder/Rand.h"
#include "cinder/gl/draw.h"
#include "spaceinvaders/invader.h"
#include "spaceinvaders/projectile.h"
#include "cinder/app/AppBase.h"

namespace spaceinvaders {
class World;
using CollisionResult = std::pair<int, std::vector<cinder::vec2>>;

class InvaderManager {
 public:
  InvaderManager();

  void TryStepInvaders();

  void DrawInvaders();

  auto TryCollideWithProjectiles(std::vector<Projectile> &projectiles) -> CollisionResult;

  auto GetRandomLowestInvaderPoint(cinder::Rand &random) -> cinder::vec2;

  auto GetAliveInvadersCount() const -> int;

  void InitAddInvader();
  auto AreInvadersAlive() const -> bool;

  auto GetGameOver() -> bool { return is_game_over_;}

 private:
  void UpdateStepDelay();

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
  cinder::gl::Texture2dRef texture_;

  int init_x_ = 0;
  int init_y_ = 4;
  int ticks_ = 0;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_INVADERMANAGER_H
