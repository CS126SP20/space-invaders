// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders_app.h"

#include "cinder/Timeline.h"

using namespace ci;

namespace spaceinvaders {

using cinder::vec3;
using cinder::app::KeyEvent;
using spaceinvaders::Projectile;
using namespace po::scene;

MyApp::MyApp()
    : ufo_(rand),
      invaders_(),
      invader_vector_(invaders_.GetInvaders()),
      player_shot_clock_(true),
      anim_timer_(true),
      invader_shot_clock_(true),
      score_(0),
      invader_guy_(0, 0, 20, 10),
      single_projectile_(0, 400, 20, 425),
      projectile_renderer_{
          player_.GetPosition().x - (Projectile::kWidth / 2.0f),
          player_.GetPosition().y - (Projectile::kHeight / 2.0f),
          player_.GetPosition().x + (Projectile::kWidth / 2.0f),
          player_.GetPosition().y + (Projectile::kHeight / 2.0f),
          "projectile1.png"} {}

void MyApp::setup() {
  cinder::gl::enableAlphaBlending();
  texture_ = cinder::gl::Texture2d::create(
      cinder::loadImage(cinder::app::loadAsset("invader1.png")));
  projectile_texture_ = cinder::gl::Texture2d::create(
      cinder::loadImage(cinder::app::loadAsset("projectile1.png")));
  choreograph::Output<cinder::Rectf> target(single_projectile_);
  choreograph::Timeline timeline;
  cinder::TimelineRef timeline1 = Timeline::create();
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
  ci::app::timeline().apply(&view->getPositionAnim(), ci::vec2(50.0f, 50.0f),
                            1.0f);

  if (invaders_.AreInvadersAlive()) {
    player_.Update();

    if (player_.IsAlive()) {
      invaders_.TryStepInvaders();
      EnemyProjectileFire();

      auto collision_result = GetCollisionResult();
      if (collision_result.second.size() > 0) {
        score_ += 10;
      }
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
  cinder::gl::draw(texture_, invader_guy_);
  cinder::gl::draw(projectile_texture_, single_projectile_);

  if (!invaders_.GetGameOver()) {
    cinder::gl::clear();
    if (anim_timer_.getSeconds() > 0.2) {
      projectile_renderer_.NextFrame();
      anim_timer_.start();
    }

    for (auto &proj : projectiles_) {
      projectile_renderer_.RenderEntity(proj.GetPosition());
    }

    PrintText(std::to_string(score_), cinder::Color::white(), {500, 50},
              {getWindowCenter().x, getWindowCenter().y - 200});

    PrintText("Lives: ", cinder::Color::white(), {500, 50},
              {getWindowCenter().x + 50, getWindowCenter().y - 200});

    PrintText(std::to_string(player_.GetLives()), cinder::Color::white(),
              {500, 50}, {getWindowCenter().x + 75, getWindowCenter().y - 200});

    invaders_.DrawInvaders();
    player_.Draw();
    ufo_.Draw();
  }
  if (invaders_.GetGameOver()) {
    cinder::gl::clear(cinder::Color(1, 0, 0));
    PrintText("GAME OVER", cinder::Color::black(), {500, 50},
              getWindowCenter());
  }
}

void MyApp::PlayerInput() {
  if (player_shot_clock_.getSeconds() > 0.5) {
    auto point = player_.GetGunPosition();
    point.y -= Projectile::kHeight;
    point.x -= Projectile::kWidth / 2.0f;
    projectiles_.emplace_back(point, Projectile::Type::Rectangle,
                              Projectile::Direction::Up);
    player_shot_clock_.start();
  }
}

void MyApp::keyDown(KeyEvent event) {
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
        point.y -= Projectile::kHeight;
        point.x -= Projectile::kWidth / 2.0f;
        projectiles_.emplace_back(point, Projectile::Type::Rectangle,
                                  Projectile::Direction::Up);
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
    auto type = static_cast<Projectile::Type>(rand.nextInt(1, 2));
    projectiles_.emplace_back(point, type, Projectile::Direction::Down);
    invader_shot_clock_.start();
  }
}

}  // namespace spaceinvaders
