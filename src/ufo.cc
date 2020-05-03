// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/ufo.h"

namespace spaceinvaders {

using cinder::loadImage;
using cinder::app::getWindowWidth;
using cinder::app::loadAsset;
using cinder::gl::Texture2d;
using State = UFO::State;

namespace {
constexpr float WIDTH = 72;
constexpr float HEIGHT = 36;
constexpr float Y_POS = 45;
}  // namespace

UFO::UFO(cinder::Rand &rand)
    : Collidable(WIDTH, HEIGHT),
      rng_(rand),
      texture_(Texture2d::create(loadImage(loadAsset("ufo.png")))),
      json_(cinder::JsonTree(loadAsset("ufo.json")))
{
  sprite_sheet_ = po::Spritesheet::create(texture_, json_);
  sprite_ = cinder::Rectf(sprite_sheet_->getFrameBounds());
  animation_ = po::SpritesheetAnimation::create(sprite_sheet_);
  animation_->setIsLoopingEnabled(true);
  animation_->play();
}

State UFO::GetState() const { return state_; }

void UFO::Update() {
  animation_->update();
  switch (state_) {
    case State::Destroyed:
      state_ = State::Waiting;
      break;

    case State::Flying:
      sprite_.offset({vx_, 0});
      if (GetPosition().x <= -WIDTH ||
          GetPosition().x >= getWindowWidth() + WIDTH) {
        state_ = State::Waiting;
      }
      break;

    case State::Waiting:
      if (rng_.nextInt(1, 250) == 100) {
        state_ = State::Flying;
        vx_ = static_cast<float>(rng_.nextInt(-1, 1)) * 200.0f;
        float x_pos;
        if (vx_ >= 0) {
          x_pos = -WIDTH;
        } else {
          x_pos = getWindowWidth();
        }
        sprite_.offsetCenterTo({x_pos, Y_POS});
      }
      break;
  }
}

void UFO::Draw() {
  animation_->draw();
  if (state_ == State::Flying) {
    cinder::gl::draw(texture_, sprite_);
  }
}

auto UFO::GetPosition() const -> const cinder::vec2 & {
  return sprite_.getCenter();
}

void UFO::OnCollide([[maybe_unused]] Collidable &other) {
  state_ = State::Destroyed;
  sprite_.offsetCenterTo({-1000, 0});
}

}  // namespace spaceinvaders