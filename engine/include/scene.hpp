#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include "game_object.hpp"
#include "log.h"

namespace engine{

class Scene{
    public:
        Scene(int id);
        ~Scene(){}
        virtual void load();
        virtual void draw();
        virtual void update(double time_elapsed) = 0;
        virtual void unload();
        int get_id();
        void set_id(int id);
    protected:
        int scene_id;
    };
}
#endif
