//
// Created by lilyl on 4/17/2020.
//

#ifndef FINALPROJECT_BALL_H
#define FINALPROJECT_BALL_H

#include <string>
#include <vector>

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

    // the number of the ball
    int id = 0;

    Ball();
    // pass in file name
    Ball(const std::string& path);

    void setTexture(const std::string& path);
    void setPos(double x, double y);
    void setVel(double x_vel, double y_vel);

    bool is_moving();

    static bool is_solid() {return id > 0 && id < 8;}
    static bool is_stripes() {return id > 8 && id < 16;}
};
#endif //FINALPROJECT_BALL_H
