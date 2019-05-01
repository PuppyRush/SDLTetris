//
// Created by chaed on 19. 3. 13.
//

#ifndef PROJECT_TETRISWAITINGROOM_H
#define PROJECT_TETRISWAITINGROOM_H

#include <boost/serialization/singleton.hpp>
#include "GameInterface/include/WaitingRoom.h"
#include "TDefine.h"

SDL_TETRIS_BEGIN

class TWaitingRoom : public game_interface::WaitingRoom
{
public:
    TWaitingRoom() = default;

    virtual void initialize() override;

    virtual void destory() override;

protected:
    virtual void postEnter(const WaitingRoom::player_ptr&) override;

    virtual void postExit(const WaitingRoom::player_ptr&) override;

    virtual void postAddedGameRoom(room_ptr room) override;

    virtual void postRemovedGameRoom(const unique_type unique) override;

private:
    virtual Json::Value toJson() const override
    {}

    virtual const std::string_view& getUniqueName() const override
    { game_interface::NAME_WAITINGROOM; }

    virtual void updateObserver(const game_interface::Packet&) override;

};

SDL_TETRIS_END

#endif //PROJECT_TETRISWAITINGROOM_H