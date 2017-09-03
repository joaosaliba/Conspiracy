#include "text.hpp"
#include "log.h"
#include "engine.hpp"
#include "text_manager.hpp"

using namespace engine;

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

void Text::shutdown(){
    INFO("Shutdown Text");

    SDL_DestroyTexture(texture);
    texture = NULL;

    font = NULL;

}

void Text::draw(int x, int y){
    SDL_Rect render_quad = {
        x,  y, width, height
    };

    SDL_RenderCopy(WindowManager::getGameCanvas(), texture, NULL, &render_quad);
}


void Text::setBackground(Color * newBackground){
    background = newBackground;
    init();
}

void Text::setTextColor(Color * newTextColor){
    textColor = newTextColor;
    init();
}
