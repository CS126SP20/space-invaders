// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/ufo.h"

#include <glm/glm.hpp>

namespace spaceinvaders {

using cinder::loadImage;
using cinder::app::getWindowWidth;
using cinder::app::loadAsset;
using cinder::gl::Texture2d;
using State = UFO::State;

namespace {
constexpr float kWidth = 72;
constexpr float kHeight = 36;
constexpr float Y_POS = 45;
}  // namespace

UFO::UFO(cinder::Rand &rand)
    : Collidable(0, 0, 10, 5),
      rng_(rand),
      texture_(Texture2d::create(loadImage(loadAsset("ufo.png")))),
      json_(cinder::JsonTree(loadAsset("ufo.json"))) {
  sprite_sheet_ = po::Spritesheet::create(texture_, json_);
  sprite_ = cinder::Rectf(sprite_sheet_->getFrameBounds());
  animation_ = po::SpritesheetAnimation::create(sprite_sheet_);
  animation_->setIsLoopingEnabled(true);
  animation_->play();
  start_pos_ = cinder::vec2(500, 20);
  cinder::vec2 end_pos = cinder::vec2(0, 20);

  ci::app::timeline().apply(&start_pos_, end_pos, 15.0f).loop();
}

void UFO::Update() {
  animation_->update();
  switch (state_) {
    case State::Destroyed:
      state_ = State::Waiting;
      break;

    case State::Flying:
      sprite_.offset({vx_, 0});
      if (GetPosition().x <= -kWidth ||
          GetPosition().x >= getWindowWidth() + kWidth) {
        state_ = State::Waiting;
      }
      break;

    case State::Waiting:
      if (rng_.nextInt(1, 250) == 100) {
        state_ = State::Flying;
        vx_ = static_cast<float>(rng_.nextInt(-1, 1)) * 200.0f;
        float x_pos;
        if (vx_ >= 0) {
          x_pos = -kWidth;
        } else {
          x_pos = getWindowWidth();
        }
        sprite_.offsetCenterTo({x_pos, Y_POS});
      }
      break;
  }
}

void UFO::Draw() {
  cinder::gl::pushModelView();
  cinder::vec2 val = start_pos_.value();
  cinder::gl::translate(
      val.x - sprite_sheet_->getOriginalBounds().getWidth() / 2,
      val.y - sprite_sheet_->getOriginalBounds().getHeight() / 2);
  animation_->draw();
  cinder::gl::popModelView();
  cinder::gl::draw(texture_, sprite_);
}

auto UFO::GetPosition() const -> const cinder::vec2 &{
  return sprite_.getCenter();
}

void UFO::OnCollide([[maybe_unused]] Collidable &other) {
  state_ = State::Destroyed;
  sprite_.offsetCenterTo({-1000, 0});
}

}  // namespace spaceinvaders