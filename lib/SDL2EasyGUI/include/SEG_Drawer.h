//
// Created by chaed on 19. 7. 4.
//

#ifndef SDL2_TETRIS_CLIENT_SEG_DRAWER_H
#define SDL2_TETRIS_CLIENT_SEG_DRAWER_H

#if _MSC_VER >= 1200
#pragma once
#endif

#include "SDL2/SDL2_gfxPrimitives.h"
#include "SEG_Struct.h"
//#include <sdl

namespace seg::drawer {

static void draw_Triangle(SDL_Renderer* renderer, const SEG_Point& p1, const SEG_Point& p2, const SEG_Point& p3,
                          const SEG_Color& color)
{
    trigonRGBA(renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a);
}

static void
draw_FilledTriangle(SDL_Renderer* renderer, const SEG_Point& p1, const SEG_Point& p2, const SEG_Point& p3,
                    const SEG_Color& color)
{
    filledTrigonRGBA(renderer, p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, color.r, color.g, color.b, color.a);
}

static void draw_RoundedRactangel(SDL_Renderer* renderer, const SDL_Rect& rect, const SEG_Color& color, int16_t rad,
                                  t_size thick = 1)
{
    auto copied{rect};
    for (t_size t = 0; t < thick; t++) {
        copied.x += t;
        copied.y += t;
        copied.h -= (t + 1);
        copied.w -= (t + 1);
        roundedRectangleRGBA(renderer, copied.x, copied.y, copied.x + copied.w, copied.y + copied.h, rad, color.r,
                             color.g, color.b,
                             color.a);
    }
}

static void
draw_FilledRoundedRactangel(SDL_Renderer* renderer, const SDL_Rect& rect, const SEG_Color& color, int16_t rad)
{
    roundedBoxRGBA(renderer, rect.x, rect.y, rect.x + rect.w, rect.y + rect.h, rad, color.r, color.g, color.b,
                   color.a);
}

static void
drawThickLine(SDL_Renderer* renderer, const SEG_Point p1, const SEG_Point p2, const SEG_Color& color,
              const size_t thick = 1)
{
    thickLineRGBA(renderer, p1.x, p1.y, p2.x, p2.y, thick, color.r, color.g, color.b, color.a);
}

static void
drawCircle(SDL_Renderer* renderer, const SEG_Point& midPoint, const SEG_Color& color, const size_t thick = 1)
{
    filledCircleRGBA(renderer, midPoint.x, midPoint.y, thick, color.r, color.g, color.b, color.a);
}

static void drawX(SDL_Renderer* renderer, const SDL_Rect& rect, const SEG_Color& color, const size_t thick = 1)
{
    SDL_Point line1[2]{{rect.x,          rect.y},
                       {rect.x + rect.w, rect.y + rect.h}};
    SDL_Point line2[2]{{rect.x + rect.w, rect.y},
                       {rect.x,          rect.y + rect.h}};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line1[0].x, line1[0].y, line1[1].x, line1[1].y, thick,
                  color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line2[0].x, line2[0].y, line2[1].x, line2[1].y, thick,
                  color.r, color.g, color.b, color.a);

}

static void drawV(SDL_Renderer* renderer, const SDL_Rect& rect, const SEG_Color& color, const size_t thick = 1)
{
    SDL_Point line1[2]{{rect.x + rect.w / 4,   rect.y + rect.h / 6},
                       {rect.x + (rect.w / 2), rect.y + rect.h - rect.h / 5}};
    SDL_Point line2[2]{{rect.x + (rect.w / 2), rect.y + rect.h - rect.h / 5},
                       {rect.x + rect.w,       rect.y}};

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line1[0].x, line1[0].y, line1[1].x, line1[1].y, thick,
                  color.r, color.g, color.b, color.a);

    thickLineRGBA(renderer, line2[0].x, line2[0].y, line2[1].x, line2[1].y, thick,
                  color.r, color.g, color.b, color.a);

}

using color_type = std::underlying_type_t<ColorCode>;

static SDL_Color getColor(const ColorCode colorCode)
{
    SEG_Color col(colorCode);
    SDL_Color color{col.r, col.g, col.b, 255};
    return color;
}

static SDL_Color getTransparent()
{
    SEG_Color col(ColorCode::white);
    SDL_Color color{col.r, col.g, col.b, 0};
    return color;
}

static ColorCode getInvertedColor(const ColorCode colodeCode)
{
    return ColorCode((static_cast<color_type>(colodeCode)) ^ 0xffffff);
}

static ColorCode getInvertedColor(const SEG_Color& color)
{
    return getInvertedColor(color.colorCode);
}

class TextDrawer
{

public:

    TextDrawer(SDL_Renderer* renderer, const SEG_TFont& fontinfo, const SEG_Point& point, const std::string& str)
            : m_textSurface(nullptr), m_point(point), m_renderer(renderer)
    {
        TTF_Font* font = TTF_OpenFont(fontinfo.font_name.c_str(), fontinfo.size);
        SDL_Color textColor = {fontinfo.color.r, fontinfo.color.g, fontinfo.color.b, fontinfo.color.a};

        m_textSurface = TTF_RenderUTF8_Solid(font, str.c_str(), textColor);
        if(m_textSurface != nullptr)
        {
            m_texture = SDL_CreateTextureFromSurface(renderer, m_textSurface);
            m_width = m_textSurface->w;
            m_height = m_textSurface->h;
        }
    }

    ~TextDrawer()
    {
        //SDL_FreeSurface(m_textSurface);
    }

    void drawText()
    {
        if (m_texture != nullptr) {
            //SDL_UnlockSurface(m_textSurface);
            //SDL_Rect clipedQuad =
            //    { 0,0, m_width, m_height };
            //SDL_SetClipRect(m_textSurface, &clipedQuad);
            //SDL_LockSurface(m_textSurface);

            //m_texture = SDL_CreateTextureFromSurface(m_renderer, m_textSurface);

            SDL_Rect renderQuad = { static_cast<int>(m_point.x), static_cast<int>(m_point.y), m_width, m_height };
            SDL_Rect originRect = { static_cast<int>(m_point.x), static_cast<int>(m_point.y),  m_textSurface->w, m_textSurface->h};

            //SDL_Texture* myTexturePart = GetAreaTextrue(renderQuad, m_renderer, m_texture);

            SDL_RenderCopy(m_renderer, m_texture, NULL, &originRect);
        }

    }

    inline int getTextWidth()
    {
        return m_textSurface ?
               static_cast<double>(m_textSurface->w) : 0;
    }

    inline int getTextHeight()
    {
        return m_textSurface ?
               static_cast<double>(m_textSurface->h) : 0;
    }

    inline void setTextWidth(const t_size w)
    {
        m_width = w;
    }

    inline void setTextHeight(const t_size h)
    {
        m_height = h;
    }

    inline void setPoint(const SEG_Point& point)
    { m_point = point; }

private:

    SDL_Surface* m_textSurface = nullptr;
    SDL_Texture* m_texture = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SEG_Point m_point = { INVALID_COORD, INVALID_COORD };
    int m_height = 0;
    int m_width = 0;
};

}

#endif //SDL2_TETRIS_CLIENT_SEG_DRAWER_H
