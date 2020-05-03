// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"

namespace spaceinvadersapp {

using cinder::vec3;
using cinder::app::KeyEvent;
using spaceinvaders::Projectile;

MyApp::MyApp()
    : ufo(rand),
      invaders_(),
      player_shot_clock_(true),
      anim_timer_(true),
      projectile_renderer_{spaceinvaders::AnimationRenderer(
          player.GetGunPosition().x, player.GetGunPosition().y,
          player.GetGunPosition().x + Projectile::WIDTH +
              player.GetGunPosition().x,
          player.GetGunPosition().y + Projectile::HEIGHT +
              player.GetGunPosition().y,
          "projectile.png")} {}

void MyApp::setup() { cinder::gl::enableAlphaBlending(); }

void MyApp::update() {
  ufo.Update();
  player.Update();
  if (invaders_.AreInvadersAlive()) {
    player.Update();
    if (player.IsAlive()) {
      invaders_.TryStepInvaders();
    } else {
      invaders_.InitAddInvader();
      projectiles_.clear();
    }
  }
}

void MyApp::draw() {
  if (anim_timer_.getSeconds() > 0.2){
    projectile_renderer_.NextFrame();
    anim_timer_.start();
  }


  cinder::gl::clear();
  player.Draw();
  ufo.Draw();
  invaders_.DrawInvaders();

  for (auto &proj : projectiles_) {
    projectile_renderer_.RenderEntity(proj.GetPosition());
  }
}

void MyApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT:
      player.MoveLeft();
      break;
    case KeyEvent::KEY_RIGHT:
      player.MoveRight();
      break;
    case KeyEvent::KEY_SPACE:
      if (player_shot_clock_.getSeconds() > 0.5f) {
        auto point = player.GetGunPosition();
        point.y -= Projectile::HEIGHT;
        point.x -= Projectile::WIDTH / 2.0f;
        projectiles_.emplace_back(point, Projectile::Type::Rectangle,
                                  Projectile::Direction::Up);
        player_shot_clock_.start();
      }
  }
}

}  // namespace spaceinvadersapp
