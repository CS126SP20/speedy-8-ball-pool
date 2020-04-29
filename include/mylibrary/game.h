//
// Created by lilyl on 4/18/2020.
//

#ifndef FINALPROJECT_GAME_H
#define FINALPROJECT_GAME_H


//ci::vec2 toCinder( const b2Vec2 &vec );
//ci::Color toCinder( const b2Color &color );
#include <Box2D/Box2D.h>
#include <memory>
#include "table.h"
#include "ball.h"
#include "cue.h"
class Ball;
class Cue;
class Table;

namespace myapp {

    class Game : public b2ContactListener {

    public:
        virtual ~Game();
        BodyRef	makeBodyShared( b2World *world, const b2BodyDef &bodyDef );
        typedef std::vector<std::shared_ptr<Wall> >		WallContainerT;
        typedef std::vector<std::shared_ptr<Ball> >		BallContainerT;
        b2World* getWorld() const		{ return world_.get(); }
        const BallContainerT& getBalls() const	{ return balls_; }
        void handleCueCollision(Cue *cue, Body *body, const vec2 &contactPoint);
        void BeginContact( b2Contact* contact );
        void setBalls();
        void setCue();
        void setTable();
        void setup();
        void draw();
        void update();
        void CueHit();
        void CueRecoil();
        bool RoundOver();
        std::shared_ptr<Cue> cue_;
    private:
        std::shared_ptr<Table> table_;
        std::vector<std::shared_ptr<Ball>> balls_;
        std::shared_ptr<Ball> cue_ball;
        std::vector<std::shared_ptr<Ball>> scored_balls_;
        std::vector<std::shared_ptr<Wall>> walls_;
        std::unique_ptr<b2World> world_;
        float mLastStepTime, mCurrentDecent;

    };
}
#endif //FINALPROJECT_GAME_H
