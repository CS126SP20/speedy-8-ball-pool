// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include "mylibrary/cue.h"
#include "mylibrary/box2d_utility.h"
#include "mylibrary/ball.h"
#include "mylibrary/table.h"
#include <mylibrary/example.h>
#include <mylibrary/body_builder.h>
#include "mylibrary/body.h"

using namespace myapp;

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}

/*
TEST_CASE("Cue calculate angle test", "[angle]") {
    b2Vec2 gravity( 0, 0 );
    std::unique_ptr<b2World> world_;
    world_.reset( new b2World( gravity ) );
    //world_->SetContactListener( this );
    BodyBuilder builder(world_.get());

    vec2 center = app::getWindowCenter();
    b2BodyDef b2body1;
    b2body1.type = b2_kinematicBody;
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);

    b2body1.position.Set(pos.x, pos.y);
    b2body1.linearVelocity = b2Vec2(0, 0);

    auto body1 = builder.makeBodyShared(world_, b2body1);
    b2CircleShape shape0;
    shape0.m_radius = 0.001f;
    b2FixtureDef fixture0;
    fixture0.shape = &shape0;
    fixture0.density = 1.0f;
    fixture0.friction = 1.0f;
    fixture0.restitution = 0.4f;
    body1->CreateFixture(&fixture0);
    auto cue = std::shared_ptr<Cue>(new Cue(body1, NULL, pos));

    vec2 pos1(0, 0);
    vec2 pos2(1, 1);
    //auto cue = builder.SetCue();
    float angle = cue->CalculateAngle(pos1, pos2);
    std::cout << angle;
}
*/