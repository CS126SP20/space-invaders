//
// Created by Saurav Raghavendra on 4/28/2020.
//

#ifndef FINALPROJECT_COLLIDABLE_H
#define FINALPROJECT_COLLIDABLE_H

#include "cinder/gl/gl.h"

namespace spaceinvaders {

class Collidable {
 public:
  Collidable(float x1, float y1, float x2, float y2);

  bool TryCollideWith(Collidable &other);
  cinder::Rectf GetBox() const;

  virtual const cinder::vec2 &GetPosition() const = 0;
  virtual void OnCollide(Collidable &other) = 0;

 private:
  cinder::vec2 size_;
  float x1_;
  float y1_;
  float x2_;
  float y2_;
  float width_;
  float height_;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_COLLIDABLE_H
