//
// Created by lilyl on 4/19/2020.
//

#ifndef FINALPROJECT_BODY_H
#define FINALPROJECT_BODY_H

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
//#include "ball.h"

using namespace cinder;

namespace myapp {
    typedef std::shared_ptr<b2Body>	BodyRef;
    class Body {
    protected:
        Body(BodyRef body, gl::Texture2dRef texture, vec2 pos);
        virtual void draw() = 0;
        virtual void handleCollision( const BodyRef body, const ci::vec2 &contactPoint ) = 0;
    public:
        BodyRef body_;
        cinder::gl::Texture2dRef texture_;
        vec2 pos_;
    };
}
#endif //FINALPROJECT_BODY_H
