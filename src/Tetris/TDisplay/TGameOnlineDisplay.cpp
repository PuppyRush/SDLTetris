//
// Created by chaed on 19. 2. 6.
//

#include <jsoncpp/json/json.h>

#include "TGameOnlineDisplay.h"
#include "../../GameInterface/Event.h"
#include "../../SDLEasyGUI/Controller/Button.h"
#include "../TClient/JsonHelper.h"
#include "../TFiguers/TFigureBuilder.h"

SDL_TETRIS


Uint32 callback(Uint32 interval, void *param) {

    SDL_UserEvent userevent;
    userevent.type = TETRIS_EVENT_FIGURETIMER;
    userevent.code = 0;

    SDL_Event event;
    event.type = TETRIS_EVENT_FIGURETIMER;
    event.user = userevent;

    SDL_PushEvent(&event);
    return (interval);
}

TGameOnlineDisplay::TGameOnlineDisplay()
{
    m_display = TDisplay::Game;
    m_mode = TLocalMode::Online;
}

void TGameOnlineDisplay::onClickedStart()
{
    {
        auto ply = std::make_shared<TPlayer>();
        ply->startGame();
        m_players.emplace_back(ply);

        ply->connectServer();
        auto board = ply->getController()->getBoard();

        board->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X, GAMEBOARD_BEGIN_Y});
        board->setblockLength(FIGURE_UNIT_LEN);

        auto nextboard = ply->getController()->getNextFigureBoard();
        nextboard->setStartDisplayPoint(TPoint{GAMEBOARD_BEGIN_X + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
                                               GAMEBOARD_BEGIN_Y});
        nextboard->setblockLength(FIGURE_UNIT_LEN);
    }

    //
    {
        auto echoPly = std::make_shared<TPlayer>();
        echoPly->startGame();
        m_players.emplace_back(echoPly);

        auto board = echoPly->getController()->getBoard();

        const auto beginX = GAMEBOARD_BEGIN_X+600;
        board->setStartDisplayPoint(TPoint{beginX, GAMEBOARD_BEGIN_Y});
        board->setblockLength(FIGURE_UNIT_LEN);

        auto nextboard = echoPly->getController()->getNextFigureBoard();
        nextboard->setStartDisplayPoint(TPoint{beginX + GAMEBOARD_DISPLAY_WIDTH + FIGURE_UNIT_LEN,
                                               GAMEBOARD_BEGIN_Y});
        nextboard->setblockLength(FIGURE_UNIT_LEN);
    }

    m_drawLine = TOptionManager::getInstance()->isDrawLine();
    m_figureTimer = SDL_AddTimer(1000, callback, nullptr);
    m_gamestart = true;

    auto ctl = getControll(resource::GAME_START);
    ctl->setEnabled(false);
}

void TGameOnlineDisplay::onClickedSuspend()
{}

void TGameOnlineDisplay::onDraw()
{
    TGameDisplay::onDraw();
}

void TGameOnlineDisplay::onPreInitialize()
{


    t_size begin_y = WINDOW_HEIGHT/10*3;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "START");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_START))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y += 80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "SUSPEND");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_SUSPEND))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }
    begin_y += 80;
    {
        ControllBuilder bld(getWindow(), {WINDOW_WIDTH/10*4+50, begin_y}, "EXIT");
        bld.font({"../resources/fonts/OpenSans-Bold.ttf", 24, TColorCode::black})->
            id(toUType(resource::GAME_END))->
            background_color(TColorCode::white)->
            width(150)->
            height(50)->
            enabled(true);

        addControll(Button::getInstance(bld));
    }

    DisplayInterface::onPreInitialize();
}

void TGameOnlineDisplay::onClose()
{
    DisplayInterface::onClose();
}

void TGameOnlineDisplay::onCreate()
{
    DisplayInterface::onCreate();
}

void TGameOnlineDisplay::registerEvent()
{
    event_buttonClick(resource::GAME_START, std::bind(&TGameOnlineDisplay::onClickedStart, this));
}

void TGameOnlineDisplay::event(const SDL_Event *event)
{
    switch (event->type) {
        case RECV_DATA:
            if(m_players.size()==2) {

                Json::Value json;
                string strbuf((char *)event->user.data1);

                Json::Reader reader;
                reader.parse(strbuf, json);

                t_coord x{0}, y{0};
                int tclass;
                int  type;

                string id;
                string ip;
                string time;
                string board;
                JsonHelper::jsonRef(json,id,ip,time,board);
                JsonHelper::ref(board, tclass, type, x,y);

                TFigureBuilder bld({x,y});
                bld.figure(TFigureClass(tclass));
                bld.type(TFigureType(type));

                auto figure = bld.build();
                m_players.at(1)->getController()->forceSet(figure.get());
                refresh();
            }
            break;
        default:;
    }

    TGameDisplay::event(event);
}

void TGameOnlineDisplay::timer()
{

}