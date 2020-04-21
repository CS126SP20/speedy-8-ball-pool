//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/cue.h"
#include "mylibrary/box2d_utility.h"

using namespace cinder;
using namespace cinder::gl;

namespace myapp {
    Cue::Cue(BodyRef body, cinder::gl::TextureRef texture, vec2 pos)
            : Body(body, texture, pos)
    {
        body_->SetUserData(this->body_.get());
    }

    void Cue::setPosition( const ci::vec2 &pos )
    {
        body_->SetTransform( b2Vec2( pos.x, pos.y ), body_->GetAngle() );
    }
/*
    vec2 Cue::getPos() const
    {
        return vec2( body_->GetPosition().x, body_->GetPosition().y );
    }
    */
    void Cue::draw() {

        float conversion = Box2DUtility::getPointsPerMeter();
        vec2 pos = vec2( body_->GetPosition().x, body_->GetPosition().y ) * conversion;
        pos.x -= texture_->getWidth();
        float t = body_->GetAngle();
        Area destRect = texture_->getBounds();
        gl::ScopedModelMatrix modelScope;
        gl::translate( pos );
        gl::rotate( t );
        //float result = std::atan (((getPos().y)*100)/((getPos().x + texture_->getWidth())*100)) * 180 / 3.1415;
        //body_->SetFixedRotation(true);
        //gl::rotate(result);

        gl::draw(texture_, destRect);

    }
    void Cue::ApplyForce() {
        static int dir = 1;
        b2Vec2 pos = b2Vec2(body_->GetPosition().x, body_->GetPosition().y);
        body_->ApplyForce(b2Vec2(0, 0), pos);
        body_->SetLinearVelocity(b2Vec2(5*dir, 0));
        dir = dir* -1;
    }
}