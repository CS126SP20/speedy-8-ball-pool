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
/**
 * Ball class that inherits from Body
 */
    class Ball : public Body {
    public:
        // whether or not it is hit into hole
        bool is_visible = true;
        // the number of the ball
        int id_ = 0;
        void draw() override;
        //void destroy() {body_->SetActive(false);}
        void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
        // pass in file name
        Ball(BodyRef body, cinder::gl::TextureRef texture_, vec2 pos, float radius);
        void SetPosition( const ci::vec2 &pos );
        vec2 getPos() const;
        float getRadius() {return radius_;}
        void setId(int id);

        // for testing purposes
        void SetVisibility(bool visible) {is_visible = visible;}
    private:
        float radius_;
    };
}

#endif //FINALPROJECT_BALL_H
