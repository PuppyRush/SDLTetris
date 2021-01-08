//
// Created by chaed on 18. 12. 22.
//

#ifndef SDLEASYGUIDE_TSTRUCT_H
#define SDLEASYGUIDE_TSTRUCT_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include <cassert>
#include <string>
#include <functional>
#include <iostream>

#include <SDL2/SDL_image.h>

#include "SEG_Constant.h"
#include "SEG_Property.h"

namespace seg {

typedef struct DisplayInfo
{
    t_display display;
    TLocalMode mode;
    TDisplayMode displayMode;
    t_id id;

} DisplayInfo;

typedef struct SEG_Color
{
public:

    ColorCode colorCode;
    using coldeType = decltype(colorCode);

    t_color r;
    t_color g;
    t_color b;
    t_color a;

    SEG_Color()
    {}

    SEG_Color(const ColorCode code, const t_color alhpa = 255)
            : colorCode(code), a(alhpa)
    {
        const auto c = std::underlying_type_t<coldeType>(code);
        r = (c >> 16) & 0x0000FF;
        g = (c >> 8) & 0x0000FF;
        b = c & 0x0000FF;
    }

    SEG_Color(const t_color r, const t_color g, const t_color b, const t_color alhpa)
            : r(r), g(g), b(b), a(alhpa)
    {

        std::underlying_type<coldeType>::type c{ 0 };
        c += r << 16;
        c += g << 8;
        c += b;
        colorCode = coldeType{c};
    }

    bool operator==(const SEG_Color& color)
    {
        return
                this->r == color.r
                && this->g == color.g
                && this->b == color.b;
    }

    const bool compare(const SEG_Color& rhs) const
    {
        return this->colorCode == rhs.colorCode;
    }


} SEG_Color;

typedef struct SEG_Point
{
public:
    t_coord x;
    t_coord y;
    t_coord z;

    SEG_Point()
            : x(0), y(0), z(0)
    {}

    SEG_Point(const t_coord x, const t_coord y, const t_coord z = 0)
            : x(x), y(y), z(z)
    {}

} SEG_Point;

typedef struct SEG_TFont
{
    std::string font_name;
    t_size size;
    SEG_Color color;

    SEG_TFont() = default;

    SEG_TFont(const std::string& str, const t_size size, const ColorCode color)
            : font_name(str), size(size), color(color)
    {}
} TFont;

//pre declearcation
class SEG_Window;

typedef struct ControlBasic
{
    SEG_Window* window;

    //컨트롤의 고유 ID
    t_id resourceId;
    SEG_Point point = SEG_Point{ INVALID_COORD, INVALID_COORD };
    SEG_Point midPoint = SEG_Point{0, 0};
    SDL_Rect positionRect = SDL_Rect{0, 0};
    t_size depth = 0;
    t_size width = 100;
    t_size height = 50;
    SEG_TFont font = {"../resources/fonts/OpenSans-Bold.ttf", 24, ColorCode::white};
    SEG_Color backgroundColor = ColorCode::black;
    std::string name = "";
    t_display display = std::numeric_limits<t_display>::max();
    bool enabled = true;
    bool multiselected = false;
    ControlKind kind = ControlKind::StaticLabel;
    int group = -1;
    bool carot = false;
    bool autoSize = true;
    bool selected = false;

    //border types
    BorderBoundaryLineType borderLineType = BorderBoundaryLineType::straight;
    BorderBoundaryType borderType = BorderBoundaryType::roundedAngle;
    SEG_Color borderColor = ColorCode::white;
    int borderAngle = 0;
    int borderThick = 1;

    ControlBasic() = default;

    ControlBasic(const ControlBasic& b)
            : resourceId(b.resourceId),
              window(b.window),
              point(b.point),
              width(b.width),
              height(b.height),
              font(b.font),
              backgroundColor(b.backgroundColor),
              name(b.name),
              display(b.display),
              enabled(b.enabled),
              multiselected(b.multiselected),
              kind(b.kind),
              group(b.group),
              carot(b.carot),
              autoSize(b.autoSize),
              selected(b.selected),
              depth(b.depth),
              borderLineType(b.borderLineType),
              borderType(b.borderType),
              borderAngle(b.borderAngle),
              borderThick(b.borderThick),
              borderColor(b.borderColor)
    {}

} TControlBasic;

}

#endif //TETRIS_FIGURE_CLASS_TSTRUCT_H
