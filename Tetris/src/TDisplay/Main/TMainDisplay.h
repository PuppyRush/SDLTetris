#ifndef TETRIS_CLIENT_TMAINDISPLAY_H
#define TETRIS_CLIENT_TMAINDISPLAY_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "TDisplayInterface.h"
#include "SDL2EasyGUI/include/SEG_Event.h"

SDL_TETRIS_BEGIN

class TMainDisplay : public TDisplayInterface
{
public:

    virtual ~TMainDisplay() = default;

    virtual void onClickedEnterServer(const void* click) = 0;

    virtual void onClickedStartLocalGame(const void* click) = 0;

    virtual void onClickedOption(const void* click) = 0;

    virtual void onClickedBack(const void* click) = 0;

protected:
    TMainDisplay();

    virtual void onInitialize()
    { TDisplayInterface::onInitialize(); }

    virtual void onDraw()
    { TDisplayInterface::onDraw(); }
};

SDL_TETRIS_END

#endif