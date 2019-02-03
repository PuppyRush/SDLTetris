//
// Created by chaed on 18. 12. 27.
//

#ifndef CONTROLLER_BUTTONBASIC_H
#define CONTROLLER_BUTTONBASIC_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "Controll.h"

SDL_TETRIS_BEGIN

class ButtonBasic : public Controll{
public:

    inline const bool isMultiselected() const noexcept{
        Controll::isMultiselected();
    }
    inline void setMultiselected(bool multiselected) noexcept{
        Controll::setMultiselected(multiselected);
    }

    virtual void draw() override;

protected:
    ButtonBasic(const ControllBuilder& bld, const TControllKind kind);

private:
    void _drawCarot();
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TBUTTONBASIC_H