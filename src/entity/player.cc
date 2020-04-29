// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/player.h"

namespace spaceinvaders {

namespace {
constexpr float BASE_Y = static_cast<float>(500) - 40.0f;
}

Player::Player()
: Collidable(44, 32){
  sprite_.set()
}

}  // namespace spaceinvaders
