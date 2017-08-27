#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <string>
#include <utility>
#include "sprite.hpp"

namespace engine{
    class GameObject{
    public:
        GameObject(std::string object_name, double position_x, double position_y,int width, int height);
        GameObject(double position_x, double position_y,int width, int height);
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

        void setName(std::string new_name);
        void setPositionX(double new_position);
        void setPositionY(double new_position);
        void setWidth(int new_width);
        void setHeight(int new_height);
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
