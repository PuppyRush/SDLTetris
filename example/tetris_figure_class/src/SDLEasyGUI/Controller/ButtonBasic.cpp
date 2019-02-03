//
// Created by chaed on 18. 12. 27.
//

#include "ButtonBasic.h"

SDL_TETRIS

ButtonBasic::ButtonBasic(const ControllBuilder& bld, const TControllKind kind)
    :Controll(bld,kind)
{


}

void ButtonBasic::draw()
{
    _drawCarot();
    Controll::draw();
}


void ButtonBasic::_drawCarot()
{
    auto renderer = getWindow()->getRenderer().get();

    if(isSelected() && isCarot())
    {
        if( GroupControllManager::getInstance()->isSelected(getGroup(), getId()))
        {
            SDL_Rect rect{getPoint().x-5, getPoint().y-5, getWidth()+10, getHeight()+10};

            const auto& linecolor = TColor::getColor(TColorCode::red);
            SDL_SetRenderDrawColor(renderer, linecolor.r, linecolor.g, linecolor.b, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}