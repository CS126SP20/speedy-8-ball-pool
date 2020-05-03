//
// Created by lilyl on 5/2/2020.
//

#include "mylibrary/body_builder.h"

#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include "mylibrary/box2d_utility.h"

using namespace cinder;

namespace myapp {
    BodyRef BodyBuilder::makeBodyShared( b2World *world, const b2BodyDef &bodyDef )
    {
        return BodyRef( world->CreateBody( &bodyDef ), [world]( b2Body *body ) { /*world->DestroyBody( body );*/ } );
    }
    BodyBuilder::BodyBuilder(b2World * world) : world_(world)
    {}

    std::vector<std::shared_ptr<Ball>> BodyBuilder::SetBalls(double radius) {
        std::vector<std::shared_ptr<Ball>> balls_;

        //balls_.push_back(cue_ball);

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
                auto body = makeBodyShared(world_, b2body);

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
        return balls_;
    }
    std::shared_ptr<Ball> BodyBuilder::SetCueBall() {
        b2BodyDef b2body;
        b2body.type = b2_dynamicBody;
        std::string ball_file = "ball" + std::to_string(0) + ".png";
        auto img1 = cinder::loadImage(cinder::app::loadAsset(ball_file));
        gl::TextureRef texture1 = cinder::gl::Texture2d::create(img1);
        const float radius = texture1->getWidth() / 2.0f;
        vec2 pos0(300 + radius, app::getWindowHeight()/2);
        auto height = texture1->getHeight();
        auto width = texture1->getWidth();

        const float velMax = 5;
        vec2 pos1 = Box2DUtility::pointsToMeters(pos0);
        b2body.position.Set(pos1.x, pos1.y);
        b2body.linearVelocity = b2Vec2(0, 0);
        b2body.linearDamping = 0.8f;
        b2body.angularDamping = 0.8f;
        auto body = makeBodyShared(world_, b2body);

        b2CircleShape shape;
        shape.m_radius = Box2DUtility::pointsToMeters(radius);
        b2FixtureDef fixture;
        fixture.shape = &shape;
        fixture.density = 500.0f;
        fixture.friction = 1000000.0f;
        fixture.restitution = 0.5f;
        body->CreateFixture(&fixture);

        auto cue_ball = std::shared_ptr<Ball>(new Ball(body, texture1, pos1, radius));
        cue_ball->setId(0);
        return cue_ball;
    }
    std::shared_ptr<Cue> BodyBuilder::SetCue() {
        auto img = cinder::loadImage(cinder::app::loadAsset("cue.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);

        vec2 center = app::getWindowCenter();
        b2BodyDef b2body1;
        b2body1.type = b2_kinematicBody;
        //vec2 pos_pt(texture->getWidth() - 1, center.y - texture->getHeight()/2);
        vec2 pos_pt(200, 150);
        //vec2 pos_pt(cue_ball->getPos().x - texture->getWidth() - 1, cue_ball->getPos().y);
        auto pos = Box2DUtility::pointsToMeters(pos_pt);

        b2body1.position.Set(pos.x, pos.y);
        b2body1.linearVelocity = b2Vec2(0, 0);

        auto body1 = makeBodyShared(world_, b2body1);

        b2CircleShape shape0;
        shape0.m_radius = 0.001f;
        b2FixtureDef fixture0;
        fixture0.shape = &shape0;
        fixture0.density = 1.0f;
        fixture0.friction = 1.0f;
        fixture0.restitution = 0.4f;
        body1->CreateFixture(&fixture0);
        auto cue_ = std::shared_ptr<Cue>(new Cue(body1, texture, pos));
        return cue_;
    }
    std::shared_ptr<Table> BodyBuilder::SetTable() {
        auto img = cinder::loadImage(cinder::app::loadAsset("table.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);
        b2BodyDef body_table;
        body_table.position.Set(0, 0);
        body_table.type = b2_staticBody;
        body_table.linearDamping = 0.0f;
        body_table.angularDamping = 0.01f;
        body_table.active = false;
        auto body = makeBodyShared(world_, body_table);
        b2PolygonShape fShape;
        fShape.SetAsBox(texture->getWidth(), texture->getHeight());
        b2FixtureDef fixDef;
        fixDef.shape = &fShape;
        fixDef.density = 1.f;
        fixDef.friction = 1000000.0f;
        body->CreateFixture(&fixDef);

        auto pos = Box2DUtility::pointsToMeters(vec2(0, 0));
        auto table_ = std::shared_ptr<Table>(new Table(body, texture, pos));
        table_->SetPockets();
        return table_;
    }
    std::vector<std::shared_ptr<Wall>> BodyBuilder::SetWalls() {
        std::vector<std::shared_ptr<Wall>> walls;
        vec2 center_meters = Box2DUtility::pointsToMeters( vec2( app::getWindowCenter() ) );
        float inset = Box2DUtility::pointsToMeters(app::getWindowWidth() - 85);
        vec2 size( center_meters.x - inset, center_meters.y - inset );
        float posx = inset;
        float posy = center_meters.y;
        b2Vec2 width = b2Vec2( 0, - size.y );
        b2Vec2 height = b2Vec2( 0, size.y );
        auto wall1 = CreateWall(posx, posy, width, height);
        walls.push_back(wall1);

        float posx2 = Box2DUtility::pointsToMeters(app::getWindowWidth() - 715);
        auto wall2 = CreateWall(posx2, posy, width, height);
        walls.push_back(wall2);

        float top = Box2DUtility::pointsToMeters(app::getWindowHeight() - 225);
        float posx3 = center_meters.x;
        b2Vec2 width1 = b2Vec2( - size.x, 0);
        b2Vec2 height1 = b2Vec2( size.x, 0 );
        auto wall3 = CreateWall(posx3, top, width1, height1);
        walls.push_back(wall3);

        float bottom = Box2DUtility::pointsToMeters(app::getWindowHeight() - 530);
        auto wall4 = CreateWall(posx3, bottom, width1, height1);
        walls.push_back(wall4);
        return walls;
    }
    std::shared_ptr<Wall> BodyBuilder::CreateWall(float posx, float posy, b2Vec2 width, b2Vec2 height) {
        b2BodyDef bodyDef;
        bodyDef.position.Set(posx, posy);
        bodyDef.type = b2_staticBody;
        auto body1 = makeBodyShared(world_, bodyDef);
        b2EdgeShape leftWallShape;
        leftWallShape.Set(width, height);

        b2FixtureDef leftWallFixture;
        leftWallFixture.shape = &leftWallShape;
        leftWallFixture.density = 1.0f;
        leftWallFixture.friction = 1.0f;
        leftWallFixture.restitution = 0.5f;
        body1->CreateFixture(&leftWallFixture);
        auto wall = std::shared_ptr<Wall>(new Wall(body1));
        wall->width_ = 0;
        return wall;
    }
}