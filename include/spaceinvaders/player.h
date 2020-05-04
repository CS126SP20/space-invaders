// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include "cinder/Utilities.h"
#include "cinder/app/AppBase.h"
#include "spaceinvaders/collidable.h"

namespace spaceinvaders {

class Player : public Collidable{
 public:
  constexpr static int kWidth = 44;
  constexpr static int kHeight = 32;

  Player();

  void MoveLeft();
  void MoveRight();

  void Update();
  void Draw();

  auto GetGunPosition() const -> cinder::vec2;

  const cinder::vec2 &GetPosition() const;
  void OnCollide(Collidable &other) override;

  auto GetLives() const -> int;
  auto IsAlive() -> bool;

  void TryRevive();

 private:
  void Restart();
  cinder::Rectf sprite_;
  cinder::gl::Texture2dRef texture_;
  cinder::vec2 velocity_;
  cinder::Timer death_timer_;

  const float speed = 15;
  bool is_alive_ = true;
  int lives_left_ = 3;
};

}  // namespace spaceinvaders

#endif  // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
