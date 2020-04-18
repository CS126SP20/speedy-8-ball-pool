//
// Created by lilyl on 4/18/2020.
//

#ifndef FINALPROJECT_CUE_H
#define FINALPROJECT_CUE_H

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

namespace myapp {
    class Cue {
    public:
        void setTexture();
        void render();
        void draw();
    private:
        cinder::gl::Texture2dRef texture_;

    };
}
#endif //FINALPROJECT_CUE_H
