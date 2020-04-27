// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/engine.h"

namespace spaceinvaders {

Engine::Engine(const Player& player) {
  player_ = player;
}

void Engine::HandleBulletCollision(const b2BodyDef& bullet, const b2BodyDef& other) {
  if (reinterpret_cast<int>(other.userData) == kInvaderType) {
    explode_bodies_.push_back(other);
    player_.AddToScore(100);
  } else if (reinterpret_cast<int>(other.userData) == kShrapnelType) {
    garbage_bodies_.push_back(other);
    player_.AddToScore(5);
  }
  garbage_bodies_.push_back(bullet);
}

void Engine::HandlePlayerCollision(const b2BodyDef& player, const b2BodyDef& other) {
  if (reinterpret_cast<int>(player.userData) == kInvaderType) {
    explode_bodies_.push_back(other);
    player_.SubtractFromScore(100);
    player_.RemoveLife();
    explode_bodies_.push_back(player);
  }
}

void Engine::HandleBombCollision(b2BodyDef& bomb,
                                 const b2BodyDef& other) {
  if (!reinterpret_cast<bool>(bomb.userData)) {
    if (reinterpret_cast<int>(other.userData) != kInvaderType) {
      explode_bodies_.push_back(bomb);
      if (reinterpret_cast<int>(other.userData) == kPlayerType) {
        player_.RemoveLife();
        explode_bodies_.push_back(other);
      }
      bomb.userData = reinterpret_cast<void*>(static_cast<int>(true));
    }
  }

}
}