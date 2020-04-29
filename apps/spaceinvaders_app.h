// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <vector>

#include "Box2D/Box2D.h"
#include "choreograph/Choreograph.h"
#include "cinder/app/App.h"
#include "cinder/app/KeyEvent.h"
#include "cinder/gl/gl.h"
#include "spaceinvaders/collidable.h"
#include "spaceinvaders/player.h"

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
};

}  // namespace spaceinvadersapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
