#include "text.hpp"
#include "log.h"
#include "engine.hpp"
#include "text_manager.hpp"
/** text class responable for  rendering text in display */
using namespace engine;

/** construtor method of  text
 *@param text text itself
 *@paramfontpath  path for the font 
 * @param size  size of text 
 * @param high quality of text 
 * @param background background color. 
 * @param  text_color  color of the text 
 * @return text object
*/ 
Text::Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, Color *new_back_ground, Color *new_text_color){
    text = new_text;
    fontPath = new_font_path;
    size = new_size;
    font = NULL;
    high_1uality = is_high_quality;
    background = new_background;
    text_color = new_textColor;
    init();
}

/** set text texture 
*@param  text object wich store text informations  
*/

void Text::init(){

    if (fontPath == ""){
        WARN("Invalid path for font!");
        exit(-1);
    }

    font = TextManager::instance.loadFont(fontPath, size);

    SDL_Color color = {textColor->r, textColor->g, textColor->b, textColor->a};
    SDL_Color bg_color = {background->r, background->g, background->b, background->a};

    SDLSurface * surface = NULL;

    if (highQuality && bg_color.a == 0x00){
        surface = TTF_RenderText_Blended(
            font, text.c_str(), color
        );
    }
    else if (high_quality){
        surface = TTF_RenderText_Shaded(
            font, text.c_str(), color, bg_color
        );
    }
    else{
        surface = TTF_RenderText_Solid(
            font, text.c_str(), color
        );
    }

    if(surface == NULL){
        exit(-1);
    }

    if(texture != NULL){
		SDL_DestroyTexture(texture);
	}

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);

    if (texture == NULL){
        exit(-1);
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}

/** render the text 
* @param text object which store text infomration. 
* @param text object.
*/

void Text::shutdown(){
    INFO("Shutdown Text");

    SDL_DestroyTexture(texture);
    texture = NULL;

    font = NULL;

}
/** render text 
* @param x , y which is  the position in  x axis and y axis. 
*/
void Text::draw(int x, int y){
    SDL_Rect render_quad = {
        x,  y, width, height
    };

    SDL_RenderCopy(WindowManager::getGameCanvas(), texture, NULL, &render_quad);
}

/** set atibute background*/ 
void Text::setBackground(Color * newBackground){
    background = newBackground;
    init();
}
/** set textcolor  atribute 
* @param Newtextcolor whihc is the text color. 
*/
void Text::setTextColor(Color * newTextColor){
    textColor = newTextColor;
    init();
}
