// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "spaceinvaders_app.h"

using cinder::app::App;
using cinder::app::RendererGl;


namespace spaceinvadersapp {

const int kSamples = 8;
const int kWidth = 500;
const int kHeight = 500;

void SetUp(App::Settings* settings) {
  settings->setWindowSize(kWidth, kHeight);
  settings->setTitle("Space Invaders");
}

}  // namespace spaceinvadersapp


// This is a macro that runs the application.
CINDER_APP(spaceinvadersapp::MyApp,
           RendererGl(RendererGl::Options().msaa(spaceinvadersapp::kSamples)),
           spaceinvadersapp::SetUp)
