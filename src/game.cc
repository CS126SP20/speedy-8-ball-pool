//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/game.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include <algorithm>
#include <cmath>
#include <string>

using namespace cinder;

namespace myapp {
    BodyRef Game::makeBodyShared( b2World *world, const b2BodyDef &bodyDef )
    {
        return BodyRef( world->CreateBody( &bodyDef ), [world]( b2Body *body ) { /*world->DestroyBody( body );*/ } );
    }
    void Game::setup() {
        mLastStepTime = 0;
        b2Vec2 gravity( 0, 10 );

        world_.reset( new b2World( gravity ) );
        world_->SetContactListener( this );

        table_.setTexture();


        int cur = 1;
        double radius = 10 + 0.5;

        //double py = (100 + 500/2) - 5*radius;
        vec2 pos0(300, app::getWindowHeight()/2 - radius);
        b2BodyDef b2body;
        b2body.type = b2_staticBody;
        auto body = makeBodyShared(world_.get(), b2body);
        std::string ball_file = "ball" + std::to_string(0) + ".png";
        auto img1 = cinder::loadImage(cinder::app::loadAsset(ball_file));
        gl::TextureRef texture1 = cinder::gl::Texture2d::create(img1);
        auto ball = std::shared_ptr<Ball>(new Ball(body, texture1, pos0));
        ball->setId(0);
        balls_.push_back(ball);

        double px = 500.0;
        double py = app::getWindowHeight()/2 - 5*radius;
        for (int i = 5; i > 0; --i)
        {
            for (int j = 0; j < i; ++j) {
                b2BodyDef b2body;
                b2body.type = b2_staticBody;
                auto body = makeBodyShared(world_.get(), b2body);
                vec2 pos(px, py + radius*j*2);
                std::string ball_file = "ball" + std::to_string(cur) + ".png";
                auto img = cinder::loadImage(cinder::app::loadAsset(ball_file));
                gl::TextureRef texture = cinder::gl::Texture2d::create(img);
                auto ball = std::shared_ptr<Ball>(new Ball(body, texture, pos));
                ball->setId(cur);
                balls_.push_back(ball);
                cur++;
            }

            px -= radius * std::sqrt(3);
            py += radius;
        }
        // 8-ball must be at the center of the triangle
        std::swap(balls_[7]->getPos(), balls_[10]->getPos());

        // Oposite signs at the corners
        std::swap(balls_[4]->getPos(), balls_[8]->getPos());
        //reload();

        vec2 center = app::getWindowCenter();
        b2BodyDef b2body1;
        b2body1.type = b2_staticBody;
        auto body1 = makeBodyShared(world_.get(), b2body1);
        auto img = cinder::loadImage(cinder::app::loadAsset("cue.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);
        //app::getWindowHeight()/2 - radius/2
        vec2 centerImage( 0, center.y - texture->getHeight()/2);
        cue_ = std::shared_ptr<Cue>(new Cue(body1, texture, centerImage));
    }
    void Game::update() {
        float currentTime = (float)app::getElapsedSeconds();
        float deltaTime = currentTime - mLastStepTime;

        world_->Step( deltaTime, 8, 3 );

        mLastStepTime = currentTime;
    }

    void Game::draw() {

        table_.draw();

        for (auto ball : balls_) {
            ball->draw();
        }
        cue_->draw();
    }
}
