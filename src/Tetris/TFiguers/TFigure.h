#ifndef TERIS_FIGURE_CLASS_TFIGURE_H
#define TERIS_FIGURE_CLASS_TFIGURE_H

#if _MSC_VER >= 1200
  #pragma once
#endif


#include <cassert>
#include <memory>
#include <deque>
#include <numeric>
#include <array>

#include "Tetris/Common/TDefine.h"
#include "../Common/TType.h"
#include "../../GameInterface/TypeTraits.h"
#include "TFigureUnit.h"

SDL_TETRIS_BEGIN


/***********************************************
*		            □ □ □ □                    *
*		            □ □ ■ □                    *
*		            □ □ □ □                    *
*		            □ □ □ □                    *
*	   	      Relatevie Coordnation		       *
*	(x-2,y-1) (x-1,y-1) (x,y-1)	 (x+1,y-1)     *
*	(x-2,y  ) (x-1,y  ) (x,y  )	 (x+1,y  )     *
*	(x-2,y+1) (x-1,y+1) (x,y+1)	 (x+1,y+1)     *
*	(x-2,y+2) (x-1,y+2) (x,y+2)	 (x+1,y+2)     *
***********************************************/

class TFigureBuilder;
class TFigure{
public:

    using FigureCoords = std::array<TFigureUnit, 4>;
    
    virtual ~TFigure();
    
    inline const TFigureType getType()
    { return m_figureType;}

    inline const TFigureClass getClass()
    { return m_figureClass;}

    inline const size_t getWidth()
    { return m_width;}
    
    inline const size_t getHeight()
    { return m_height;}

    inline const TColor getColor()
    { return m_color;}

    inline const TPoint getPoint()
    { return m_point;}

    inline void setPoint(const TPoint& point)
    { _resetRelateivePoint(point); m_point = point; }

    inline FigureCoords& getCoords()
    { return m_relativeCoord;}

    std::shared_ptr<TFigure> goRight();
    std::shared_ptr<TFigure> goLeft();
    std::shared_ptr<TFigure> goDown();
    std::shared_ptr<TFigure> rotateLeft();
    std::shared_ptr<TFigure> rotateRight();

    TFigureUnit getLeftmost();
    TFigureUnit getRightmost();
    TFigureUnit getUpmost();
    TFigureUnit getDownmost();

    void copy(const TFigure& fig);
    const std::shared_ptr<TFigure> copy() const;
    virtual const TFigureType getRandomlyFigureType() const;

    template <class T>
    inline void setAll(const T& type)
    {
        for(auto& unit : m_relativeCoord)
            unit.set(type);
    }

    template <class T>
    inline void setAll(T&& type)
    {
        for(auto& unit : m_relativeCoord)
            unit.set(type);
    }

    virtual void initialize() = 0;
    virtual const TFigureType getTypeBegin() const = 0;
    virtual const TFigureType getTypeEnd() const = 0;

protected:
    TFigure(const TFigureBuilder *bld);
    TFigure();

    t_size m_figureTypeCount;
    t_size m_width;
    t_size m_height;
    TPoint m_point;
    TColor m_color;
    TFigureClass  m_figureClass;
    TFigureType m_figureType;
    FigureCoords m_relativeCoord;
    
private:

    virtual void _goRight();
    virtual void _goLeft();
    virtual void _goDown();
    virtual const std::shared_ptr<TFigure> _copy() const = 0;
    virtual bool _validation() = 0;
    virtual void _rotateLeft() = 0;
    virtual void _rotateRight() = 0;
    void _resetRelateivePoint(const TPoint& exPt);
};

SDL_TETRIS_END

#endif