//
// Created by lilyl on 4/17/2020.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <string>
#include <vector>
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
using namespace cinder;
namespace myapp {
    struct Circle {
        double pos_x;
        double pos_y;
        double radius;
    };

    class Ball {
    public:
        // not movable if it is opposite type of current player
        bool is_movable = true;
        // whether or not it is hit into hole
        bool is_visible = true;

        Circle data;
        cinder::gl::TextureRef texture_;

        // the number of the ball
        int id = 0;

        Ball();
        // pass in file name
        Ball(int id);

        void draw();
        void setTexture(const std::string& path);
        void setPos(double x, double y);
        void setVel(double x_vel, double y_vel);

        bool is_moving();

        static bool is_solid(int num) {return num > 0 && num < 8;}
        static bool is_stripes(int num) {return num > 8 && num < 16;}
    };
}

#endif //FINALPROJECT_BALL_H
