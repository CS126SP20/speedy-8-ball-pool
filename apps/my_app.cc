// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/audio/Source.h>
#include <cinder/audio/Utilities.h>
#include <cinder/audio/audio.h>
#include "cinder/app/RendererGl.h"
#include "cinder/Log.h"

namespace myapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;
using std::string;

using cinder::app::KeyEvent;
using namespace cinder;

MyApp::MyApp() {}

void MyApp::setup() {
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
    auto img = cinder::loadImage( cinder::app::loadAsset("table.png") );
    texture_ = cinder::gl::Texture2d::create( img );
}

void MyApp::update() { }

void MyApp::draw() {
    cinder::gl::clear();
    cinder::Area area = texture_->getBounds();
    cinder::Area bound = getWindowBounds();
    cinder::Area fit = Area::proportionalFit(area, bound, true, false);
    cinder::gl::draw(texture_, fit);
}

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
