// Copyright (c) 2020 Saurav Raghavendra. All rights reserved.

#include "spaceinvaders/animationrenderer.h"

namespace spaceinvaders {

AnimationRenderer::AnimationRenderer(float x1, float y1, float x2, float y2,
                                     const std::string &image_path)
    : entity_(x1, y1, x2, y2),
      texture_(cinder::gl::Texture2d::create(
          cinder::loadImage(cinder::app::loadAsset(image_path)))) {}

void AnimationRenderer::NextFrame() { current_frame_++; }

void AnimationRenderer::RenderEntity(const cinder::vec2 &position) {
  cinder::gl::clear();
  entity_.offsetCenterTo(position);
  cinder::gl::draw(texture_, entity_);
}

}  // namespace spaceinvaders