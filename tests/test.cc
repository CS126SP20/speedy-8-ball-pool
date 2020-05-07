// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>
#include <Box2D/Box2D.h>
#include "mylibrary/cue.h"
#include "mylibrary/box2d_utility.h"
#include "mylibrary/ball.h"
#include "mylibrary/table.h"
#include <mylibrary/game.h>

using namespace myapp;

TEST_CASE("Random sanity test", "[random]") {
  const float random = cinder::randFloat();
  REQUIRE(0. <= random);
  REQUIRE(random <= 1.);
}


TEST_CASE("Cue calculate angle test", "[angle]") {

    vec2 center = vec2(0, 0);
    b2BodyDef b2body1;
    b2body1.type = b2_kinematicBody;
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Cue> cue = std::shared_ptr<myapp::Cue>(new myapp::Cue(nullptr, nullptr, pos));

    vec2 pos1(0, 0);
    vec2 pos2(1, 1);
    float angle = cue->CalculateAngle(pos1, pos2);
    REQUIRE(angle <= 2.3561945);
}

TEST_CASE("Cue set power", "[power]") {
    vec2 center = vec2(0, 0);
    b2BodyDef b2body1;
    b2body1.type = b2_kinematicBody;
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Cue> cue = std::shared_ptr<myapp::Cue>(new myapp::Cue(nullptr, nullptr, pos));
    cue->DecreasePower();
    REQUIRE(cue->GetPower() == 25);
    cue->IncreasePower();
    REQUIRE(cue->GetPower() == 30);
}

TEST_CASE("Ball set id", "[ball id]") {
    vec2 center = vec2(0, 0);
    b2BodyDef b2body1;
    b2body1.type = b2_kinematicBody;
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Ball> ball = std::shared_ptr<myapp::Ball>(new myapp::Ball(nullptr, nullptr, pos, 10.5));
    ball->setId(5);
    REQUIRE(ball->id_ == 5);
}

TEST_CASE("Ball is visible", "[ball visibility]") {
    vec2 center = vec2(0, 0);
    b2BodyDef b2body1;
    b2body1.type = b2_kinematicBody;
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Ball> ball = std::shared_ptr<myapp::Ball>(new myapp::Ball(nullptr, nullptr, pos, 10.5));
    REQUIRE(ball->is_visible);
}

TEST_CASE("Table pockets", "[pockets]") {
    vec2 center = vec2(0, 0);
    b2BodyDef b2body1;
    b2body1.type = b2_kinematicBody;
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Table> table = std::shared_ptr<myapp::Table>(new myapp::Table(nullptr, nullptr, pos));
    std::vector<vec2> pockets;
    pockets.push_back(vec2(1, 1));
    table->TestPockets(pockets);
    REQUIRE(table->GetPockets().size() == 1);
}

TEST_CASE("Table ball pocketed", "[ball pocketed]") {
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Table> table = std::shared_ptr<myapp::Table>(new myapp::Table(nullptr, nullptr, pos));
    std::vector<vec2> pockets;
    pockets.push_back(vec2(1, 1));
    table->TestPockets(pockets);

    vec2 pos_pt1(1, 1);
    auto pos1 = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Ball> ball = std::shared_ptr<myapp::Ball>(new myapp::Ball(nullptr, nullptr, pos1, 10.5));

    // ball that is within pocket should be pocketed
    REQUIRE(table->is_pocketed(ball));
}

TEST_CASE("Table ball not pocketed", "[ball not pocketed]") {
    vec2 pos_pt(200, 150);
    auto pos = Box2DUtility::pointsToMeters(pos_pt);
    std::shared_ptr<myapp::Table> table = std::shared_ptr<myapp::Table>(new myapp::Table(nullptr, nullptr, pos));
    std::vector<vec2> pockets;
    pockets.push_back(vec2(1, 1));
    table->TestPockets(pockets);

    vec2 pos_pt1(200, 200);
    auto pos1 = Box2DUtility::pointsToMeters(pos_pt1);
    std::shared_ptr<myapp::Ball> ball = std::shared_ptr<myapp::Ball>(new myapp::Ball(nullptr, nullptr, pos1, 1));

    // ball that is not within distance should not be pocketed
    REQUIRE(!table->is_pocketed(ball));
}

TEST_CASE("Not game over", "[not game over]") {
    myapp::Game game;
    vec2 pos_pt1(200, 200);
    auto pos1 = Box2DUtility::pointsToMeters(pos_pt1);
    std::shared_ptr<myapp::Ball> ball = std::shared_ptr<myapp::Ball>(new myapp::Ball(nullptr, nullptr, pos1, 1));
    ball->SetVisibility(true);
    std::vector<std::shared_ptr<myapp::Ball>> balls;
    balls.push_back(ball);
    game.SetBalls(balls);
    // game not over when ball is visible
    bool over = game.GameOver();
    REQUIRE(!over);
}

TEST_CASE("game over", "[game over]") {
    myapp::Game game;
    vec2 pos_pt1(200, 200);
    auto pos1 = Box2DUtility::pointsToMeters(pos_pt1);
    std::shared_ptr<myapp::Ball> ball = std::shared_ptr<myapp::Ball>(new myapp::Ball(nullptr, nullptr, pos1, 1));
    ball->SetVisibility(false);
    std::vector<std::shared_ptr<myapp::Ball>> balls;
    balls.push_back(ball);
    game.SetBalls(balls);
    // game over when balls all not visible
    bool over = game.GameOver();
    REQUIRE(over);
}