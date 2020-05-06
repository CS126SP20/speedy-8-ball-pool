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
/**
 * Cue class which inherits from body
 */
    class Cue : public Body {
    public:
        Cue(BodyRef body, cinder::gl::TextureRef texture_, vec2 pos);
        void draw() override;
        // handles collision between cue and ball
        void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
        void setPosition( const ci::vec2 &pos );
        // sets direction based on mouse position
        void SetDirection(vec2 pos);
        // applies force when cue hits ball
        void ApplyForce();
        // checks when cue has hit ball
        bool IsHit() {return hit_;}
        void IncreasePower();
        void DecreasePower();
        float GetPower() {return power_;}
        // calculates the angle based on the mouse position
        float CalculateAngle(vec2 pos1, vec2 pos2);
    private:
        vec2 direction_;
        float angle_;
        float power_ = 30;
        bool hit_ = false;
        float kMaxPower = 50;
        float kMinPower = 10;
        float kPowerIncrement = 5;

    };
}
#endif //FINALPROJECT_CUE_H
