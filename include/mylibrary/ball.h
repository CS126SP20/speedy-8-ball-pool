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
#include "body.h"


using namespace cinder;
namespace myapp {

    class Ball : public Body {
    public:
        // not movable if it is opposite type of current player
        bool is_movable = true;
        // whether or not it is hit into hole
        bool is_visible = true;
        // the number of the ball
        int id_ = 0;

        Ball();
        void draw() override;
        void destroy() {body_->SetActive(false);}
        void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
        // pass in file name
        Ball(BodyRef body, cinder::gl::TextureRef texture_, vec2 pos, float radius);
        void SetPosition( const ci::vec2 &pos );
        vec2 getPos() const;
        float getRadius() {return radius_;}
        void setId(int id);
        void setVel(double x_vel, double y_vel);

        bool is_moving();

        static bool is_solid(int num) {return num > 0 && num < 8;}
        static bool is_stripes(int num) {return num > 8 && num < 16;}
    private:
        float radius_;
    };
}

#endif //FINALPROJECT_BALL_H
