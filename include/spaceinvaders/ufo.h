// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_UFO_H
#define FINALPROJECT_UFO_H

#include "cinder/Rand.h"
#include "cinder/Timeline.h"
#include "cinder/Utilities.h"
#include "cinder/app/AppBase.h"
#include "poSpritesheet/poSpritesheet.h"
#include "poSpritesheet/poSpritesheetAnimation.h"
#include "spaceinvaders/collidable.h"
#include "choreograph/Choreograph.h"
#include "cinder/Timeline.h"

namespace spaceinvaders {

class UFO : public Collidable {
 public:
  enum class State { Waiting, Flying, Destroyed };

  UFO(cinder::Rand &rand);

  State GetState() const;

  void Update();

  void Draw();

  auto GetPosition() const -> const cinder::vec2 & override;
  void OnCollide(Collidable &other);

 private:
  cinder::Rand &rng_;
  cinder::gl::TextureRef texture_;
  ;
  cinder::Rectf sprite_;
  float vx_;
  State state_;
  po::SpritesheetRef sprite_sheet_;
  po::SpritesheetAnimationRef animation_;
  cinder::JsonTree json_;
  choreograph::Timeline timeline_;
  cinder::Anim<cinder::vec2> start_pos_;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_UFO_H
