#include "TFigureL.h"
#include "Common/TypeTraits.h"

using namespace tetris;

TFigureL::TFigureL(const TFigureBuilder *bld)
    : TFigure(bld)
{
    _rotateLeft();
}

TFigureL::~TFigureL() {
}

void TFigureL::initialize() {
    m_figureTypeCount = toUType(getTypeEnd()) - toUType(getTypeBegin());
}

void TFigureL::_rotateLeft() {

    m_relativeCoord[0].set({m_point.x, m_point.y});

    switch (m_figureType) {
        case TFigureType::A:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_point.x, m_point.y + 1});
            m_relativeCoord[2].set({m_point.x, m_point.y - 1});
            m_relativeCoord[3].set({m_point.x + 1, m_point.y + 1});
            m_figureType = TFigureType::B;
            break;
        case TFigureType::B:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_point.x - 1, m_point.y});
            m_relativeCoord[2].set({m_point.x + 1, m_point.y - 1});
            m_relativeCoord[3].set({m_point.x + 1, m_point.y});
            m_figureType = TFigureType::C;
            break;
        case TFigureType::C:
            m_width = 2;
            m_height = 3;
            m_relativeCoord[1].set({m_point.x - 1, m_point.y - 1});
            m_relativeCoord[2].set({m_point.x, m_point.y + 1});
            m_relativeCoord[3].set({m_point.x, m_point.y - 1});
            m_figureType = TFigureType::D;
            break;
        case TFigureType::D:
            m_width = 3;
            m_height = 2;
            m_relativeCoord[1].set({m_point.x - 1, m_point.y + 1});
            m_relativeCoord[2].set({m_point.x + 1, m_point.y});
            m_relativeCoord[3].set({m_point.x - 1, m_point.y});
            m_figureType = TFigureType::A;
            break;
        default:
            assert(0);
    }
}

void TFigureL::_rotateRight() {

}

bool TFigureL::_validation() {

}

const TFigureType TFigureL::getTypeBegin() const {
    return TFigureType::A;
}

const TFigureType TFigureL::getTypeEnd() const {
    return TFigureType::D;
}

const std::shared_ptr<TFigure> TFigureL::_copy() const {
    return std::shared_ptr<TFigureL>(new TFigureL());
}