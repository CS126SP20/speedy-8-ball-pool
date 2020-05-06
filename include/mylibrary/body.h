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

using namespace cinder;

namespace myapp {

    class Ball;
    typedef std::shared_ptr<b2Body>	BodyRef;
    /**
     * Parent body class that all other bodies inherit from
     */
    class Body {
    protected:
        BodyRef body_;
        cinder::gl::Texture2dRef texture_;
        vec2 pos_;

    public:
        Body(BodyRef body, gl::Texture2dRef texture, vec2 pos);
        virtual void draw() = 0;
        virtual void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) = 0;
        BodyRef GetBody() {return body_;}
    };
}
#endif //FINALPROJECT_BODY_H
