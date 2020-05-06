//
// Created by lilyl on 4/18/2020.
//

#ifndef FINALPROJECT_GAME_H
#define FINALPROJECT_GAME_H


//ci::vec2 toCinder( const b2Vec2 &vec );
//ci::Color toCinder( const b2Color &color );
#include <Box2D/Box2D.h>
#include <memory>
#include <cinder/audio/Source.h>
#include <cinder/audio/Utilities.h>
#include <cinder/audio/audio.h>
#include "table.h"
#include "ball.h"
#include "cue.h"
class Ball;
class Cue;
class Table;
using namespace cinder;
namespace myapp {
    /**
     * Game state class to track current state
     */
    enum class GameState {
        kLogin,
        kPlaying,
        kFoul,
        kGameOver,
    };
/**
 * Main Game class
 */
    class Game : public b2ContactListener {
    public:
        ~Game() override;
        // sets up the world and all the bodies
        void Setup();
        // draws all the bodies
        void Draw();
        // updates the game state and body visibility
        void Update();
        // calls the cue hit
        void CueHit();
        // checks when all the balls are hit in
        bool GameOver();
        // set the position of the cue ball if cue ball gets hit in
        void SetCueBall(const vec2& pos);
        std::shared_ptr<Cue> cue_;
        GameState GetState() {return state_;}
        void SetGameState(GameState state) {state_ = state;}
    private:
        std::shared_ptr<Table> table_;
        std::vector<std::shared_ptr<Ball>> balls_;
        std::shared_ptr<Ball> cue_ball;
        std::vector<std::shared_ptr<Wall>> walls_;
        std::unique_ptr<b2World> world_;
        float mLastStepTime;
        GameState state_;
        audio::VoiceRef ball_sound_;
        audio::VoiceRef cue_sound_;
        audio::VoiceRef wall_sound_;
        audio::VoiceRef pocket_sound_;

        void BeginContact( b2Contact* contact ) override;
        void HandleCueCollision(Cue *cue, Body *body, const vec2 &contactPoint);
        void HandleBallCollision(Ball *ball_, Body *body, const vec2 &contactPoint);
        void HandleWallCollision(Wall *wall, Body *body, const vec2 &contactPoint);
        void DrawPowerBar();


    };
}
#endif //FINALPROJECT_GAME_H
