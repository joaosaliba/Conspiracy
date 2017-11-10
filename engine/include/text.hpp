#include <iostream>
#include <string>

#include "sdl2includes.hpp"
#include "engine.hpp"
#include "color.hpp"
/** set text   aspects as zie, font, luanity
 *@param newtext, font_path, new_size, ishigh quality, new_back_ground, new_text_color*/ 


using namespace  std;
 class Text{
        Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, std::string new_back_ground, std:: string new_text_color);            
        void init();
        void loadFont();/** retrail the text font*/
        void setBackground(Color * newBackground);/** set the text background*/
        void setTextColor(Color * newTextColor);/** set the text color*/
    protected:
        SDL_Texture * texture; /** the text texture */ 
        TTF_Font * font;/** the text font*/

        std::string text; /** the text itself*/
        std::string font_path;/**the font self*/
        int size;/** the text size*/
        bool highQuality;/** the text quality*/

        std::string background;/** the text background*/
        std::string textColor;/** the text color*/
        int width;/** the text width*/
        int height;/** the text high*/
};

#endif
