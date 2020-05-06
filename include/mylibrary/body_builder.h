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
class Ball;
class Cue;
class Table;


using namespace cinder;
namespace myapp {
    class BodyBuilder {
    public:
        BodyBuilder(b2World * world);
        std::vector<std::shared_ptr<Ball>> SetBalls(double radius);
        std::shared_ptr<Ball> SetCueBall();
        std::shared_ptr<Cue> SetCue();
        std::shared_ptr<Table> SetTable();
        std::vector<std::shared_ptr<Wall>> SetWalls();
        BodyRef makeBodyShared( b2World *world, const b2BodyDef &bodyDef );
    private:

        std::shared_ptr<Wall> CreateWall(float posx, float posy, b2Vec2 width, b2Vec2 height);
        b2World *world_;
    };

}
#endif //FINALPROJECT_BODY_BUILDER_H
