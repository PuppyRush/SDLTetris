//
// Created by chaed on 19. 4. 27.
//

#include "CheckBox.h"
#include "SEG_Drawer.h"

using namespace seg;

CheckBox::CheckBox(CheckBoxBuilder& bld)
        : ButtonBasic(bld), m_lineThick(bld.m_lineThick), m_type(bld.m_type)
{
    bld.kind(ControlKind::CheckBox);
}

void CheckBox::onDraw()
{
    _drawCheck(isSelected());
    ButtonBasic::onDraw();
}

void CheckBox::onDrawBackground()
{

    ButtonBasic::onDrawBackground();
}

void CheckBox::onMouseButtonEvent(const SDL_MouseButtonEvent* button)
{
    if (button->button == SDL_BUTTON_LEFT  && button->state == SDL_PRESSED && isHit(button->x, button->y)) {
        setSelected(!isSelected());
    }
}

void CheckBox::_drawCheck(const bool chk)
{
    switch(m_type)
    {
    case CheckBoxType::vType:
        if (chk) {
            drawer::drawV(getSDLRenderer(), getPosition(), m_lineColor, m_lineThick);
        } else {
            drawer::drawV(getSDLRenderer(), getPosition(), getBackgroundColor(), 0);
        }
        break;
    case CheckBoxType::oType:

        break;
    case CheckBoxType::xType:
        if (chk) {
            drawer::drawX(getSDLRenderer(), getPosition(), m_lineColor, m_lineThick);
        } else {
            drawer::drawX(getSDLRenderer(), getPosition(), getBackgroundColor(), m_lineThick);
        }
        break;
    }


}