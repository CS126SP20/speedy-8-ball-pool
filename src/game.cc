//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/game.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/gl/draw.h>
#include "mylibrary/box2d_utility.h"
#include "cinder/Rand.h"
#include "cinder/CinderAssert.h"
#include "mylibrary/body_builder.h"

using namespace cinder;
using std::string;

// constants
float kPowerBarX1 = 100;
float kPowerBarY1 = 600;
float kPowerBarX2 = 485;
float kPowerBarY2 = 620;
float kPowerMultiplicity = 7;
std::string kCueSoundFile = "cue.wav";
std::string kBallSoundFile = "poolballhit.wav";
std::string kWallSoundFile = "wall.wav";
std::string kPocketSoundFIle = "pocket.wav";

namespace myapp {
    void Game::Setup() {
        // initial game state
        state_ = GameState::kLogin;

        mLastStepTime = 0;
        b2Vec2 gravity( 0, 0 );
        world_.reset( new b2World( gravity ) );
        world_->SetContactListener( this );

        // creates all the bodies
        BodyBuilder builder(world_.get());
        table_ = builder.CreateTable();
        cue_ball = builder.CreateCueBall();
        balls_ = builder.CreateBalls(cue_ball->getRadius());
        walls_ = builder.CreateWalls();
        cue_ = builder.CreateCue();

        // creates all the audio refs
        audio::SourceFileRef sourceFile = audio::load( app::loadAsset( kCueSoundFile ) );
        cue_sound_ = audio::Voice::create( sourceFile );
        audio::SourceFileRef sourceFile2 = audio::load( app::loadAsset( kBallSoundFile ) );
        ball_sound_ = audio::Voice::create( sourceFile2 );
        audio::SourceFileRef sourceFile3 = audio::load( app::loadAsset( kWallSoundFile ) );
        wall_sound_ = audio::Voice::create( sourceFile3 );
        audio::SourceFileRef sourceFile4 = audio::load( app::loadAsset( kPocketSoundFIle ) );
        pocket_sound_ = audio::Voice::create( sourceFile4 );

    }

    void Game::Update() {
        auto currentTime = (float)app::getElapsedSeconds();
        float deltaTime = currentTime - mLastStepTime;

        world_->Step( deltaTime, 8, 3 );
        mLastStepTime = currentTime;

        // foul if game is not over and cue ball is hit in
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
        }  else if ( typeid( *objectA ) == typeid( Wall )) {
            HandleWallCollision(dynamic_cast<Wall *>( objectA ), objectB, contactPoint );
        } else if (typeid( *objectB ) == typeid( Wall )) {
            HandleWallCollision(dynamic_cast<Wall *>( objectB ), objectA, contactPoint );
        } else if ( typeid( *objectA ) == typeid( Ball )) {
            HandleBallCollision(dynamic_cast<Ball *>( objectA ), objectB, contactPoint );
        } else if (typeid( *objectB ) == typeid( Ball )) {
            HandleBallCollision(dynamic_cast<Ball *>( objectB ), objectA, contactPoint );
        }
    }

    void Game::HandleCueCollision(Cue *cue, Body *body, const vec2 &contactPoint) {
        state_ = GameState::kPlaying;
        cue_sound_->start();
        Ball *ball = dynamic_cast<Ball *>( body );
        if(ball != nullptr && ball->is_visible)
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
            // game is over if all the balls are not visible
            if (ball->is_visible) {
                over = false;
            }
        }
        return over;
    }
    void Game::DrawPowerBar() {
        cinder::gl::drawStrokedRect(Rectf(kPowerBarX1, kPowerBarY1, kPowerBarX2, kPowerBarY2));
        // draws size based on power of cue
        cinder::gl::drawSolidRect(Rectf(kPowerBarX1, kPowerBarY1,
                kPowerBarX1 + cue_->GetPower()*kPowerMultiplicity, kPowerBarY2));
    }
    void Game::Draw() {
        DrawPowerBar();
        table_->draw();

        if (table_->is_pocketed(cue_ball) && cue_ball->GetBody()->IsActive())
        {
            pocket_sound_->start();
            // if ball is hit in, set visibility to false and deactiviate body
            cue_ball->is_visible = false;
            cue_ball->GetBody()->SetActive(false);
        }
        else {
            cue_ball->draw();
            // reactivate cue ball after placed
            cue_ball->GetBody()->SetActive(true);
        }

        for (auto ball : balls_) {
            if (table_->is_pocketed(ball) && ball->GetBody()->IsActive())
            {
                pocket_sound_->start();
                // if ball is hit in, set visibility to false and deactiviate body
                ball->is_visible = false;
                ball->GetBody()->SetActive(false);
            }
            else
                ball->draw();
        }
        if (!cue_->IsHit()) {
            // if cue has not hit yet, draw cue and set body as active
            cue_->draw();
            cue_->GetBody()->SetActive(true);
        } else {
            // after cue hits ball, deactivate and do not draw
            cue_->GetBody()->SetActive(false);
        }
        for (auto wall : walls_) {
            wall->draw();
        }

    }

}
