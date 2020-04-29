// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/gl/draw.h>
#include <cinder/audio/Source.h>
#include <cinder/audio/Utilities.h>
#include <cinder/audio/audio.h>
#include "cinder/app/RendererGl.h"
#include "cinder/Log.h"
#include <cinder/Font.h>
#include <cinder/Text.h>

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
    game_.setup();
    //game_.setTexture();
}

void MyApp::update() {
    game_.update();
}

void MyApp::draw() {
    cinder::gl::clear();
    gl::enableAlphaBlending();
    game_.draw();

}
void MyApp::mouseDown( MouseEvent event )
{
    game_.cue_->setPosition(event.getPos());
    tracking_mode = true;
    //game_.CueRecoil();
   // game_.cue_->setPosition(event.getPos());
    //mScene.addGear( event.getPos() );
}

void MyApp::mouseDrag( MouseEvent event )
{
    if (!tracking_mode) {
        return;
    }
    game_.cue_->SetDirection(event.getPos());
}

void MyApp::mouseUp( MouseEvent event )
{
    if (tracking_mode)
        game_.CueHit();
    tracking_mode = false;
}

void MyApp::keyDown(KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_SPACE) {
        tracking_mode = false;
    }
}

}  // namespace myapp
