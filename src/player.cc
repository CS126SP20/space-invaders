// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/player.h"

namespace spaceinvaders {

using cinder::loadImage;
using cinder::app::getWindowCenter;
using cinder::app::getWindowHeight;
using cinder::app::getWindowWidth;
using cinder::app::loadAsset;
using cinder::gl::Texture2d;

Player::Player()
    : Collidable(44, 32),
      sprite_{getWindowCenter().x - 22.0f, getWindowCenter().y + 210.0f,
              getWindowCenter().x, getWindowCenter().y + 16.0f + 210.0f},
      texture_{Texture2d::create(loadImage(loadAsset("player.png")))} {

}

void Player::Restart() {
  velocity_ *= 0.0f;
  texture_ = Texture2d::create(loadImage(loadAsset("player.png")));
  is_alive_ = true;
  lives_left_--;
  sprite_.offsetCenterTo({getWindowCenter().x, getWindowCenter().y + 200.0f});
}

void Player::Draw() { cinder::gl::draw(texture_, sprite_); }

void Player::MoveLeft() { velocity_.x -= speed; }

void Player::MoveRight() { velocity_.x += speed; }

void Player::Update() {
  if (is_alive_) {
    auto width = sprite_.getWidth();
    sprite_.offset(velocity_);
    velocity_ *= 0.25f;
    if (sprite_.getCenter().x <= 0) {
      velocity_.x = 1.0f;
      sprite_.offsetCenterTo(
          {1.0f, static_cast<float>(getWindowHeight() - 40.0f)});
    } else if (sprite_.getCenter().x + width >= getWindowWidth()) {
      velocity_.x = -1.0f;
      sprite_.offsetCenterTo({getWindowWidth() - 1.0f - width,
                              static_cast<float>(getWindowHeight()) - 40.0f});
    }
  }
}

auto Player::GetGunPosition() const -> cinder::vec2 {
  return {sprite_.getCenter().x + sprite_.getWidth() / 2,
          sprite_.getCenter().y};
}

auto Player::GetPosition() const -> const cinder::vec2& { return sprite_.getCenter(); }

void Player::OnCollide([[maybe_unused]] Collidable& other) {
  is_alive_ = true;
  death_timer_.start();
}

auto Player::GetLives() const -> int {
  return lives_left_; }

auto Player::IsAlive() -> bool { return is_alive_; }

void Player::TryRevive() {
  if (death_timer_.getSeconds() >= 1.5f) {
    Restart();
  }
}

// namespace spaceinvaders
}  // namespace spaceinvaders
