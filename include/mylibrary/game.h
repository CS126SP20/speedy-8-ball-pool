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
    enum class GameState {
        kLogin,
        kPlaying,
        kFoul,
        kGameOver,
    };

    class Game : public b2ContactListener {

    public:
        virtual ~Game();
        typedef std::vector<std::shared_ptr<Wall> >		WallContainerT;
        typedef std::vector<std::shared_ptr<Ball> >		BallContainerT;
        b2World* getWorld() const		{ return world_.get(); }
        const BallContainerT& getBalls() const	{ return balls_; }
        void HandleCueCollision(Cue *cue, Body *body, const vec2 &contactPoint);
        void HandleBallCollision(Ball *ball_, Body *body, const vec2 &contactPoint);
        void HandleWallCollision(Wall *wall, Body *body, const vec2 &contactPoint);
        void BeginContact( b2Contact* contact );
        void setup();
        void draw();
        void update();
        void CueHit();
        bool GameOver();
        void SetCueBall(const vec2& pos);
        void DrawPowerBar();
        std::shared_ptr<Cue> cue_;
        GameState GetState() {return state_;}
        void SetGameState(GameState state) {state_ = state;}
    private:
        std::shared_ptr<Table> table_;
        std::vector<std::shared_ptr<Ball>> balls_;
        std::shared_ptr<Ball> cue_ball;
        std::vector<std::shared_ptr<Wall>> walls_;
        std::unique_ptr<b2World> world_;
        float mLastStepTime, mCurrentDecent;
        bool IsOver_;
        GameState state_;
        audio::VoiceRef ball_sound_;
        audio::VoiceRef cue_sound_;
        audio::VoiceRef wall_sound_;
        audio::VoiceRef pocket_sound_;

    };
}
#endif //FINALPROJECT_GAME_H
