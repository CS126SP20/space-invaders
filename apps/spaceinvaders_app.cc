// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"
#include "spaceinvaders/Box2dUtils.h"
#include "spaceinvaders/Box2dUtils.cc"

namespace spaceinvadersapp {

using cinder::vec3;
using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
}

void MyApp::update() {}

void MyApp::draw() {
  cinder::Rectf rectf({getWindowWidth() / 2, (float)getWindowHeight() - 40.0f});
  auto img = loadImage(loadAsset("player.png"));
  cinder::gl::Texture2dRef texture2D = cinder::gl::Texture2d::create(img);
  cinder::gl::draw(texture2D, rectf);
}

void MyApp::keyDown(KeyEvent event) {
}

}  // namespace spaceinvadersapp
