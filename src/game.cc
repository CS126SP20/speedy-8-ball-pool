//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/game.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>

using namespace cinder;

namespace myapp {
    void Game::setup() {
        Ball ball(0);
        balls_.push_back(ball);
    }
    void Game::setTexture() {
        table_.setTexture();
        cue_.setTexture();
        for (Ball& ball : balls_) {
            std::string ball_file = "ball" + std::to_string(ball.id) + ".png";
            ball.setTexture(ball_file);
        }
    }
    void Game::draw() {
        cinder::gl::enableAlphaBlending();
        for (Ball ball : balls_) {
            ball.draw();
        }

        cue_.draw();
        cinder::gl::enableAlphaBlending();
        table_.draw();
        cinder::gl::enableAlphaBlending();
    }
}
