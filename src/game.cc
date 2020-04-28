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
#include "cinder/Log.h"
#include "cinder/Rand.h"
#include "cinder/CinderAssert.h"

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


        setTable();
        setCue();
        setBalls();

    }
    void Game::setBalls() {
        // set cue ball

        b2BodyDef b2body;
        b2body.type = b2_dynamicBody;
        std::string ball_file = "ball" + std::to_string(0) + ".png";
        auto img1 = cinder::loadImage(cinder::app::loadAsset(ball_file));
        gl::TextureRef texture1 = cinder::gl::Texture2d::create(img1);
        const float radius = texture1->getWidth() / 2.0f;
        vec2 pos0(cue_->GetWidth() + radius, app::getWindowHeight()/2);
        auto height = texture1->getHeight();
        auto width = texture1->getWidth();

        const float velMax = 5;
        vec2 pos1 = Box2DUtility::pointsToMeters(pos0);
        b2body.position.Set(pos1.x, pos1.y);
        b2body.linearVelocity = b2Vec2(0, 0);
        b2body.linearDamping = 0.8f;
        b2body.angularDamping = 0.8f;
        auto body = makeBodyShared(world_.get(), b2body);

        b2CircleShape shape;
        shape.m_radius = Box2DUtility::pointsToMeters(radius);
        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 500.0f;
        fixture.friction = 1000000.0f;
        fixture.restitution = 0.5f;
        body->CreateFixture(&fixture);

        auto ball = std::shared_ptr<Ball>(new Ball(body, texture1, pos1, radius));
        ball->setId(0);
        balls_.push_back(ball);

        // set rest of balls
        int cur = 1;
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
                b2body.linearDamping = 0.8f;
                b2body.angularDamping = 0.8f;
                //b2body.linearVelocity = b2Vec2(i%2 == 0 ? -1 : 1, 0);
                auto body = makeBodyShared(world_.get(), b2body);

                b2CircleShape shape;
                shape.m_radius = Box2DUtility::pointsToMeters(radius);
                b2FixtureDef fixture;
                fixture.shape = &shape;
                fixture.density = 500.0f;
                fixture.friction = 5.0f;
                fixture.restitution = 0.5f;
                body->CreateFixture(&fixture);
                auto ball = std::shared_ptr<Ball>(new Ball(body, texture, pos, radius));
                ball->setId(cur);
                balls_.push_back(ball);
                cur++;
            }

            px -= radius * std::sqrt(3);
            py += radius;
        }

    }
    void Game::setCue() {
        // set cue

        auto img = cinder::loadImage(cinder::app::loadAsset("cue.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);

        vec2 center = app::getWindowCenter();
        b2BodyDef b2body1;
        b2body1.type = b2_kinematicBody;
        vec2 pos_pt(texture->getWidth() - 1, center.y - texture->getHeight()/2);
        //vec2 pos_pt(0, center.y - texture->getHeight()/2);
        auto pos = Box2DUtility::pointsToMeters(pos_pt);

        b2body1.position.Set(pos.x, pos.y);
        b2body1.linearVelocity = b2Vec2(0, 0);

        auto body1 = makeBodyShared(world_.get(), b2body1);
        //const float radius = 0.2;

        /*
         * b2PolygonShape polygonShape;
          polygonShape.SetAsBox( 0.5f, 1.25f );
          m_body->CreateFixture(&polygonShape, 1);
         */
       // b2PolygonShape shape0;
        //shape0.SetAsBox(texture->getWidth(), texture->getHeight());

        b2CircleShape shape0;
        shape0.m_radius = 0.01f;
        b2FixtureDef fixture0;
        fixture0.shape = &shape0;
        fixture0.density = 1.0f;
        fixture0.friction = 1.0f;
        fixture0.restitution = 0.4f;
        body1->CreateFixture(&fixture0);
        cue_ = std::shared_ptr<Cue>(new Cue(body1, texture, pos));
    }

    void Game::setTable() {
        auto img = cinder::loadImage(cinder::app::loadAsset("table.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);
        b2BodyDef body_table;
        body_table.position.Set(0, 0);
        body_table.type = b2_staticBody;
        body_table.linearDamping = 0.0f;
        body_table.angularDamping = 0.01f;
        body_table.active = false;
        auto body = makeBodyShared(world_.get(), body_table);
        b2PolygonShape fShape;
        fShape.SetAsBox(texture->getWidth(), texture->getHeight());
        b2FixtureDef fixDef;
        fixDef.shape = &fShape;
        fixDef.density = 1.f;
        fixDef.friction = 1000000.0f;
        body->CreateFixture(&fixDef);

        auto pos = Box2DUtility::pointsToMeters(vec2(0, 0));
        table_ = std::shared_ptr<Table>(new Table(body, texture, pos));
        //table_->setTexture();
        table_->SetPockets();
        // set walls
        vec2 center_meters = Box2DUtility::pointsToMeters( vec2( app::getWindowCenter() ) );
        float inset = Box2DUtility::pointsToMeters(app::getWindowWidth() - 85);

        vec2 size( center_meters.x - inset, center_meters.y - inset );

        b2BodyDef bodyDef;
        bodyDef.position.Set( inset, center_meters.y );
        bodyDef.type = b2_staticBody;
        auto body1 = makeBodyShared(world_.get(), bodyDef);
        b2EdgeShape leftWallShape;
        leftWallShape.Set( b2Vec2( 0, - size.y ), b2Vec2( 0, size.y ) );

        b2FixtureDef leftWallFixture;
        leftWallFixture.shape = &leftWallShape;
        leftWallFixture.density = 1.0f;
        leftWallFixture.friction = 1.0f;
        leftWallFixture.restitution = 0.5f;
        body1->CreateFixture(&leftWallFixture);
        auto wall = std::shared_ptr<Wall>(new Wall(body1));
        wall->mSide = Wall::Side::LEFT;
        wall->width_ = 0;
        walls_.push_back(wall);

        b2BodyDef bodyDef2;
        float left = Box2DUtility::pointsToMeters(app::getWindowWidth() - 715);
        bodyDef2.position.Set(left, center_meters.y );
        bodyDef2.type = b2_staticBody;
        auto body2 = makeBodyShared(world_.get(), bodyDef2);
        b2EdgeShape rightWallShape;
        rightWallShape.Set( b2Vec2( 0, - size.y ), b2Vec2( 0, size.y ) );

        b2FixtureDef rightWallFixture;
        rightWallFixture.shape = &rightWallShape;
        rightWallFixture.density = 1.0f;
        rightWallFixture.friction = 1.0f;
        rightWallFixture.restitution = 0.5f;
        body2->CreateFixture(&rightWallFixture);
        auto wall2 = std::shared_ptr<Wall>(new Wall(body2));
        wall2->mSide = Wall::Side::RIGHT;
        wall2->width_ = 0;
        walls_.push_back(wall2);

       // vec2 center_meters = Box2DUtility::pointsToMeters( vec2( app::getWindowCenter() ) );
        float top = Box2DUtility::pointsToMeters(app::getWindowHeight() - 225);
        b2BodyDef bodyDef3;
        bodyDef3.position.Set(center_meters.x, top);
        bodyDef3.type = b2_staticBody;
        auto body3 = makeBodyShared(world_.get(), bodyDef3);
        b2EdgeShape topWallShape;
        topWallShape.Set( b2Vec2( - size.x, 0), b2Vec2( size.x, 0 ) );

        b2FixtureDef topWallFixture;
        topWallFixture.shape = &topWallShape;
        topWallFixture.density = 1.0f;
        topWallFixture.friction = 1.0f;
        topWallFixture.restitution = 0.5f;
        body3->CreateFixture(&topWallFixture);
        auto wall3 = std::shared_ptr<Wall>(new Wall(body3));
        wall3->mSide = Wall::Side::TOP;
        wall3->width_ = 0;
        walls_.push_back(wall3);


        float bottom = Box2DUtility::pointsToMeters(app::getWindowHeight() - 530);
        b2BodyDef bodyDef4;
        bodyDef4.position.Set(center_meters.x, bottom);
        bodyDef4.type = b2_staticBody;
        auto body4 = makeBodyShared(world_.get(), bodyDef4);
        b2EdgeShape bottomWallShape;
        bottomWallShape.Set( b2Vec2( - size.x, 0), b2Vec2( size.x, 0 ) );

        b2FixtureDef bottomWallFixture;
        bottomWallFixture.shape = &bottomWallShape;
        bottomWallFixture.density = 1.0f;
        bottomWallFixture.friction = 1.0f;
        bottomWallFixture.restitution = 0.5f;
        body4->CreateFixture(&bottomWallFixture);
        auto wall4 = std::shared_ptr<Wall>(new Wall(body4));
        wall4->mSide = Wall::Side::BOTTOM;
        wall4->width_ = 0;
        walls_.push_back(wall4);

    }
    void Game::update() {
        float currentTime = (float)app::getElapsedSeconds();
        float deltaTime = currentTime - mLastStepTime;

        world_->Step( deltaTime, 8, 3 );

        mLastStepTime = currentTime;
    }
    void Game::BeginContact( b2Contact* contact ) {
        void *userDataA = contact->GetFixtureA()->GetBody()->GetUserData();
        void *userDataB = contact->GetFixtureB()->GetBody()->GetUserData();

        CI_ASSERT( userDataA && userDataB );

        b2WorldManifold worldManifold;
        contact->GetWorldManifold( &worldManifold );

        vec2 contactPoint = Box2DUtility::metersToPoints( Box2DUtility::toCinder( worldManifold.points[0] ) );

        Body *objectA = static_cast<Body *>( userDataA );
        Body *objectB = static_cast<Body *>( userDataB );

        if( typeid( *objectA ) == typeid( Cue ) )
            handleCueCollision(dynamic_cast<Cue *>( objectA ), objectB, contactPoint );
    }
    void Game::handleCueCollision(Cue *cue, Body *body, const vec2 &contactPoint) {
        Ball *ball = dynamic_cast<Ball *>( body );
        if(ball != NULL && ball->is_visible)
            cue->handleCollision(ball, contactPoint );
    }
    void Game::CueHit() {
        cue_->ApplyForce();
    }
    void Game::CueRecoil() {
        cue_->Recoil();
    }
    void Game::draw() {

        table_->draw();
        /*
        for (auto& p : table_.pockets_)
        {
            double r = 10;
            cinder::gl::drawSolidCircle(p + cinder::vec2(r, r), r );
        }
         */
        for (auto ball : balls_) {
            if (table_->is_pocketed(ball))
            {
                ball->is_visible = false;
                //balls_.erase(std::remove(balls_.begin(), balls_.end(), ball), balls_.end());
            }
            else
                ball->draw();
        }
        cue_->draw();

        for (auto wall : walls_) {
            wall->draw();
        }

    }
    Game::~Game() {
        b2Body* b = world_->GetBodyList();
        while (b != NULL) {
            world_->DestroyBody(b);
            b = world_->GetBodyList();
        }
    }

}
