// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"

using cinder::vec3;
using namespace choreograph;
using cinder::app::KeyEvent;

namespace spaceinvadersapp {

using cinder::app::KeyEvent;

MyApp::MyApp()
    : gravity_{0.0f, -10.0f},
      world_{gravity_},
      player_{spaceinvaders::Player()} {}

void MyApp::setup() {}

void MyApp::update() {}

void MyApp::draw() {
  b2CircleShape circleShape;
  Output<cinder::vec3> target;
  Timeline timeline;

  timeline.apply(&target)
      .then<Hold>(vec3(1.0), 1.0)
      .then<RampTo>(vec3(100), 3.0);
  timeline.step(1.0 / 60.0);
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT:
      break;
    case KeyEvent::KEY_RIGHT:
      break;
  }
}

}  // namespace spaceinvadersapp
