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
    struct Wall : Body {
        Wall(BodyRef body);
        void handleCollision(Ball *ball, const ci::vec2 &contactPoint ) override;
        void draw() override;
        float width_;
        enum class Side	{ LEFT, RIGHT, TOP, BOTTOM } mSide;
    };
    class Table {
    private:
        int mMin_ = 0;
        void SetPockets();
        /*
        Texture background;
        Rect r[6] {};  // Rect colliders for walls
        Ball b[12] {}; // Ball colliders to simulate pocket sides
        SDL_Point pocket_sensors[6] {}; // Check if ball in the pocket
        */
    public:
        std::vector<vec2> pockets_;

        cinder::gl::Texture2dRef texture_;
        //Table();
        void setTexture();
        void render();
        void draw();

        bool is_pocketed(std::shared_ptr<Ball> b);

        double  getWidth() const noexcept {return texture_->getWidth(); }
        double getHeight() const noexcept {return app::getWindowHeight();}
    };
}

#endif //FINALPROJECT_TABLE_H
