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

  const cinder::vec2 &GetPosition() const;
  bool IsAlive() const;
  Type GetType() const;

  void OnCollide(Collidable &other) override;

  void MakeAlive() {

  }

 private:
  const cinder::vec2 initial_position_;
  cinder::vec2 location_;
  bool is_alive_ = false;
  Type type_;

 public:
  constexpr static float kWidth = 48;
  constexpr static float kHeight = 32;
};
}

#endif  // FINALPROJECT_INVADER_H
