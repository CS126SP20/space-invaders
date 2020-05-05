// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <poScene/Events.h>
#include <poScene/View.h>
#include <spaceinvaders/ufo.h>

#include <vector>

#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/gl/gl.h"
#include "poScene/ShapeView.h"
#include "poScene/View.h"
#include "poScene/ViewController.h"
#include "spaceinvaders/collidable.h"
#include "spaceinvaders/invadermanager.h"
#include "spaceinvaders/player.h"
#include "spaceinvaders/projectile.h"
#include "spaceinvaders/ufo.h"

namespace spaceinvaders {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  void UpdateProjectiles(std::vector<cinder::vec2> &collision_points);
  void EnemyProjectileFire();
  auto GetCollisionResult() -> spaceinvaders::CollisionResult;
  spaceinvaders::Player player_;
  spaceinvaders::UFO ufo_;
  cinder::Rand rand;
  spaceinvaders::InvaderManager invaders_;
  std::vector<spaceinvaders::Projectile> projectiles_;
  spaceinvaders::AnimationRenderer projectile_renderer_;
  cinder::Timer invader_shot_clock_;
  cinder::Timer player_shot_clock_;
  cinder::Timer anim_timer_;
  int score_;
  po::scene::ViewRef view;
};

}  // namespace spaceinvaders

#endif  // FINALPROJECT_APPS_MYAPP_H_
