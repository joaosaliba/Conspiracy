#ifndef ENGINE_TEXT_HPP
#define ENGINE_TEXT_HPP

#include <iostream>
#include <string>

#include "sdl2includes.hpp"
#include "engine.hpp"
#include "color.hpp"

namespace engine{

    class Text{
    public:
        Text( std::string  newText, std::string newFont_path, int newSize, bool isHigh_quality, Color* newBackground, Color* new_text_color);
         ~Text(){}

        void init();
        void draw(int x, int y);
        void shutdown();
        void loadFont();
        void setBackground(Color * newBackground);
        void setTextColor(Color * new_text_color);
    protected:
        SDL_Texture * texture;
        TTF_Font * font;

        std::string text;
        std::string font_path;
        int size;
        bool high_quality;

        Color *background;
        Color *text_color;
        int width;
        int height;
    };
}

#endif
