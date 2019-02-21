#ifndef TETRIS_TMAIN_TMAINLOCALDISPLAY_H
#define TETRIS_TMAIN_TMAINLOCALDISPLAY_H


#if _MSC_VER >= 1200
  #pragma once
#endif

#include <vector>
#include <boost/serialization/singleton.hpp>

#include "TMainDisplay.h"

SDL_TETRIS_BEGIN

class TLocalMainDisplay final : public TMainDisplay
{
public:

	TLocalMainDisplay();
    ~TLocalMainDisplay(){}

private:

	[[deprecated("dont call this function in TLocalMainDisplay")]]
	virtual void onClickedEnterServer() {assert(0);};

	virtual void onClickedStartLocalGame() override final;
	virtual void onClickedOption() override final;
	virtual void registerEvent() override final;
	virtual void onPreInitialize() override final;
	virtual void onTimer() override final;
    virtual void onDraw() override final;

	virtual void updateObserver(const Observer&, const game_interface::Packet &) override final {}
};

SDL_TETRIS_END

#endif