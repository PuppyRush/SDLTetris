#ifndef TETRIS_TFIGUREBUILDER_H
#define TETRIS_TFIGUREBUILDER_H

#if _MSC_VER >= 1200
  #pragma once
#endif

#include "../Common/TType.h"
#include "TFigure.h"
#include "TFigureL.h"
#include "TFigureZ.h"
#include "TFigureI.h"
#include "TFigureT.h"
#include "TFigureO.h"

SDL_TETRIS_BEGIN

class TFigureBuilder final
{
public:

    TFigureBuilder(const Point &point);
    virtual ~TFigureBuilder() {}

    inline TFigureBuilder* color(const ColorCode& color)
    {
        this->m_color = color;
        return this;
    }


    inline TFigureBuilder* type(const TFigureType& type)
    {
        this->m_figureType = type;
        return this;
    }

    inline TFigureBuilder* age(const t_age& age)
    {
        this->m_age = age;
        return this;
    }

    inline TFigureBuilder *unitType(const UnitType& type)
    {
        this->m_unitType = type;
        return this;
    }

    inline TFigureBuilder *figure(const TFigureClass& figure)
    {
        this->m_figureClass = figure;
        return this;
    }

    inline const Point getPoint() const noexcept { return m_point; }
    inline const ColorCode getColor() const noexcept { return m_color; }
    inline const TFigureType getType() const noexcept { return m_figureType; }
    inline const t_age getAge() const noexcept { return m_age; }
    inline const t_size getHeight() const noexcept { return m_height; }
    inline const t_size getWidth() const noexcept { return m_width; }
    inline const UnitType getUnitType() const noexcept { return m_unitType; }
    inline constexpr const TFigureClass getClass() const noexcept { return m_figureClass; }

    std::shared_ptr<TFigure> build();

private:
    inline void width(const t_size width)
    { m_width = width;}

    inline void height(const t_size height)
    { m_height = height;}

    t_size m_width;
    t_size m_height;
    ColorCode m_color;
    Point m_point;
    TFigureType m_figureType;
    TFigureClass  m_figureClass = TFigureClass::End;
    t_age m_age;
    UnitType m_unitType;
    
};

SDL_TETRIS_END

#endif