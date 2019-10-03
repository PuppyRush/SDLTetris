#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <atomic>
#include <unordered_map>

#include "TWindow.h"
#include "../Common/THeader.h"
#include "TControll/TControllBuilder.h"
#include "TControll/TControll.h"

SDL_TETRIS_BEGIN

class TDisplayInterface
{
public:
	//imple 'enum class' at child class.
    enum class UIResource : t_type;

    inline bool operator==(const TDisplayInterface* dp)
	{
		return this->m_display == dp->m_display;
	}

	void addMenu(const std::shared_ptr<TControll> ctl);
    bool clickedMenuEvent(const TPoint& point);

	void erase();
	void show();
	void hide();
	void setDisplay(const TDisplay dp);

	inline void setBackgroundImgPath(const std::string &path) { m_backgroundImgPath = path;}
	inline void setGoBack(const bool end) { m_goBack = end;}
	inline void setRun(const bool run) { m_run = run;}
	inline void setStopDraw(const bool set) { m_stopDraw = set;}

	inline const bool getGoBack() const noexcept{ return m_goBack;}
	inline const bool getRun() const noexcept{ return m_run;}
	inline const bool getSetDraw() const noexcept{ return m_stopDraw;}
	inline const TDisplay getDisplay() const noexcept{ return m_display;}

    virtual ~TDisplayInterface();
	virtual void _event(const SDL_Event* event);
	virtual bool clickedBack(const TDisplay disply) = 0;

protected:
	TDisplayInterface();
	void _refresh();

    inline std::shared_ptr<SDL_Window> getWindow() const noexcept
    {
        return m_window->getWindow();
    }

    inline std::shared_ptr<SDL_Renderer> getRenderer() const noexcept
    {
        return m_window->getRenderer();
    }

	virtual void _preInitialize() = 0;

private:

	void _initializing();
	void _drawMenus();
	void _drawCarot();
	void _release();

    inline std::shared_ptr<SDL_Event> getSDLEvent() const noexcept
    {  return m_window->getSDLEvent();  }

	virtual void _timer() =0;
	virtual void _draw() =0;

	std::vector<std::shared_ptr<TControll>> m_menus;
	std::string m_backgroundImgPath;
    std::shared_ptr<TWindow> m_window;

    bool m_stopDraw = false;
	bool m_goBack;
	bool m_canGoOtherDisplay;
	std::atomic_bool m_run = true;
	TDisplay m_display;
};

SDL_TETRIS_END