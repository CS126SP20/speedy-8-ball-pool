//
// Created by lilyl on 4/17/2020.
//

#ifndef FINALPROJECT_TABLE_H
#define FINALPROJECT_TABLE_H
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "body.h"
#include "ball.h"

using namespace cinder;
namespace myapp {
    /**
     * Wall struct that simulates the borders of the table
     */
    struct Wall : Body {
        Wall(BodyRef body);
        void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
        void draw() override;
        float width_;
    };

    /**
     * Table class
     */
    class Table : Body {

        public:
            Table(BodyRef body, cinder::gl::TextureRef texture_, vec2 pos);
            void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
            // sets the positions of the pockets on table
            void SetPockets();
            //Table();
            void draw() override;
            // checks if a ball has been pocketed
            bool is_pocketed(std::shared_ptr<Ball> b);
            std::vector<vec2> GetPockets() {return pockets_;}
            // for testing purposes
            void TestPockets(std::vector<vec2> pockets) {pockets_ = pockets;}
        private:
            std::vector<vec2> pockets_;
    };
}

#endif //FINALPROJECT_TABLE_H
