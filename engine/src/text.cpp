#include "text.hpp"
#include "log.h"
#include "engine.hpp"
#include "text_manager.hpp"
#include<string>
#include <assert.h>

using namespace engine;


    Text( std::string  newText, std::string new_font_path, int new_size, bool is_high_quality, std::string new_back_ground, std::string new_text_color) { 
    std::string text= newText;
    std::string font_path ;
    font_path= new_font_path;
    int size = new_size;
    TTF_Font *font = NULL;
    bool high_quality ;
    high_quality= is_high_quality;   
    std::string background = new_back_ground; 
    std::string text_color= new_text_color;
    init();
   }
void texture(){
	   if(texture != NULL) {
		SDL_DestroyTexture(texture);
	}

    texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), surface);

    if (texture == NULL) {
        exit(-1);
    }


}
 bool is_high_quality(){
 bool high_quality=true;
   if (high_quality && bg_color.a == 0x00) {
        surface = TTF_RenderText_Blended(
            font, c_str(), color
        );
    }
     	  
    else if (high_quality) {
        surface = TTF_RenderText_Shaded(
            font, c_str(), color, bg_color
        );
    }else{
       high_quality=false;
   }	    
 }     	    
 
void init(){
	
        	
	
    INFO("entrou no construtor");	
    if ( font_path == "") {// verifica se p caminho da ofnte e valido . 
        WARN("Invalid path for font!");
        exit(-1);
    }
	
	
    TTF_Font* font = TextManager::instance.loadFont( font_path,  size);

    SDL_Color color = {text_color->r, text_color->g, text_color->b, text_color->a};
    SDL_Color bg_color = {background->r, background->g, background->b, background->a};

    SDL_Surface * surface = NULL;

    (!is_high_quality()) {
        surface = TTF_RenderText_Solid(
            font,c_str(), color
       );
    }

    if(surface == NULL) {
        exit(-1);
    }

    texture();
    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
}


void shutdown() {
    INFO("Shutdown Text");

    SDL_DestroyTexture(texture);
    texture = NULL;

    font = NULL;

}

void draw(int x, int y) {
    INFO("entrou no metodo draw");	
    assert(x>0);
    assert(y>0);	
    SDL_Rect renderQuad = {
        x,  y, width, height
    };

    SDL_RenderCopy(WindowManager::getGameCanvas(), texture, NULL, &renderQuad);
}


void setBackground(std:: string new_back_ground) {
    INFO("entrou no metodo setBackground);
    background = new_back_ground;
    init();
}

void setTextColor(std::string new_text_color) {
    INFO(entoru no metodo setTextColor");	
    text_color = new_text_color;
    init();
}
