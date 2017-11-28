#include "sprite.hpp"
#include "engine.hpp"
#include "log.h"
#include <assert.h>
using namespace engine;

    Sprite::Sprite(std::string newDirectory){
        directory = newDirectory;
        init();
    }

    void Sprite::init(){
        INFO("Init sprite.");
        SDLSurface * image = NULL;
        image = IMG_Load(directory.c_str());

        
        
        if(image == NULL){// encera o metodo se a image for iqual a nulo. 
            ERROR("INIT SPRITE ERROR.");
            exit(-1);
        }

        
        
        texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), image);

        
        
        if(texture == NULL){// encera o metodo se nao houver uma textura. 
            ERROR("CREATE TEXTURE SPRITE ERROR.");
            exit(-1);
        }

        
        
        drawWidth = lenght.first = image->w;
        drawHeight = lenght.second = image->h;
        SDL_FreeSurface(image);

    }

    void Sprite::shutdown(){
        INFO("Destroy sprite.");
        SDL_DestroyTexture(texture);
        texture = NULL;
    }
    void Sprite::setDrawSize(int w, int h){
        drawWidth = w;
        drawHeight = h;
    }
    void Sprite::draw(int x, int y){// procurar o arquivo onde axis esta definido.
        INFO(" entrou no metodo draw da classe sprite");
        assert(x>0);
        DEBUG(" valor de x valido");
        assert(y>0); 
        DEBUG("valor de y valido");
        axis.horizontal = x;
        axis.vertical = y;
         //Crop image
        clipRect = {0, 0, lenght.first, lenght.second};

        // Rendering in screen
        renderQuad = {axis.horizontal, axis.vertical, drawWidth, drawHeight };

        SDL_RenderCopy(WindowManager::getGameCanvas(), texture, &clipRect, &renderQuad);
    }
