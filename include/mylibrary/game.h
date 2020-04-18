//
// Created by lilyl on 4/18/2020.
//

#ifndef FINALPROJECT_GAME_H
#define FINALPROJECT_GAME_H

#include "table.h"
#include "ball.h"
#include "cue.h"

namespace myapp {
    class Game {
    public:
        void setup();
        void setTexture();
        void draw();
    private:
        Table table_;
        std::vector<Ball> balls_;
        Cue cue_;

    };
}
#endif //FINALPROJECT_GAME_H
