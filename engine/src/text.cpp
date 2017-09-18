#include "text.hpp"
#include "log.h"
#include "engine.hpp"
#include "text_manager.hpp"

using namespace engine;

Text::Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, Color *newBackground, Color *new_text_color) {
    text = newText;
    font_path = new_font_path;
    size = new_size;
    font = NULL;
    high_quality = is_high_quality;
    background = newBackground;
    text_color = new_text_color;
    init();
}


void Text::init() {

    if (font_path == "") {
        WARN("Invalid path for font!");
        exit(-1);
    }

    font = TextManager::instance.loadFont(font_path, size);

    SDL_Color color = {text_color->r, text_color->g, text_color->b, text_color->a};
    SDL_Color bg_color = {background->r, background->g, background->b, background->a};

    SDL_Surface * surface = NULL;

    if (high_quality && bg_color.a == 0x00) {
        surface = TTF_RenderText_Blended(
            font, text.c_str(), color
        );
    }
    else if (high_quality) {
        surface = TTF_RenderText_Shaded(
            font, text.c_str(), color, bg_color
        );
    }
    else {
        surface = TTF_RenderText_Solid(
            font, text.c_str(), color
        );
    }

    if(surface == NULL) {
        exit(-1);
    }

    if(texture != NULL) {
		SDL_DestroyTexture(texture);
	}

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);

    if (texture == NULL) {
        exit(-1);
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}

void Text::shutdown() {
    INFO("Shutdown Text");

    SDL_DestroyTexture(texture);
    texture = NULL;

    font = NULL;

}

void Text::draw(int x, int y) {
    SDL_Rect renderQuad = {
        x,  y, width, height
    };

    SDL_RenderCopy(WindowManager::getGameCanvas(), texture, NULL, &renderQuad);
}


void Text::setBackground(Color * newBackground) {
    background = newBackground;
    init();
}

void Text::setTextColor(Color * new_text_color) {
    text_color = new_text_color;
    init();
}
