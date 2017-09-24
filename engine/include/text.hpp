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
        Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, Color* new_back_ground, Color* new_text_color);
         ~Text(){}

        void init();
        void draw(int x, int y);
        void shutdown();
        void loadFont();
        void setBackground(Color * new_back_ground);
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
