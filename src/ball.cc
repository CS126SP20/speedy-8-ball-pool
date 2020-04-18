//
// Created by lilyl on 4/17/2020.
//

#include "mylibrary/ball.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>

using namespace cinder;

namespace myapp {
    Ball::Ball(int id) {
        this->id = id;
    }
    void Ball::setTexture(const std::string &path) {
        auto img = cinder::loadImage(cinder::app::loadAsset(path));
        texture_ = cinder::gl::Texture2d::create(img);
        cinder::Area area = texture_->getBounds();
        texture_->setCleanBounds(area);
    }
    void Ball::draw() {
        cinder::gl::enableAlphaBlending();
        ivec2 imgSize(texture_->getWidth(), texture_->getHeight());
        ivec2 centerImage( ( app::getWindowWidth() - imgSize.x)/2, (app::getWindowHeight() - imgSize.y)/2);
        ivec2 center(300, 300);
        gl::clear(ColorAf( 0.0f, 0.0f, 0.0f, 0.0f ));
        gl::draw(texture_, center);
        cinder::gl::enableAlphaBlending();
    }
}