#include "sprite.hpp"
#include "engine.hpp"
#include "log.h"

using namespace engine;

    Sprite::Sprite(std::string newDirectory){
        directory = newDirectory;
        init();
    }

    void Sprite::init(){
        INFO("Init sprite.");
        SDL_Surface * image = NULL;// delcara imagem como vazia
        image = IMG_Load(directory.c_str());// carrega a imagem

        if(image == NULL){
            ERROR("INIT SPRITE ERROR.");
            exit(-1);
        }

        texture = SDL_CreateTextureFromSurface(WindowManager::getGameCanvas(), image);

        if(texture == NULL){
            ERROR("CREATE TEXTURE SPRITE ERROR.");
            exit(-1);
        }

        drawWidth = lenght.first = image->w;// seta a altura da primeira imagem
        drawHeight = lenght.second = image->h;// seta a latura da segunda imagem.
        SDL_FreeSurface(image);

    }

    void Sprite::shutdown(){
        INFO("Destroy sprite.");
        SDL_DestroyTexture(texture);
        texture = NULL;// termina o metodo detruindo a imagem
    }
    void Sprite::setDrawSize(int w, int h){
        drawWidth = w;// seta a largura
        drawHeight = h;// seta a altura.
    }
    void Sprite::draw(int x, int y){
        axis.first = x;// seta o eixo horizontal.
        axis.second = y;// seta o eixo vertical.
         //Crop image
        clipRect = {0, 0, lenght.first, lenght.second};

        // Rendering in screen
        renderQuad = {axis.first, axis.second, drawWidth, drawHeight };

        SDL_RenderCopy(WindowManager::getGameCanvas(), texture, &clipRect, &renderQuad);
}
