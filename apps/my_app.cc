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
template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
    cinder::gl::color(color);

    auto box = TextBox()
            .alignment(TextBox::CENTER)
            .font(cinder::Font(kNormalFont, 30))
            .size(size)
            .color(color)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}
void MyApp::mouseDown( MouseEvent event )
{
    if (game_.GetState() == GameState::kReady) {
        game_.cue_->setPosition(event.getPos());
        tracking_mode = true;
    }
    if (game_.GetState() == GameState::kFoul) {
        game_.SetCueBall(event.getPos());
    }
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
    if (event.getCode() == KeyEvent::KEY_UP) {
        game_.cue_->IncreasePower();
    } else if (event.getCode() == KeyEvent::KEY_DOWN) {
        game_.cue_->DecreasePower();
    }
}

}  // namespace myapp
