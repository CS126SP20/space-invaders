// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include "cinder/app/App.h"
#include "Box2D/Box2D.h"
#include "cinder/gl/gl.h"
#include "choreograph/Choreograph.h"
#include "spaceinvaders/player.h"
#include "cinder/app/KeyEvent.h"
#include <vector>

namespace spaceinvadersapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  b2Vec2 gravity_;
  b2World world_;
  spaceinvaders::Player player_;
  int formation_delta_ = 0;
  double formation_direction_ = 1.5;
  bool left_down_ = false;
  bool right_down_ = false;
  std::chrono::time_point<std::chrono::system_clock> last_fired_;
  std::chrono::time_point<std::chrono::system_clock> last_bombed_;
  std::vector<b2BodyDef> invaders_;
  std::vector<b2BodyDef> garbage_bodies_;
};

}  // namespace spaceinvadersapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
