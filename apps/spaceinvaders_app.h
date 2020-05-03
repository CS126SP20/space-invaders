// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <spaceinvaders/ufo.h>

#include <vector>

#include "Box2D/Box2D.h"
#include "choreograph/Choreograph.h"
#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/gl/gl.h"
#include "spaceinvaders/collidable.h"
#include "spaceinvaders/invadermanager.h"
#include "spaceinvaders/player.h"
#include "spaceinvaders/projectile.h"
#include "spaceinvaders/ufo.h"

namespace spaceinvadersapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  spaceinvaders::Player player;
  spaceinvaders::UFO ufo;
  cinder::Rand rand;
  spaceinvaders::InvaderManager invaders_;
  std::vector<spaceinvaders::Projectile> projectiles_;
  spaceinvaders::AnimationRenderer projectile_renderer_;
  cinder::gl::Texture2dRef texture_;
  cinder::Timer player_shot_clock_;
  cinder::Timer anim_timer_;
};

}  // namespace spaceinvadersapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
