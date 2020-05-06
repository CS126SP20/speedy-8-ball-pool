// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/audio/Source.h>
#include "cinder/Log.h"
#include <cinder/params/Params.h>



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
const char kNormalFont[] = "Arial";
using cinder::app::KeyEvent;
using namespace cinder;
using namespace ci;
using namespace ci::app;
const char kDbPath[] = "pool.db";

MyApp::MyApp()
    : scoreboard_{cinder::app::getAssetPath(kDbPath).string()},
      printed_game_over_{false}
    {}

void MyApp::setup() {
    game_.Setup();
    mPrintFps = false;
    // create parameters
    mParams = params::InterfaceGl::create( getWindow(), "Welcome To 8 Ball Pool!", toPixels( ivec2( 400, 100 ) ) );
    vec2 center = app::getWindowCenter();
    mParams->setPosition(ivec2(center.x - ((float)mParams->getWidth() / 2), 50));
    // add parameter username
    mParams->addParam( "Enter Username:", &player_name_);
    mParams->addSeparator();
    // add button to start game
    mParams->addButton( "Click to start game", std::bind( &MyApp::button, this ) );

}
void MyApp::button()
{
    // if start button is clicked, change game state to playing and start timer
    game_.SetGameState(GameState::kPlaying);
    mParams->clear();
    start_time_ = system_clock::now();
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
    const cinder::vec2 locp = {loc.x - (float)box_size.x / 2, loc.y - (float)box_size.y / 2};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}
std::string MyApp::ConvertTime(size_t ms) {
    using namespace std::chrono;

    unsigned int secs = ms / 1000;
    ms %= 1000;
    unsigned int mins = secs / 60;
    secs %= 60;

    std::string seconds;
    std::string minutes;
    if (mins < 10) {
        minutes = "0" + std::to_string(mins);
    } else {
        minutes = std::to_string(mins);
    }
    if (secs < 10) {
        seconds = "0" + std::to_string(secs);
    } else {
        seconds = std::to_string(secs);
    }
    return minutes + ":" + seconds;
}
size_t MyApp::GetScore() {

    using namespace std::chrono;
    const auto current_time = system_clock::now();
    auto ms = current_time - start_time_;
    size_t duration  = duration_cast<milliseconds>(ms).count();
    return duration;
}
void MyApp::update() {
    if (game_.GetState() == GameState::kLogin) {
        if(mPrintFps && getElapsedFrames() % 60 == 0 )
            console() << getAverageFps() << std::endl;
    }
    else if (game_.GetState() == GameState::kPlaying || game_.GetState() == GameState::kFoul) {
        game_.Update();
    }
    else if (game_.GetState() == GameState::kGameOver) {
        if (top_players_.empty()) {
            if (game_.GameOver()) {
                scoreboard_.AddScoreToScoreBoard({player_name_, GetScore()});
            }
            top_players_ = scoreboard_.RetrieveHighScores(kLimit);
            Player player(player_name_, GetScore());
            top_scores_ = scoreboard_.RetrieveHighScores(player, kLimit);
            // It is crucial the this vector be populated, given that `kLimit` > 0.
            assert(!top_players_.empty());
        }
        return;
    }

}

void MyApp::DrawGameOver() {
    // Lazily print.
    if (printed_game_over_) return;
    if (top_players_.empty()) return;

    const cinder::vec2 center = getWindowCenter();
    const cinder::ivec2 size = {500, 50};
    const Color color = Color::white();

    float row = 1;
    PrintText("Game Over :(", color, size, center);
    PrintText("All Player Top Scores", color, size, {center.x, center.y + 50});
    for (const myapp::Player& player : top_players_) {
        std::stringstream ss;
        ss << player.name << " - " << ConvertTime(player.score);
        PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
    }
    PrintText("Current Player Top Scores", color, size, {center.x, 100});
    row = 0;
    for (const myapp::Player& player : top_scores_) {
        std::stringstream ss2;
        ss2 << player.name << " - " << ConvertTime(player.score);
        PrintText(ss2.str(), color, size, {center.x, 100 + (++row) * 50});
    }
    printed_game_over_ = true;
}

void MyApp::draw() {
    if (game_.GetState() == GameState::kLogin) {
        auto img = cinder::loadImage(cinder::app::loadAsset("background.png"));
        gl::TextureRef texture = cinder::gl::Texture2d::create(img);
        gl::draw(texture, vec2(0, 0));
        mParams->draw();
    }
    else if (game_.GetState() == GameState::kPlaying || game_.GetState() == GameState::kFoul ) {
        cinder::gl::clear();
        gl::enableAlphaBlending();
        game_.Draw();
        const cinder::vec2 center = vec2(100, 100);
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::white();
        PrintText(ConvertTime(GetScore()), color, size, center);

    } else if (game_.GetState() == GameState::kGameOver) {
        if (!printed_game_over_) cinder::gl::clear(Color(0, 0, 0));
        DrawGameOver();
    }

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
}

void MyApp::mouseDrag( MouseEvent event )
{
    if (!tracking_mode) {
        return;
    }
    // set direction of cue based on mouse position
    game_.cue_->SetDirection(event.getPos());
}

void MyApp::mouseUp( MouseEvent event )
{
    if (tracking_mode)
        game_.CueHit();
    tracking_mode = false;
}

void MyApp::keyDown(KeyEvent event) {
    if (event.getCode() == KeyEvent::KEY_ESCAPE)
        game_.SetGameState(GameState::kGameOver);
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
