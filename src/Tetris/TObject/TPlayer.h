//
// Created by chaed on 19. 1. 13.
//

#ifndef TETRIS_FIGURE_CLASS_TPLAYER_H
#define TETRIS_FIGURE_CLASS_TPLAYER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include <cassert>

#include "GameInterface/Online/Packet.h"
#include "GameInterface/Object/Player.h"
#include "Tetris/Common/TDefine.h"
#include "Tetris/TClient/TClientController.h"
#include "Tetris/TFiguers/TFigureController.h"
#include "Tetris/TObject/TScore.h"

SDL_TETRIS_BEGIN

class TPlayer final : public game_interface::Player
{
public:

    TPlayer();
    virtual ~TPlayer();

    inline const bool isReady() const noexcept { return m_isReady; }
    inline const int getOrder() const noexcept { return m_order; }
    inline const bool isSurvive() const noexcept { return m_isSurvive; }

    inline const std::shared_ptr<TFigureController> getController() const noexcept {
        assert(m_gameCtl && m_gameCtl.get());
        return m_gameCtl;
    }

    inline void setOrder(const int idx) noexcept { m_order = idx; }
    inline void setReady(const bool rdy) noexcept { m_isReady = rdy; }

    void command(const t_eventType event);
    void sendPacket(game_interface::Packet &);
    void startGame();
    void endGame();
    void connectServer();

    virtual void updateObserver(const Observer&, const game_interface::Packet &) override;

    static std::shared_ptr<TPlayer> getPlayer()
    {
        static auto player = std::make_shared<TPlayer>();
        return player;
    }


private:
    int m_order;
    bool m_isReady;
    bool m_isSurvive;
    game_interface::TIPString m_ip;
    TScore m_score;

    std::shared_ptr<TFigureController> m_gameCtl;
    TClientController m_clientCtl;
};

SDL_TETRIS_END

#endif //TETRIS_FIGURE_CLASS_TPLAYER_H
