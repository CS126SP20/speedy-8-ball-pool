//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/cue.h"

using namespace cinder;
using namespace cinder::gl;

namespace myapp {
    Cue::Cue(BodyRef body, cinder::gl::TextureRef texture, vec2 pos)
            : Body(body, texture, pos)
    {}

    void Cue::setPosition( const ci::vec2 &pos )
    {
        //pos_ = pos;
        body_->SetTransform( b2Vec2( pos.x, pos.y ), body_->GetAngle() );
    }

    vec2 Cue::getPos() const
    {
        return vec2( body_->GetPosition().x, body_->GetPosition().y );
    }
    void Cue::draw() {
        float t = body_->GetAngle();

        gl::ScopedModelMatrix modelScope;
        float result = std::atan ((getPos().y)/(getPos().x - texture_->getWidth())) * 180 / 3.1415;

       // body_->SetFixedRotation(true);
        gl::rotate(result);
        gl::draw(texture_, pos_);
        /*
float conversion = 100;
vec2 pos = vec2( body_->GetPosition().x, body_->GetPosition().y ) * conversion;
float t = body_->GetAngle();


gl::ScopedModelMatrix modelScope;
gl::translate( pos );
gl::rotate( t );


ivec2 imgSize(texture_->getWidth(), texture_->getHeight());
ivec2 centerImage( 0, (app::getWindowHeight() - imgSize.y)/2);
ivec2 center(250, 300);
gl::draw(texture_, centerImage);
*/

    }
}