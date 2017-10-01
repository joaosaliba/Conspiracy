/**Class to create, destroy and
*manipulate the objects of the game.
*/

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <string>
#include <utility>
#include "sprite.hpp"

namespace engine{
    class GameObject{
    public:
        GameObject(std::string object_name, double object_position_x, double object_position_y, int object_width, int object_height);
        GameObject(double object_position_x, double object_position_y,int object_width, int object_height);
        GameObject();
        ~GameObject();

        virtual void draw() = 0;
        virtual void update(double time_elapsed) = 0;

        std::string getName();
        double getPositionX();
        double getPositionY();
        int getWidth();
        int getHeight();
        std::pair<double,double> getCenter();
        bool isEnabled();
        bool isVisible();

        void setName(std::string object_new_name);
        void setPositionX(double object_new_position);
        void setPositionY(double object_new_position);
        void setWidth(int object_new_width);
        void setHeight(int object_new_height);
        void setEnabled(bool param_enabled);
        void setVisible(bool param_visible);

    private:
        std::string name;

        bool enabled;

        bool visible;
        // X position and Y position in pixels
        std::pair <double, double> position;

        // Width and Height in pixels
        std::pair <int, int> size;

    };
}

#endif
