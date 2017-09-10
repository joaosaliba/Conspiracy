#ifndef ENGINE_TEXT_HPP
#define ENGINE_TEXT_HPP

#include <iostream>
#include <string>

#include "sdl2includes.hpp"
#include "engine.hpp"
#include "color.hpp"
/** set text   aspects as zie, font, luanity
 *@param newtext, font_path, new_size, ishigh quality, new_back_ground, new_text_color*/ 
*/ 
namespace engine{
    /**  set the text 
    class Text{
    public:
        Text( std::string  newText, std::string newFontPath, int newSize, bool isHighQuality, Color* newBackground, Color* newTextColor);
         ~Text(){}

        void init();
        void draw(int x, int y);
        void shutdown();/** delete the text from display*/
        void loadFont();/** retrail the text font*/
        void setBackground(Color * newBackground);/** set the text background*/
        void setTextColor(Color * newTextColor);/** set the text color*/
    protected:
        SDL_Texture * texture; /** the text texture */ 
        TTF_Font * font;/** the text font*/

        std::string text; /** the text itself*/
        std::string fontPath;/**the font self*/
        int size;/** the text size*/
        bool highQuality;/** the text quality*/

        Color *background;/** the text background*/
        Color *textColor;/** the text color*/
        int width;/** the text width*/
        int height;/** the text high*/
    };
}

#endif

