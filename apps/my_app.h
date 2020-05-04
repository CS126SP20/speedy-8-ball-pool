// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "mylibrary/table.h"
#include "mylibrary/game.h"

using namespace ci;
using namespace ci::app;

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown( MouseEvent event ) override;
  void mouseDrag( MouseEvent event ) override;
  void mouseUp( MouseEvent event ) override;
  void DrawTime();

private:
    myapp::Game game_;
    cinder::gl::Texture2dRef texture_;
    bool tracking_mode;
    std::chrono::time_point<std::chrono::system_clock> start_time_;
   // float minutes = 0;
   // float seconds = 0;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
