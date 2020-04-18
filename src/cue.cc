//
// Created by lilyl on 4/18/2020.
//

#include "mylibrary/cue.h"

using namespace cinder;

namespace myapp {
    void Cue::setTexture() {
        auto img = cinder::loadImage(cinder::app::loadAsset("cue.png"));
        texture_ = cinder::gl::Texture2d::create(img);
    }
    void Cue::draw() {
        cinder::Area area = texture_->getBounds();
        cinder::Area bound = app::getWindowBounds();
        cinder::Area fit = Area::proportionalFit(area, bound, true, false);
        cinder::gl::draw(texture_, fit);
    }
}