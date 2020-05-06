// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "mylibrary/table.h"
#include "mylibrary/game.h"
#include "mylibrary/scoreboard.h"
#include <cinder/params/Params.h>

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
  // gets the ending time score
  size_t GetScore();
  // converts milliseconds to string that displays time in standard format
  std::string ConvertTime(size_t ms);
  void button();
  void DrawGameOver();

private:
    myapp::Game game_;
    bool tracking_mode;
    ScoreBoard scoreboard_;
    std::vector<Player> top_players_;
    std::vector<Player> top_scores_;
    const size_t kLimit = 3;
    std::chrono::time_point<std::chrono::system_clock> start_time_;
    params::InterfaceGlRef	mParams;
    std::string player_name_;
    bool mPrintFps;
    bool printed_game_over_;

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
