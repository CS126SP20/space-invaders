//
// Created by Saurav Raghavendra on 4/28/2020.
//

#ifndef FINALPROJECT_INVADER_H
#define FINALPROJECT_INVADER_H

#include <spaceinvaders/collidable.h>
#include "spaceinvaders/player.h"

namespace spaceinvaders {


class Invader : public Collidable {
 public:
  enum class Type {
    Octopus,
    Crab,
    Squid,
  };

  Invader(const cinder::vec2 &initial_location, Type type);

  void Move(float x, float y);

  void KillInvader() {is_alive_ = false;}

  auto GetPosition() const -> const cinder::vec2 & override;
  auto IsAlive() const -> bool;
  auto GetType() const -> Type;

  void OnCollide(Collidable &other) override;

  void MakeAlive() {
    is_alive_ = true;
    location_ = initial_position_;
  };

 private:
  const cinder::vec2 initial_position_;
  cinder::vec2 location_;
  bool is_alive_ = false;
  Type type_;
  void PrintTextt(const std::string &text, const cinder::Color &color,
                  const cinder::ivec2 &size, const cinder::vec2 &loc);

 public:
  constexpr static float kWidth = 10;
  constexpr static float kHeight = 16;
};
}

#endif  // FINALPROJECT_INVADER_H
