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
#include "mylibrary/body_builder.h"

using namespace cinder;
using std::string;

namespace myapp {
    void Game::setup() {
        state_ = GameState::kLogin;

        mLastStepTime = 0;
        b2Vec2 gravity( 0, 0 );

        world_.reset( new b2World( gravity ) );
        world_->SetContactListener( this );

        BodyBuilder builder(world_.get());

        table_ = builder.SetTable();
        cue_ball = builder.SetCueBall();
        balls_ = builder.SetBalls(cue_ball->getRadius());
        walls_ = builder.SetWalls();
        cue_ = builder.SetCue();

        audio::SourceFileRef sourceFile = audio::load( app::loadAsset( "cue.wav" ) );
        cue_sound_ = audio::Voice::create( sourceFile );
        audio::SourceFileRef sourceFile2 = audio::load( app::loadAsset( "poolballhit.wav" ) );
        ball_sound_ = audio::Voice::create( sourceFile2 );
        audio::SourceFileRef sourceFile3 = audio::load( app::loadAsset( "wall.wav" ) );
        wall_sound_ = audio::Voice::create( sourceFile3 );
        audio::SourceFileRef sourceFile4 = audio::load( app::loadAsset( "pocket.wav" ) );
        pocket_sound_ = audio::Voice::create( sourceFile4 );



    }

    void Game::update() {
        auto currentTime = (float)app::getElapsedSeconds();
        float deltaTime = currentTime - mLastStepTime;

        world_->Step( deltaTime, 8, 3 );

        mLastStepTime = currentTime;

        if (!GameOver() && !cue_ball->is_visible) {
            state_ = GameState::kFoul;
        }
        if (GameOver()) {
            state_= GameState::kGameOver;
        }

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
            HandleCueCollision(dynamic_cast<Cue *>( objectA ), objectB, contactPoint );
        else if ( typeid( *objectB ) == typeid( Cue )) {
            HandleCueCollision(dynamic_cast<Cue *>( objectB ), objectA, contactPoint );
        } else if ( typeid( *objectA ) == typeid( Ball )) {
            HandleBallCollision(dynamic_cast<Ball *>( objectA ), objectB, contactPoint );
        } else if (typeid( *objectB ) == typeid( Ball )) {
            HandleBallCollision(dynamic_cast<Ball *>( objectB ), objectA, contactPoint );
        } else if ( typeid( *objectA ) == typeid( Wall )) {
            HandleWallCollision(dynamic_cast<Wall *>( objectA ), objectB, contactPoint );
        } else if (typeid( *objectB ) == typeid( Wall )) {
            HandleWallCollision(dynamic_cast<Wall *>( objectB ), objectA, contactPoint );
        }
    }
    void Game::HandleCueCollision(Cue *cue, Body *body, const vec2 &contactPoint) {
        state_ = GameState::kPlaying;
        cue_sound_->start();
        Ball *ball = dynamic_cast<Ball *>( body );
        if(ball != NULL && ball->is_visible)
            cue->handleCollision(ball, contactPoint );

    }
    void Game::HandleBallCollision(Ball *ball_, Body *body, const vec2 &contactPoint) {
        state_ = GameState::kPlaying;
        ball_sound_->start();

    }
    void Game::HandleWallCollision(Wall *wall, Body *body, const vec2 &contactPoint) {
        state_ = GameState::kPlaying;
        wall_sound_->start();

    }
    void Game::SetCueBall(const vec2& pos) {
        cue_ball->SetPosition(pos);
        state_ = GameState::kPlaying;
    }
    void Game::CueHit() {
        cue_->ApplyForce();
    }
    bool Game::GameOver() {
        bool over = true;
        for (auto ball : balls_) {
            if (ball->is_visible) {
                over = false;
            }
        }
        return over;
    }
    void Game::DrawPowerBar() {
        cinder::gl::drawStrokedRect(Rectf(100, 600, 485, 620));
        cinder::gl::drawSolidRect(Rectf(100, 600, 100 + cue_->GetPower()*7, 620));
    }
    void Game::draw() {
        DrawPowerBar();
        table_->draw();
        if (table_->is_pocketed(cue_ball) && cue_ball->GetBody()->IsActive())
        {
            pocket_sound_->start();
            cue_ball->is_visible = false;
            cue_ball->GetBody()->SetActive(false);
        }
        else {
            cue_ball->draw();
            cue_ball->GetBody()->SetActive(true);
        }

        for (auto ball : balls_) {
            if (table_->is_pocketed(ball) && ball->GetBody()->IsActive())
            {
                pocket_sound_->start();
                ball->is_visible = false;
                ball->GetBody()->SetActive(false);
            }
            else
                ball->draw();
        }
        if (!cue_->hit) {
            cue_->draw();
            cue_->GetBody()->SetActive(true);
        } else {
            cue_->GetBody()->SetActive(false);
        }

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
