#include "text.hpp"
#include "log.h"
#include "engine.hpp"
#include "text_manager.hpp"

using namespace engine;

Text::Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, Color *new_back_ground, Color *new_text_color) {
    text = newText;
    font_path = new_font_path;
    size = new_size;
    font = NULL;
    high_quality = is_high_quality;
    background = new_back_ground;
    text_color = new_text_color;
    init();
}

 void test_texture(){
	  if (font_path == "") {// valid if path is valid. 
        WARN("Invalid path for font!");
        exit(-1);
    }
 }	
 void test_surface(){
	 if(surface == NULL) {// testa se no caso de nao ser high_quality o metodo foi testado corretamente.
        exit(-1);
    }
 }
void test_texture(){
 if (texture == NULL) {// testa se a textura foi colocada corretamente
        exit(-1);
    }
	
}
void Text::init() {

    test_texture(); 
	

    if(texture != NULL) {
		SDL_DestroyTexture(texture);
	}

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);

   test_texture();	
	
   
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
   void test_surface()
	
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


void Text::setBackground(Color * new_back_ground) {
    background = new_back_ground;
    init();
}

void Text::setTextColor(Color * new_text_color) {
    text_color = new_text_color;
    init();
}
