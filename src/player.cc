// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include <spaceinvaders/player.h>

namespace spaceinvaders {

Player::Player() : lives_{3}, score_{0} {}

void Player::AddToScore(int points) {
  score_ += points;
}

void Player::SubtractFromScore(int points) {
  score_ -= points;
}

void Player::RemoveLife() {
  lives_--;
}

}  // namespace spaceinvaders
