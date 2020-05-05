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

  /**
   * Checks whether the current Collidable collided with the other Collidable.
   *
   * @param other the other Collidable.
   * @return whether the 2 objects collided with each other.
   */
  bool TryCollideWith(Collidable &other);

  /**
   * Gets the rectangular region of the collidable.
   *
   * @return the rectangular region of the collidable as a Rectf.
   */
  cinder::Rectf GetBox() const;

  /**
   * Gets the current position of the Collidable.
   *
   * @return the current position of the Collidable.
   */
  virtual const cinder::vec2 &GetPosition() const = 0;

  /**
   * Contains the behavior when the Collidable collides with another
   * Collidable.
   *
   * @param other the other collidable.
   */
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
