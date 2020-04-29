// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"

namespace spaceinvadersapp {

using cinder::vec3;
using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {

}

void MyApp::update() {
  player.Update();
}

void MyApp::draw() {
  cinder::gl::clear();
  player.Draw();
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT :
      player.MoveLeft();
      break;
    case KeyEvent::KEY_RIGHT :
      player.MoveRight();
      break;
  }
}

}  // namespace spaceinvadersapp
