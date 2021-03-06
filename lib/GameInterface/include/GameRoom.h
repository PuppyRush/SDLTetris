//
// Created by chaed on 19. 2. 8.
//

#ifndef GAMEINTERFACE_GAMEROOM_H
#define GAMEINTERFACE_GAMEROOM_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "Room.h"

namespace game_interface {

class GameRoom : public Room
{
public:
    using unique_type = Room::unique_type;
    using room_ptr = Room::room_ptr;

    virtual Json::Value toJson() const override;

    virtual void fromJson(const Json::Value& json);

    virtual void updateObserver(const packet::Packet&) = 0;

protected:

    explicit GameRoom() = default;

    virtual void postEnter(const player_ptr&) = 0;

    virtual void postExit(const player_ptr&) = 0;

};

}
#endif //SDL2EASYGUI_GAMEROOM_H
