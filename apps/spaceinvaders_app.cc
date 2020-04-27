// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"

namespace spaceinvadersapp {

using cinder::vec3;
using cinder::app::KeyEvent;

MyApp::MyApp()
    : gravity_{0.0f, -10.0f},
      world_{gravity_},
      player_{spaceinvaders::Player()} {}

void MyApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
}

void MyApp::update() {}

void MyApp::draw() {
  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);
  b2Body* groundBody = world_.CreateBody(&groundBodyDef);
  cinder::gl::color(cinder::Color::black());
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT:
      left_down_ = true;
      break;
    case KeyEvent::KEY_RIGHT:
      right_down_ = true;
      break;
  }
}

}  // namespace spaceinvadersapp
