// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"


namespace spaceinvaders {

using cinder::vec3;
using cinder::app::KeyEvent;
using spaceinvaders::Projectile;
using po::scene::ShapeView;
using po::scene::Alignment;

MyApp::MyApp()
    : ufo_(rand),
      invaders_(),
      player_shot_clock_(true),
      anim_timer_(true),
      invader_shot_clock_(true),
      score_(0),
      projectile_renderer_{
          player_.GetGunPosition().x - (Projectile::kWidth / 2.0f),
          player_.GetGunPosition().y - (Projectile::kHeight / 2.0f),
          player_.GetGunPosition().x + (Projectile::kWidth / 2.0f),
          player_.GetGunPosition().y + (Projectile::kHeight / 2.0f),
          "projectile.png"} {}

void MyApp::setup() {
  cinder::gl::enableAlphaBlending();
  view = ShapeView::createRect(50.0f, 50.0f);
  view->setPosition(ci::vec2(250.0f, 250.0f))
      .setFillColor(cinder::Color(1.0f, 0.0f, 0.0f))
      .setAlpha(0.5f)
      .setRotation(45.0f)
      .setAlignment(Alignment::CENTER_CENTER);
  ci::app::timeline().apply(&view->getPositionAnim(), ci::vec2(50.0f, 50.0f),
                            1.0f);
}

void MyApp::update() {
  if (invaders_.AreInvadersAlive()) {
    player_.Update();

    if (player_.IsAlive()) {
      invaders_.TryStepInvaders();
      EnemyProjectileFire();

      auto collision_result = GetCollisionResult();
      if (collision_result.second.size() > 0) {
        score_ += collision_result.first;
      }
      ufo_.Update();
    }
  } else {
    invaders_.InitAddInvader();
    projectiles_.clear();
  }
}

void PrintText(const std::string &text, const cinder::Color &color,
               const cinder::ivec2 &size, const cinder::vec2 &loc) {
  cinder::gl::color(color);

  auto box = cinder::TextBox()
                 .alignment(cinder::TextBox::CENTER)
                 .font(cinder::Font("Arial", 30))
                 .size(size)
                 .color(color)
                 .backgroundColor(cinder::ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

void MyApp::draw() {
  cinder::gl::clear();

  if (!invaders_.GetGameOver()) {
    if (anim_timer_.getSeconds() > 0.2) {
      projectile_renderer_.NextFrame();
      anim_timer_.start();
    }

    for (auto &proj : projectiles_) {
      projectile_renderer_.RenderEntity(proj.GetPosition());
    }

    PrintText("Score: ", cinder::Color::white(), {500, 50},
              {getWindowCenter().x - 100, getWindowCenter().y - 200});

    PrintText(std::to_string(score_), cinder::Color::white(), {500, 50},
              {getWindowCenter().x - 40, getWindowCenter().y - 200});

    PrintText("Lives: ", cinder::Color::white(), {500, 50},
              {getWindowCenter().x + 50, getWindowCenter().y - 200});

    PrintText(std::to_string(player_.GetLives()), cinder::Color::white(),
              {500, 50}, {getWindowCenter().x + 100, getWindowCenter().y - 200});

    invaders_.DrawInvaders();
    player_.Draw();
    ufo_.Draw();
  }
  if (invaders_.GetGameOver() || player_.GetLives() == -1) {
    cinder::gl::clear(cinder::Color(1, 0, 0));
    PrintText("GAME OVER", cinder::Color::black(), {500, 50},
              getWindowCenter());
    PrintText("Your Score: ", cinder::Color::black(), {500, 50},
              {getWindowCenter().x, getWindowCenter().y + 20});
    PrintText(std::to_string(score_), cinder::Color::black(), {500, 50},
              {getWindowCenter().x + 100, getWindowCenter().y + 20});
  }
}

void MyApp::keyDown(KeyEvent event) {
  if (!player_.IsAlive() && player_.GetLives() >= 0) {
    player_.TryRevive();
  }
  switch (event.getCode()) {
    case KeyEvent::KEY_LEFT:
      player_.MoveLeft();
      break;
    case KeyEvent::KEY_RIGHT:
      player_.MoveRight();
      break;
    case KeyEvent::KEY_SPACE:
      if (player_shot_clock_.getSeconds() > 0.5) {
        auto point = player_.GetGunPosition();
        point.y -= 2.0f * Projectile::kHeight;
        point.x -= Projectile::kWidth / 2.0f;
        projectiles_.emplace_back(point,Projectile::Direction::Up);
        player_shot_clock_.start();
      }
      break;
  }
}

void MyApp::UpdateProjectiles(std::vector<cinder::vec2> &collision_points) {
  for (auto itr = projectiles_.begin(); itr != projectiles_.end();) {
    auto &projectile = *itr;
    if (!projectile.IsActive()) {
      itr = projectiles_.erase(itr);
    } else {
      if (projectile.TryCollideWith(player_)) {
        collision_points.emplace_back(player_.GetPosition());
        projectiles_.clear();
        return;
      }
      projectile.Update();
      itr++;
    }
  }
}

auto MyApp::GetCollisionResult() -> spaceinvaders::CollisionResult {
  auto result = invaders_.TryCollideWithProjectiles(projectiles_);
  UpdateProjectiles(result.second);

  for (auto &projectile : projectiles_) {
    if (ufo_.TryCollideWith(projectile)) {
      result.second.emplace_back(projectile.GetPosition());
    }

    for (auto &other_projectile : projectiles_) {
      if (other_projectile.GetID() != projectile.GetID()) {
        if (other_projectile.TryCollideWith(projectile)) {
          result.second.emplace_back(projectile.GetPosition());
        }
      }
    }
  }

  return result;
}

void MyApp::EnemyProjectileFire() {
  if (invader_shot_clock_.getSeconds() >= 0.1 && rand.nextInt(0, 30) == 2) {
    auto point = invaders_.GetRandomLowestInvaderPoint(rand);
    if (static_cast<int>(point.x) == -1) {
      return;
    }
    projectiles_.emplace_back(point, Projectile::Direction::Down);
    invader_shot_clock_.start();
  }
}

}  // namespace spaceinvaders
