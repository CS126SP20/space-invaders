//
// Created by Saurav Raghavendra on 4/28/2020.
//

#ifndef FINALPROJECT_COLLIDABLE_H
#define FINALPROJECT_COLLIDABLE_H

#include "cinder/gl/gl.h"

namespace spaceinvaders {

class Collidable {
 public:
  Collidable(float width, float height);

  bool TryCollideWith(Collidable &other);
  cinder::RectT<float> GetBox() const;

  virtual const cinder::vec2 &GetPosition() const = 0;
  virtual void OnCollide(Collidable &other) = 0;

 private:
  cinder::vec2 size_;
};
}

#endif  // FINALPROJECT_COLLIDABLE_H
