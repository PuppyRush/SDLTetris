#ifndef TETRIS_TMAIN_TMAINLOCALDISPLAY_H
#define TETRIS_TMAIN_TMAINLOCALDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TMainLocalDisplay final : public TMainDisplay
{
public:

	TMainLocalDisplay();
    ~TMainLocalDisplay(){}

private:

	virtual void onClickedStartLocalGame() final;
	virtual void registerEvent() override final;
	virtual void onPreInitialize() final;
	virtual void event(const SDL_Event *event) final;
	virtual void timer() final;
    virtual void onDraw() final;
};

SDL_TETRIS_END

#endif