//
// Created by chaed on 18. 12. 15.
//


#include <iostream>
#include <random>
#include <functional>

#include "Tetris/Common/TResource.h"
#include "SDLEasyGUI/SEG_Event.h"
#include "SDLEasyGUI/Controller/Button.h"
#include "TSingleGameDisplay.h"
#include "TOption/TOptionManager.h"

SDL_TETRIS
using namespace game_interface;

TSingleGameDisplay::TSingleGameDisplay()
{
    m_display = toUType(TDisplay::Game);
    m_mode = TLocalMode::Local;
}


void TSingleGameDisplay::onClickedStart()
{
    auto ply = TPlayer::getPlayer();
    ply->startGame();
    m_players.emplace_back(ply);

    auto board = ply->getController()->getBoard();

    m_drawLine = TOptionManager::getInstance()->isDrawLine();

    board->setStartDisplayPoint(Point{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
    board->setblockLength(FIGURE_UNIT_LEN);

    auto nextboard = ply->getController()->getNextFigureBoard();
    nextboard->setStartDisplayPoint(Point{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN, GAMEBOARD_BEGIN_Y});
    nextboard->setblockLength(FIGURE_UNIT_LEN);

    TimerAdder tAdder(1000,toUType(TetrisEvent::TETRIS_EVENT_FIGURETIMER));
    m_figureTimer = tAdder.addTimer();

    m_gamestart = true;

    auto ctl = getControll(resource::GAME_START);
    ctl->setEnabled(false);
}

void TSingleGameDisplay::onClickedSuspend()
{

}

void TSingleGameDisplay::registerEvent() {

    event_buttonClick(toUType(resource::GAME_START), std::bind(&TSingleGameDisplay::onClickedStart, this));
}

void TSingleGameDisplay::onPreInitialize()
{


    t_size begin_y = WINDOW_HEIGHT/10*3;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::GAME_START))->
            backgroundColor(ColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::GAME_SUSPEND))->
            backgroundColor(ColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }
    begin_y += 80;
    {
        ButtonBuilder bld(getWindow(), {WINDOW_WIDTH/5*3, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::black})->
            id(toUType(resource::GAME_END))->
            backgroundColor(ColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(bld.build());
    }

    DisplayInterface::onPreInitialize();
}

void TSingleGameDisplay::onClose()
{

    TGameDisplay::onClose();
}

void TSingleGameDisplay::onCreate()
{

    TGameDisplay::onCreate();
}


void TSingleGameDisplay::onTimer()
{

}

void TSingleGameDisplay::onDraw() {
    TGameDisplay::onDraw();
}