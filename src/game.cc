//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/game.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include <algorithm>
#include <cmath>
#include <string>
#include "mylibrary/box2d_utility.h"

using namespace cinder;

namespace myapp {
    BodyRef Game::makeBodyShared( b2World *world, const b2BodyDef &bodyDef )
    {
        return BodyRef( world->CreateBody( &bodyDef ), [world]( b2Body *body ) { /*world->DestroyBody( body );*/ } );
    }
    void Game::setup() {
        mLastStepTime = 0;
        b2Vec2 gravity( 0, 0 );

        world_.reset( new b2World( gravity ) );
        world_->SetContactListener( this );

        table_.setTexture();


        auto img = cinder::loadImage(cinder::app::loadAsset("cue.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);

        vec2 center = app::getWindowCenter();
        b2BodyDef b2body1;
        b2body1.type = b2_dynamicBody;
        vec2 pos_pt(0, center.y - texture->getHeight()/2);
        auto pos = Box2DUtility::pointsToMeters(pos_pt);

        b2body1.position.Set(pos.x, pos.y);
        b2body1.linearVelocity = b2Vec2(0, 0);

        auto body1 = makeBodyShared(world_.get(), b2body1);
        //const float radius = 0.2;
        b2CircleShape shape0;
        shape0.m_radius = 0.2f;
        b2FixtureDef fixture0;
        fixture0.shape = &shape0;
        fixture0.density = 1.0f;
        fixture0.friction = 1.0f;
        fixture0.restitution = 0.4f;
        body1->CreateFixture(&fixture0);
        cue_ = std::shared_ptr<Cue>(new Cue(body1, texture, pos));


        int cur = 1;
       // float radius = 10 + 0.5;

        //double py = (100 + 500/2) - 5*radius;

        b2BodyDef b2body;
        b2body.type = b2_dynamicBody;
        std::string ball_file = "ball" + std::to_string(0) + ".png";
        auto img1 = cinder::loadImage(cinder::app::loadAsset(ball_file));
        gl::TextureRef texture1 = cinder::gl::Texture2d::create(img1);
        const float radius = texture1->getWidth() / 2.0f;
        vec2 pos0(texture->getWidth() + radius, app::getWindowHeight()/2);
        auto height = texture1->getHeight();
        auto width = texture1->getWidth();

        const float velMax = 5;
        vec2 pos1 = Box2DUtility::pointsToMeters(pos0);
        b2body.position.Set(pos1.x, pos1.y);
        b2body.linearVelocity = b2Vec2(0, 0);

        auto body = makeBodyShared(world_.get(), b2body);

        b2CircleShape shape;

        shape.m_radius = Box2DUtility::pointsToMeters(radius);
        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 1.0f;
        fixture.friction = 1.0f;
        fixture.restitution = 0.4f;
        body->CreateFixture(&fixture);

        // texture width of ball 1 might be greater than rest?

        auto ball = std::shared_ptr<Ball>(new Ball(body, texture1, pos1, radius));
        ball->setId(0);
        balls_.push_back(ball);

        double px = 600.0;
        double py = app::getWindowHeight()/2 - 4*radius;
        for (int i = 5; i > 0; --i)
        {
            for (int j = 0; j < i; ++j) {
                b2BodyDef b2body;
                b2body.type = b2_dynamicBody;

                vec2 pos_pt(px, py + radius*j*2);
                std::string ball_file = "ball" + std::to_string(cur) + ".png";
                auto img = cinder::loadImage(cinder::app::loadAsset(ball_file));
                gl::TextureRef texture = cinder::gl::Texture2d::create(img);

                auto height = texture->getHeight();
                auto width = texture->getWidth();

                const float velMax = 5;
                vec2 pos = Box2DUtility::pointsToMeters(pos_pt);
                b2body.position.Set(pos.x, pos.y);
                b2body.linearVelocity = b2Vec2(0, 0);
                //b2body.linearVelocity = b2Vec2(i%2 == 0 ? -1 : 1, 0);
                auto body = makeBodyShared(world_.get(), b2body);

                b2CircleShape shape;
                shape.m_radius = Box2DUtility::pointsToMeters(radius);
                b2FixtureDef fixture;
                fixture.shape = &shape;
                fixture.density = 1.0f;
                fixture.friction = 1.0f;
                fixture.restitution = 0.4f;
                body->CreateFixture(&fixture);
                auto ball = std::shared_ptr<Ball>(new Ball(body, texture, pos, radius));
                ball->setId(cur);
                balls_.push_back(ball);
                cur++;
            }

            px -= radius * std::sqrt(3);
            py += radius;
        }
        // 8-ball must be at the center of the triangle
        //std::swap(balls_[7]->getPos(), balls_[10]->getPos());

        // Oposite signs at the corners
        //std::swap(balls_[4]->getPos(), balls_[8]->getPos());
        //reload();

    }
    void Game::update() {
        float currentTime = (float)app::getElapsedSeconds();
        float deltaTime = currentTime - mLastStepTime;

        world_->Step( deltaTime, 8, 3 );

        mLastStepTime = currentTime;
    }
    void Game::CueHit() {
        cue_->ApplyForce();
    }
    void Game::draw() {

        table_.draw();

        for (auto ball : balls_) {
            ball->draw();
        }
        cue_->draw();
    }
    Game::~Game() {
        b2Body* b = world_->GetBodyList();
        while (b != NULL) {
            world_->DestroyBody(b);
            b = world_->GetBodyList();
        }
    }

}
