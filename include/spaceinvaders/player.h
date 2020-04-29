// Copyright (c) 2020 Saurav Rgahavendra. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include "cinder/app/AppBase.h"
#include "collidable.h"
#include "Box2D/Box2D.h"

namespace spaceinvaders {

class Player : public Collidable {
 public:
  constexpr static int kWidth = 44;
  constexpr static int kHeight = 32;

  Player();

  void MoveLeft();
  void MoveRight();

  void Update();
  void Draw();

  cinder::vec2 GetGunPosition() const;

  const cinder::vec2 &GetPosition() const;
  void OnCollide(Collidable &other) override;

  int GetLives() const;
  bool IsAlive();

  void TryRevive();

 private:
  void Restart();
  cinder::Rectf sprite_;
  cinder::vec2 velocity_;
  cinder::Timer death_timer_;

  constexpr static int kWindowHeight = 500;
  bool is_alive_ = true;
  int lives_left_ = 3;
};

}  // namespace spaceinvaders

#endif  // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
