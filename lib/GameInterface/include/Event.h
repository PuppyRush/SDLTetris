//
// Created by chaed on 19. 2. 8.
//

#ifndef GAMEINTERFACE_EVENT_H
#define GAMEINTERFACE_EVENT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <SDL2/SDL_events.h>

namespace game_interface {

enum GAMEINTERFACE_EVENT
{
    RECV_DATA = SDL_USEREVENT + 1,
    GAMEINTERFACE_EVENT_END
};

}

#endif //TETRIS_FIGURE_CLASS_EVENT_H
