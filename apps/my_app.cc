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

const char kNormalFont[] = "Arial";

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
    start_time_ = system_clock::now();
    //game_.setTexture();
}

void MyApp::update() {
    game_.update();
}

void MyApp::draw() {
    cinder::gl::clear();
    gl::enableAlphaBlending();
    game_.draw();
    DrawTime();
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
void MyApp::DrawTime() {
    const auto current_time = system_clock::now();
    auto ms = current_time - start_time_;

    using namespace std::chrono;
    auto secs = duration_cast<seconds>(ms);
    ms -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);

    const cinder::vec2 center = vec2(100, 100);
    const cinder::ivec2 size = {500, 50};
    const Color color = Color::white();
    std::string seconds = "";
    std::string minutes = "";
    if (mins.count() < 10) {
        minutes = "0" + std::to_string(mins.count());
    } else {
        minutes = std::to_string(mins.count());
    }
    if (secs.count() < 10) {
        seconds = "0" + std::to_string(secs.count());
    } else {
        seconds = std::to_string(secs.count());
    }
    PrintText(minutes + ":" + seconds, color, size, center);
}
void MyApp::mouseDown( MouseEvent event )
{
    if (game_.GetState() == GameState::kPlaying) {
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
