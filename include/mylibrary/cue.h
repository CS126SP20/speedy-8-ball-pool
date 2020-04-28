//
// Created by lilyl on 4/18/2020.
//

#ifndef FINALPROJECT_CUE_H
#define FINALPROJECT_CUE_H

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "body.h"

using namespace cinder;

namespace myapp {

    class Cue : public Body {
    public:
        Cue(BodyRef body, cinder::gl::TextureRef texture_, vec2 pos);
        void render();
        void draw();
        void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
        void setPosition( const ci::vec2 &pos );
        vec2 getPos() const;
        double GetWidth() {return texture_->getWidth();}
        double GetHeight() {return texture_->getHeight();}
        void ApplyForce();
        void Recoil();
    private:

    };
}
#endif //FINALPROJECT_CUE_H
