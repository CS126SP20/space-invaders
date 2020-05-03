// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/invadermanager.h"

namespace spaceinvaders {

using cinder::app::getWindowHeight;
using cinder::app::getWindowWidth;

namespace {
const int kMaxInvaders = 55;
}

InvaderManager::InvaderManager()
    : step_gap_(std::chrono::seconds(static_cast<long>(0.5f))),
      invader_renderer_(0, 50, Invader::kWidth, 50 + Invader::kHeight,
                       "invader1.png"),
      step_timer_(true) {
  const int gap = 10;

  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 11; x++) {
      float invader_x = x * Invader::kWidth + (gap * x * 3) + Invader::kWidth;
      float invader_y = y * Invader::kHeight + (gap * y) + Invader::kHeight * 4;
      invaders_.emplace_back(cinder::vec2{invader_x, invader_y},
                             Invader::Type::Crab);
    }
  }
}

void InvaderManager::TryStepInvaders() {
  if (step_timer_.getSeconds() > step_gap_.count()) {
    invader_renderer_.NextFrame();

    bool MoveDown = false;
    float step = is_moving_left ? -10.0f : 10.0f;
    if (move_down_) {
      step *= -1;
    }

    for (auto &invader : invaders_) {
      if (!invader.IsAlive()) {
        continue;
      }

      invader.Move(step, 0.0f);
      if (move_down_) {
        invader.Move(0, Invader::kHeight / 2.0f);
      } else if (!MoveDown) {
        MoveDown = TestInvaderPosition(invader);
      }

      if (move_down_) {
        is_moving_left = !is_moving_left;
      }
      move_down_ = MoveDown;
      step_timer_.start();
    }
  }
}

void InvaderManager::DrawInvaders() {
  for (auto &invader : invaders_) {
    if (!invader.IsAlive()) {
      continue;
    }
    invader_renderer_.RenderEntity(invader.GetPosition());
  }
}

CollisionResult InvaderManager::TryCollideWithProjectiles(
    std::vector<Projectile> &projectiles) {
  CollisionResult result;
  std::vector<cinder::vec2> collisionPoints;
  for (auto &projectile : projectiles) {
    for (auto &invader : invaders_) {
      if (!invader.IsAlive() || !projectile.IsActive()) continue;
      if (projectile.TryCollideWith(invader)) {
        alive_invaders_--;
        if (alive_invaders_ == 0) {
          has_all_invaders_been_added_ = false;
        }
        result.second.emplace_back(invader.GetPosition());
        result.first += ((int)invader.GetType() + 1) * 100;
        UpdateStepDelay();
      }
    }
  }
  return result;
}

cinder::vec2 InvaderManager::GetRandomLowestInvaderPoint(cinder::Rand &random) {
  if (alive_invaders_ == 0) {
    return {-1, -1};
  }

  while (true) {
    auto invader_column = random.nextInt(0, 10);
    for (int y = 4; y >= 0; y--) {
      int index = y * 11 + invader_column;
      auto &invader = invaders_.at(index);
      if (invader.IsAlive()) {
        return {invader.GetPosition().x + Invader::kWidth / 2,
                invader.GetPosition().y + Invader::kHeight + 5};
      }
    }
  }
}

void InvaderManager::InitAddInvader() {
  cinder::Timer delay(true);
  if (delay.getSeconds() > 0.02) {
    invaders_.at(init_y_ * 11 + init_x_).MakeAlive();
    alive_invaders_++;
    init_x_++;
    if (init_x_ == 11) {
      init_x_ = 0;
      init_y_--;
    }
    delay.start();
  }

  if (alive_invaders_ == kMaxInvaders) {
    has_all_invaders_been_added_ = true;
    init_x_ = 0;
    init_y_ = 4;
    UpdateStepDelay();
  }
}

bool InvaderManager::AreInvadersAlive() const {
  return has_all_invaders_been_added_;
}

void InvaderManager::UpdateStepDelay() {
  step_gap_ =
      std::chrono::seconds(static_cast<long>((float)alive_invaders_ / 90.0f));
}

bool InvaderManager::TestInvaderPosition(const Invader &invader) {
  if (invader.GetPosition().y > getWindowHeight() - 150) {
    is_game_over_ = true;
  }
  return (invader.GetPosition().x < 15 && is_moving_left) ||
         (invader.GetPosition().x + Invader::kWidth > getWindowWidth() - 15 &&
          !is_moving_left);
}

auto InvaderManager::GetAliveInvadersCount() const -> int {
  return alive_invaders_;
}
}  // namespace spaceinvaders
