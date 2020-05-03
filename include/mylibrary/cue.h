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
        void SetDirection(vec2 pos);
        vec2 getPos() const;
        double GetWidth() {return texture_->getWidth();}
        double GetHeight() {return texture_->getHeight();}
        void ApplyForce();
        void Recoil();
        bool hit = false;
        void IncreasePower();
        void DecreasePower();
        float GetPower() {return power_;}
    private:
        vec2 direction_;
        float angle_;
        float power_ = 30;
        float CalculateAngle(vec2 pos1, vec2 pos2);
    };
}
#endif //FINALPROJECT_CUE_H
