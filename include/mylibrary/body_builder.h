//
// Created by lilyl on 5/2/2020.
//

#ifndef FINALPROJECT_BODY_BUILDER_H
#define FINALPROJECT_BODY_BUILDER_H

#include <string>
#include <vector>
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "body.h"
#include "table.h"
#include "ball.h"
#include "cue.h"

// forward declaration
class Ball;
class Cue;
class Table;

using namespace cinder;
namespace myapp {
    /**
     * create all the bodies used in the game
     */
    class BodyBuilder {
    public:
        BodyBuilder(b2World * world);
        // creates all balls except cue ball and return vector of balls
        std::vector<std::shared_ptr<Ball>> CreateBalls(double radius);
        // returns a single cue ball
        std::shared_ptr<Ball> CreateCueBall();
        // returns a created cue
        std::shared_ptr<Cue> CreateCue();
        // returns a created table
        std::shared_ptr<Table> CreateTable();
        std::vector<std::shared_ptr<Wall>> CreateWalls();
        // adds body to the world
        BodyRef makeBodyShared( b2World *world, const b2BodyDef &bodyDef );
    private:
        // creates a single wall at specified position
        std::shared_ptr<Wall> CreateWall(float posx, float posy, b2Vec2 width, b2Vec2 height);
        b2World *world_;
    };

}
#endif //FINALPROJECT_BODY_BUILDER_H
