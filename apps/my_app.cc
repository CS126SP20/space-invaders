// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() : gravity{0.0f, -10.0f}, world{gravity} {}

void MyApp::setup() {}

void MyApp::update() {}

void MyApp::draw() {
  b2CircleShape circle;
  circle.m_p.Set(2.0f, 3.0f);
  circle.m_radius = 0.5f;
}

void MyApp::keyDown(KeyEvent event) {}

}  // namespace myapp
