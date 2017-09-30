/**Class to create, destroy and
*manipulate the objects of the game.
*/

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <string>
#include <utility>
#include "sprite.hpp"

namespace engine {
    class game_object {
    public:
<<<<<<< HEAD
        game_object(std::string object_name, double position_x, 
        double position_y,int width, int height);
        game_object(double position_x, double position_y,int width, int height);
        game_object();
        ~game_object();
=======
        GameObject(std::string object_name, double object_position_x, double object_position_y, int object_width, int object_height);
        GameObject(double object_position_x, double object_position_y,int object_width, int object_height);
        GameObject();
        ~GameObject();
>>>>>>> origin/Development

        virtual void draw() = 0;
        virtual void update(double time_elapsed) = 0;

<<<<<<< HEAD
        std::string get_name();
        double get_position_x();
        double get_position_y();
        int get_width();
        int get_height();
        std::pair<double,double> get_center();
        bool is_enabled();
        bool is_visible();

        void set_name(std::string new_name);
        void set_position_x(double new_position);
        void set_position_y(double new_position);
        void set_width(int new_width);
        void set_height(int new_height);
        void set_enabled(bool param_enabled);
        void set_visible(bool param_visible);
=======
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
>>>>>>> origin/Development

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
