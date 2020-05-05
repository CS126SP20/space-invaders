// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/invadermanager.h"

namespace spaceinvaders {

using cinder::app::getWindowHeight;
using cinder::app::getWindowWidth;

using cinder::TextBox;
using cinder::app::getWindowCenter;

namespace {
const int kMaxInvaders = 55;
}

InvaderManager::InvaderManager()
    : step_gap_(std::chrono::seconds(static_cast<long>(0.5f))),
      invader_renderer_(0, 25, Invader::kWidth, 25 + Invader::kHeight,
                        "invader.png"),
      step_timer_(true),
      alive_invaders_(0) {
  const int gap = 10;

  for (int y = 0; y < 5; y++) {
    for (int x = 0; x < 11; x++) {
      float invader_x = x * Invader::kWidth + (gap * x * 3) + Invader::kWidth;
      float invader_y = y * Invader::kHeight + (gap * y) + Invader::kHeight * 4;
      invaders_.emplace_back(cinder::vec2{invader_x, invader_y});
    }
  }
}

void InvaderManager::TryStepInvaders() {
  if (step_timer_.getSeconds() > step_gap_.count()) {
    invader_renderer_.NextFrame();

    bool MoveDown = false;
    float step = is_moving_left ? -0.8f : 0.8f;
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
    }
    if (move_down_) {
      is_moving_left = !is_moving_left;
    }
    move_down_ = MoveDown;
    step_timer_.start();
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

auto InvaderManager::TryCollideWithProjectiles(
    std::vector<Projectile> &projectiles) -> CollisionResult {
  CollisionResult result;
  std::vector<cinder::vec2> collisionPoints;
  for (auto &projectile : projectiles) {
    for (auto &invader : invaders_) {
      if (!invader.IsAlive() || !projectile.IsActive()) {
        continue;
      }
      if (projectile.TryCollideWith(invader)) {
        alive_invaders_--;
        if (alive_invaders_ == 0) {
          has_all_invaders_been_added_ = false;
        }
        result.second.emplace_back(invader.GetPosition());
        result.first += 20;
        UpdateStepDelay();
      }
    }
  }
  return result;
}

auto InvaderManager::GetRandomLowestInvaderPoint(cinder::Rand &random)
    -> cinder::vec2 {
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
  static cinder::Timer delay(true);
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

auto InvaderManager::AreInvadersAlive() const -> bool {
  return has_all_invaders_been_added_;
}

void InvaderManager::UpdateStepDelay() {
  step_gap_ = std::chrono::seconds(
      static_cast<int32_t>(static_cast<float>(alive_invaders_) / 90.0f));
}

auto InvaderManager::TestInvaderPosition(const Invader &invader) -> bool {
  if (invader.GetPosition().y > static_cast<float>(getWindowHeight()) - 75) {
    is_game_over_ = true;
  }
  return (invader.GetPosition().x < 15 && is_moving_left) ||
         (invader.GetPosition().x + Invader::kWidth >
              static_cast<float>(getWindowWidth()) - 15 &&
          !is_moving_left);
}

}  // namespace spaceinvaders
