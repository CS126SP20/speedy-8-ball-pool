//
// Created by lilyl on 4/17/2020.
//

#include "mylibrary/table.h"
#include <cinder/app/App.h>
#include <Box2D/Box2D.h>
#include <cinder/app/App.h>
#include <cinder/gl/gl.h>
#include "mylibrary/box2d_utility.h"

using namespace cinder;
namespace myapp {
    Wall::Wall(BodyRef body)
            : Body(body, nullptr, vec2(0, 0))
    {
        body_->SetUserData(this->body_.get());
    }
    void Wall::handleCollision( const BodyRef body, const ci::vec2 &contactPoint ) {

    }

    void Wall::draw() {
        float pointsPerMeter = Box2DUtility::getPointsPerMeter();
        auto pos = pointsPerMeter * body_->GetPosition();

        Rectf wallRect( pos.x - width_, 0, pos.x + width_, app::getWindowHeight() );
        gl::drawSolidRect( wallRect );

    }
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
