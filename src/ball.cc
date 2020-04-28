//
// Created by lilyl on 4/17/2020.
//

#include "mylibrary/ball.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include "mylibrary/box2d_utility.h"

using namespace cinder;

namespace myapp {
    Ball::Ball(BodyRef body, cinder::gl::TextureRef texture, vec2 pos, float radius)
        : radius_(radius), Body(body, texture, pos)
    {
        body_->SetUserData(this);
    }


    void Ball::setPosition( const ci::vec2 &pos )
    {
        //pos_ = pos;
        body_->SetTransform( b2Vec2( pos.x, pos.y ), body_->GetAngle() );
    }

    vec2 Ball::getPos() const
    {
        return vec2( body_->GetPosition().x, body_->GetPosition().y );
        //return pos_;
    }
    void Ball::setId(int id) {
        id_ = id;
    }
    void Ball::draw() {
        if (is_visible) {
            float conversion = Box2DUtility::getPointsPerMeter();
            vec2 pos = vec2( body_->GetPosition().x, body_->GetPosition().y ) * conversion;
            Rectf imageDest(-radius_-2, -radius_-2, radius_+2, radius_+2);

            float t = body_->GetAngle();
            //auto radius = texture_->getWidth() / 2.0f;

            gl::ScopedModelMatrix modelScope;
            //ivec2 imgSize(texture_->getWidth(), texture_->getHeight());
            // ivec2 centerImage( data.pos_x,  (app::getWindowHeight() - imgSize.y)/2);
            gl::translate(pos);
            gl::rotate( t );
            gl::draw(texture_, imageDest);
        }

        //data.pos_x += 1;
        //gl::draw(texture_, imageDest);
        /**
        ivec2 imgSize(texture_->getWidth(), texture_->getHeight());
        ivec2 centerImage( data.pos_x, (app::getWindowHeight() - imgSize.y)/2);
        ivec2 center(300, 300);
        gl::draw(texture_, centerImage);
         */
    }
    void Ball::handleCollision(Ball *ball, const ci::vec2 &contactPoint ) {
        body_->SetLinearVelocity(b2Vec2(20, 0));
    }
/*
    bool Ball::isCollidingWith( Ball other )
    {
        // This is a simplification: there is a change we will miss the collision.
        return ( glm::distance(pos_, other.pos_ ) < ( 2 * radius ) );
    }
    */
}