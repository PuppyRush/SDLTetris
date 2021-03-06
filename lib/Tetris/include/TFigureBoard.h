//
// Created by chaed on 18. 11. 24.
//

#ifndef TETRISMODULE_FIGUREBOARD_H
#define TETRISMODULE_FIGUREBOARD_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <array>
#include <memory>
#include <cassert>
#include <exception>
#include <random>
#include <algorithm>
#include <set>

#include "TFigureInterface.h"
#include "TProperty.h"

namespace tetris_module {

template<size_t WIDTH, size_t HEIGHT>
class TFigureBoard final
{

public:

    using figure_type = TFigureInterface;
    using figure_ptr = std::shared_ptr<figure_type>;
    using board_type = std::array<std::array<TFigureUnit, WIDTH>, HEIGHT>;

    TFigureBoard()
            : m_backgroundColor(seg::ColorCode::white)
    {
        clear();
    }

    ~TFigureBoard() = default;

    inline board_type getBoard() const noexcept
    {
        return m_board;
    }

    inline const seg::SEG_Point& getStartDisplayPoint() const
    {
        return m_startGameDisplayPoint;
    }

    inline void setStartDisplayPoint(const seg::SEG_Point& m_StartDisplayPoint)
    {
        TFigureBoard::m_startGameDisplayPoint = m_StartDisplayPoint;
    }

    inline const seg::t_size getblockLength() const
    {
        return m_gameblockLength;
    }

    inline void setblockLength(seg::t_size m_blockLength)
    {
        TFigureBoard::m_gameblockLength = m_blockLength;
    }

    void setGhostFigure(const figure_ptr& src, figure_ptr& dest)
    {
        dest = src->copy();
        dest->setAll(UnitType::Ghost);
        dest->setAll(seg::SEG_Color{seg::ColorCode::silver, 64});

        _eraseCoords(dest);

        std::shared_ptr<TFigureInterface> copied(nullptr);
        while (_isValidation(dest)) {
            copied = dest->move(SDLK_DOWN);
        }

        if (copied) {
            dest = copied;
            _setCoords(dest);
        }

        _setCoords(dest);
    }

    const bool _isValidation(figure_ptr destFigure) const
    {

        for (const auto& coord : destFigure->getCoords()) {
            if (isHit(coord)) {
                return false;
            }
        }

        return true;
    }

    void _eraseCoords(const figure_ptr& figure)
    {
        for (const auto& coord : figure->getCoords()) {
            const auto x = coord.getPoint().x;
            const auto y = coord.getPoint().y;
            UnitType unit = static_cast<UnitType>( m_board[y][x].getType() & (~coord.getType()) | UnitType::Empty );
            m_board[y][x].set(static_cast<UnitType>(unit));
        }
    }

    void _setCoords(const figure_ptr& figure)
    {
        for (const auto& coord : figure->getCoords()) {
            const auto x = coord.getPoint().x;
            const auto y = coord.getPoint().y;
            m_board[y][x].set(coord.getColor());

            int unit = m_board[y][x].getType() | coord.getType();
            unit &= ~UnitType::Empty;
            m_board[y][x].set(static_cast<UnitType>(unit));
        }
    }

    bool _eraseLinesIfFillLineThenCollapse()
    {
        std::set<seg::t_coord, std::greater<seg::t_coord>> collapedLines;
        for (seg::t_coord y = GAMEBOARD_HEIGHT_COUNT - 1; y >= 0; --y) {
            int x = 0;
            for (; x < GAMEBOARD_WIDTH_COUNT; ++x) {
                if ((m_board[y][x].getType() & UnitType::Fixed) != UnitType::Fixed) {
                    break;
                }
            }
            if (x == GAMEBOARD_WIDTH_COUNT) {
                collapedLines.insert(y);
                for (int x = 0; x < GAMEBOARD_WIDTH_COUNT; ++x) {
                    m_board[y][x].set(static_cast<UnitType>(UnitType::Empty));
                }
            }
        }

        if (collapedLines.empty()) {
            return false;
        }

        for (seg::t_coord x = 0; x < GAMEBOARD_WIDTH_COUNT; ++x) {
            for (seg::t_coord y = GAMEBOARD_HEIGHT_COUNT - 1; y >= 0; --y) {
                if ((m_board[y][x].getType() & UnitType::Fixed) == UnitType::Fixed) {
                    const size_t removedCnt = std::count_if(collapedLines.begin(), collapedLines.end(),
                                                            [y](const auto _y) {
                                                                return y < _y;
                                                            });

                    if (removedCnt > 0) {
                        m_board[y + removedCnt][x].set(UnitType::Fixed);
                        m_board[y + removedCnt][x].set(m_board[y][x].getColor());
                        m_board[y][x].set(static_cast<UnitType>(UnitType::Empty));
                        m_board[y][x].set(seg::ColorCode::none);
                    }
                }
            }
        }

        return true;
    }

    const bool isExterior(const TFigureUnit& unit) const noexcept
    {
        return unit.getPoint().x < 0 || unit.getPoint().x >= WIDTH ||
               unit.getPoint().y < 0 || unit.getPoint().y >= HEIGHT;
    }

    inline const bool isHit(const TFigureUnit& unit) const noexcept
    {
        if (!isExterior(unit)) {
            return (m_board[unit.getPoint().y][unit.getPoint().x].getType() & UnitType::Fixed) == UnitType::Fixed;
        } else {
            return true;
        }
    }

    void clear()
    {
        for (int i = 0; i < m_board.size(); i++) {
            auto board = m_board[i];
            for (int l = 0; l < board.size(); l++) {
                board[l] = TFigureUnit{seg::SEG_Point(i, l), 0, seg::ColorCode::none, UnitType::Empty};
            }
        }
    }

    inline seg::SEG_Color getBackgroundColor()
    { return m_backgroundColor; }

private:

    seg::SEG_Point m_startGameDisplayPoint;
    seg::t_size m_gameblockLength;
    seg::SEG_Color m_backgroundColor;

    board_type m_board;
};

}

#endif //TERIS_FIGURE_CLASS_FIGUREBOARD_H
