// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#ifndef FINALPROJECT_ANIMATIONRENDERER_H
#define FINALPROJECT_ANIMATIONRENDERER_H

#include "cinder/gl/Texture.h"
#include "cinder/gl/draw.h"
#include "cinder/app/AppBase.h"
#include "cinder/gl/gl.h"

namespace spaceinvaders {

class AnimationRenderer {
 public:
  AnimationRenderer(float x1, float y1,
                    float x2, float y2, const std::string &image_path);

  /**
   * Moves the animation to the next frame.
   */
  void NextFrame();

  /**
   * Draws the entity to the screen at a given position.
   */
  void RenderEntity(const cinder::vec2 &position);

 private:
  cinder::Rectf entity_;
  int current_frame_;
  cinder::gl::Texture2dRef texture_;
};
}  // namespace spaceinvaders

#endif  // FINALPROJECT_ANIMATIONRENDERER_H
