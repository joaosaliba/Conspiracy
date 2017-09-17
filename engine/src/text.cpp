#include "text.hpp"
#include "log.h"
#include "engine.hpp"
#include "text_manager.hpp"

using namespace engine;

Text::Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, Color *new_back_ground, Color *new_text_color){
    text = new_text;/** text itself*/
    fontPath = new_font_path;/** fontPath font path*/
    size = new_size;/** size of text */
    font = NULL;/** font to the  text*/ 
    high_1uality = is_high_quality;/** high_1uality quality level of the text*/
    background = new_background;/** background form the text*/
    text_color = new_textColor;/** text_color color which text we display*/
    init();
}


void Text::init(){

    if (fontPath == ""){/** fontPath font path,  exit if  which  doen't exist*/ 
        WARN("Invalid path for font!");
        exit(-1);
    }

    font = TextManager::instance.loadFont(fontPath, size);

    SDL_Color color = {textColor->r, textColor->g, textColor->b, textColor->a};
    SDL_Color bg_color = {background->r, background->g, background->b, background->a};

    SDLSurface * surface = NULL;
    /** if the text is in high quality and align render another else move to next clause */ 
    if (highQuality && bg_color.a == 0x00){ /** render the text since is in high quality and transparent */ 
        surface = TTF_RenderText_Blended(
            font, text.c_str(), color
        );
    }
    else if (high_quality){/** render the text since it's in high quality and isn't transparent   or move to another clause*/
        surface = TTF_RenderText_Shaded(
            font, text.c_str(), color, bg_color
        );
    }
    else{/** render the text solid since another clauses is false*/
        surface = TTF_RenderText_Solid(
            font, text.c_str(), color
        );
    }

    if(surface == NULL){/** if the text doen't have surface  exit the program*/
        exit(-1);
    }

    if(texture != NULL){ /**  destroy the texture to text since present or move to another clause*/
		SDL_DestroyTexture(texture);
	}

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);

    if (texture == NULL){ /** doesn't destroy since it's not needed*/
        exit(-1);
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}

void Text::shutdown(){
    INFO("Shutdown Text");

    SDL_DestroyTexture(texture);
    texture = NULL; /** text texture*/

    font = NULL; /** font to the  text*/ 

}

void Text::draw(int x, int y){
	 /** x text position in x axis, y position in y axis,  width and heigt to text which this names repesctively 
	 *width and heigh*/ 
    SDL_Rect render_quad = { x,y,width, heigh
    };

    SDL_RenderCopy(WindowManager::getGameCanvas(), texture, NULL, &render_quad);
}


void Text::setBackground(Color * newBackground){
    background = newBackground;/** background text background*/
    init();
}

void Text::setTextColor(Color * newTextColor){
    textColor = newTextColor;/** textcolor text color*/
    init();
}
