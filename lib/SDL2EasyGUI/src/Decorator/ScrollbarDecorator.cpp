//
// Created by chaed on 19. 7. 15.
//

#include "ScrollbarDecorator.h"
#include <include/SEG_Drawer.h>

using namespace seg;

ScrollbarDecorator::ScrollbarDecorator(BoxBasic* ctl)
        : Base(ctl),
          m_scrollWidth(14),
          m_scrollHeight(ctl->getHeight() / ctl->getVisibleMenuMax())
{

    m_scrollbarPosition = {Base::getPoint().x + Base::getWidth() - m_scrollWidth , Base::getPoint().y,
                           m_scrollWidth, Base::getHeight()};

    m_arrowSize = m_scrollbarPosition.h / 15;

    m_upperArrowPosition = {m_scrollbarPosition.x + m_arrowSize / 5, m_scrollbarPosition.y,
                            m_arrowSize, m_arrowSize};

    m_belowArrowPosition = {m_scrollbarPosition.x + m_arrowSize / 5,
                            m_scrollbarPosition.y + m_scrollbarPosition.h - m_arrowSize,
                            m_arrowSize, m_arrowSize};

}

bool ScrollbarDecorator::isHit(const SEG_Point& point) const
{
    return _hitTest(this->getPosition(), point) || Base::isHit(point);
}

void ScrollbarDecorator::onDraw()
{
    Base::onDraw();
    drawScroll();

}

void ScrollbarDecorator::onDrawBackground()
{
    Base::onDrawBackground();
}

void ScrollbarDecorator::drawScroll()
{
    using namespace draw_helper;

    draw_FilledRoundedRactangel(Base::getSDLRenderer(), ScrollbarDecorator::getPosition(), ColorCode::darkgray, 5);

    draw_FilledTriangle(Base::getSDLRenderer(),
                        {m_upperArrowPosition.x + m_upperArrowPosition.w / 2, m_upperArrowPosition.y},
                        {m_upperArrowPosition.x, m_upperArrowPosition.y + m_upperArrowPosition.h},
                        {m_upperArrowPosition.x + m_upperArrowPosition.w,
                         m_upperArrowPosition.y + m_upperArrowPosition.h}, ColorCode::black);
    draw_FilledTriangle(Base::getSDLRenderer(),
                        {m_belowArrowPosition.x + m_belowArrowPosition.w,
                         m_belowArrowPosition.y},
                        {m_belowArrowPosition.x, m_belowArrowPosition.y},
                        {m_belowArrowPosition.x + m_belowArrowPosition.w / 2,
                         m_belowArrowPosition.y + m_belowArrowPosition.h},
                        ColorCode::black);
}

void ScrollbarDecorator::onMouseMotionEvent(const SDL_MouseMotionEvent* motion)
{
    if (Base::_hitTest(ScrollbarDecorator::getPosition(), {motion->x, motion->y})) {
    } else {
        Base::onMouseMotionEvent(motion);
    }
};

void ScrollbarDecorator::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (Base::_hitTest(ScrollbarDecorator::getPosition(), {button->x, button->y})) {
        if (button->state == SDL_PRESSED && button->button == SDL_BUTTON_LEFT) {
            Base::setBackgroundColor(ColorCode::darkgray);
        }
        if (button->state == SDL_RELEASED) {
            Base::setBackgroundColor(ColorCode::lightgray);
        }
    } else {
        Base::onMouseButtonEvent(button);
    }
}