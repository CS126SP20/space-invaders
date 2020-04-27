// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include "Box2D/Dynamics/b2Body.h"
#include "spaceinvaders/player.h"
#include <vector>

namespace spaceinvaders {

class Engine {
 public:
  Engine(const Player& player);
  void HandleBulletCollision(const b2BodyDef& bullet, const b2BodyDef& other);
  void HandlePlayerCollision(const b2BodyDef& player, const b2BodyDef& other);
  void HandleBombCollision(b2BodyDef& bomb, const b2BodyDef& other);

 private:
  const int kInvaderType = 0;
  const int kPlayerType = 1;
  const int kBulletType = 2;
  const int kShrapnelType = 3;
  const int kGroundType = 4;
  const int kStaticType = 5;
  const int kFormationType = 6;
  const int kBombType = 7;
  Player player_;

  std::vector<b2BodyDef> explode_bodies_;
  std::vector<b2BodyDef> garbage_bodies_;
};
}

#endif  // FINALPROJECT_ENGINE_H
