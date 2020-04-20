//
// Created by lilyl on 4/17/2020.
//

#ifndef FINALPROJECT_TABLE_H
#define FINALPROJECT_TABLE_H
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
using namespace cinder;
namespace myapp {
    class Table {
        int posX, posY;
        /*
        Texture background;
        Rect r[6] {};  // Rect colliders for walls
        Ball b[12] {}; // Ball colliders to simulate pocket sides
        SDL_Point pocket_sensors[6] {}; // Check if ball in the pocket
        */
    public:

        cinder::gl::Texture2dRef texture_;
        //Table(CollisionObserver* c = nullptr);
        void setTexture();
        void render();
        void draw();
        //bool is_pocketed(const Ball& b);

        double  getWidth() const noexcept {return app::getWindowWidth(); }
        double getHeight() const noexcept {return app::getWindowHeight();}
        int         getX() const noexcept {return posX;}
        int         getY() const noexcept {return posY;}
    };
}

#endif //FINALPROJECT_TABLE_H
