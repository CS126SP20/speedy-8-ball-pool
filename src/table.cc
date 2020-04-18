//
// Created by lilyl on 4/17/2020.
//

#include "mylibrary/table.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>

using namespace cinder;
namespace myapp {

    void Table::setTexture() {
        auto img = cinder::loadImage(cinder::app::loadAsset("table.png"));
        texture_ = cinder::gl::Texture2d::create(img);
    }

    void Table::draw() {
        cinder::Area area = texture_->getBounds();
        cinder::Area bound = app::getWindowBounds();
        cinder::Area fit = Area::proportionalFit(area, bound, true, false);
        cinder::gl::draw(texture_, fit);
    }
}
