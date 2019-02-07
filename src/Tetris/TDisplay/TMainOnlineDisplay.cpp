//
// Created by chaed on 18. 12. 18.
//

#include "TMainOnlineDisplay.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "SDLEasyGUI/Windows/DisplayController.h"
#include "Tetris/Common/Resource.h"
#include "TGameOnlineDisplay.h"

SDL_TETRIS

TMainOnlineDisplay::TMainOnlineDisplay()
{
    m_mode = TLocalMode::Online;
}

void TMainOnlineDisplay::registerEvent()
{

}


void TMainOnlineDisplay::onPreInitialize() {

    t_size begin_y = WINDOW_HEIGHT/3;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH / 2 - 120, begin_y}, "PLAY TOGETHER");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            background_color(TColorCode::white)->
            id(toUType(resource::MAIN_MULTI_GAME_START_BUTTON))->
            width(240)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/2-50, begin_y}, "OPTION");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::MAIN_OPTION_BUTTON))->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y+=80;
    {
        ControllBuilder bld(getWindow(),{WINDOW_WIDTH/2-50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::MAIN_EXIT))->
            background_color(TColorCode::white)->
            width(100)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    ::DisplayInterface::onPreInitialize();

}


void TMainOnlineDisplay::timer()
{

}

void TMainOnlineDisplay::onDraw()
{

}
void TMainOnlineDisplay::event(const SDL_Event *event)
{

}

void TMainOnlineDisplay::onClickedEnterServer()
{
    DisplayController::getInstance()->modal(make_shared<TGameOnlineDisplay>());
}