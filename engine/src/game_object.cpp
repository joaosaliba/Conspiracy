/**
    @file game_object.cpp
    @brief It sets all game objects.
*/

//#define NDEBUG *uncomment to disable assertions
#include "game_object.hpp"
#include "log.h"
#include <assert.h>
#define HALF 2

using namespace engine;

/**
    @brief Game object constructor.
    @param[in] object_name name Key of the targeted object.
    @param[in] object_position_x it sets the x coordinate of the object.
    @param[in] object_position_y it sets the y coordinate of the object.
    @param[in] object_width it sets the width dimension of the object.
    @param[in] object_height it sets the height dimension of the object.
*/

GameObject::GameObject(std::string object_name, double object_position_x, double object_position_y, int object_width, int object_height) {
        assert(object_name != NULL);
        assert(object_position_x != NULL);
        assert(object_position_y != NULL);
        assert(object_width != NULL);
        assert(object_height != NULL);
        setName(object_name);
        setPositionX(object_position_x);
        setPositionY(object_position_y);
        setWidth(object_width);
        setHeight(object_height);
        setEnabled(true);
        setVisible(true);
}

/**
    @brief Game object constructor.
    @param[in] object_position_x it sets the x coordinate of the object.
    @param[in] object_position_y it sets the y coordinate of the object.
    @param[in] object_width it sets the width dimension of the object.
    @param[in] object_height it sets the height dimension of the object.
*/

GameObject::GameObject(double object_position_x, double object_position_y,int object_width, int object_height){
    assert(object_position_x != NULL);
    assert(object_position_y != NULL);
    assert(object_width != NULL);
    assert(object_height != NULL);
    setPositionX(object_position_x);
    setPositionY(object_position_y);
    setWidth(object_width);
    setHeight(object_height);
    setEnabled(true);
}

/**
    @brief Game object constructor.
*/

GameObject::GameObject(){}

/**
    @brief Game object destructor.
*/

GameObject::~GameObject(){}

//void GameObject::update(double timeElapsed){}

/**
    @brief Provides the object name.
    @return name name of the object.
*/

std::string GameObject::getName(){
    assert(object_name != NULL);
    return name;
}

/**
    @brief Provides the x coordinate of the object.
    @return position.first x coordinate value.
*/

double GameObject::getPositionX(){
    assert(object_position_x != NULL);
    return position.first;
}

/**
    @brief Provides the y coordinate of the object.
    @return position.second y coordinate value.
*/

double GameObject::getPositionY(){
    assert(object_position_y != NULL);
    return position.second;
}

/**
    @brief Provides the width dimension of the object.
    @return size.first width dimension value.
*/

int GameObject::getWidth(){
    assert(object_width != NULL);
    return size.first;
}

/**
    @brief Provides the height dimension of the object.
    @return size.second height dimension value.
*/

int GameObject::getHeight(){
    assert(object_height != NULL);
    return size.second;
}

/**
    @brief Provides a new name to game object.
    @param[in] newName the new name of the object.
*/

void GameObject::setName(std::string object_new_name){
    assert(object_new_name != NULL);
    name = object_new_name;
}

/**
    @brief Provides a new x coordinate of the object.
    @param[in] newX the new x coordinate of the object.
*/

void GameObject::setPositionX(double object_new_x){
    assert(object_new_x != NULL);
    position.first = object_new_x;
}

/**
    @brief Provides the coordinate pair of the center of the object.
    @return center coordinate pair of the center of the object.
*/

std::pair<double,double> GameObject::getCenter(){
    assert(position.first != NULL);
    assert(position.second != NULL);
    std::pair<double,double> center;
    center.first = (position.first + size.first/HALF);
    center.second = (position.second + size.second/HALF);
    return center;
}

/**
    @brief Provides a new y coordinate of the object.
    @param[in] newY the new y coordinate of the object.
*/

void GameObject::setPositionY(double object_new_y){
    assert(object_new_y != NULL);
    position.second = object_new_y;
}

/**
    @brief Provides a new width dimension of the object.
    @param[in] newWidth the new object width dimension.
*/

void GameObject::setWidth(int object_new_width){
    assert(object_new_width != NULL);
    size.first = object_new_width;
}

/**
    @brief Provides a new height dimension of the object.
    @param[in] newHeight the new object height dimension.
*/

void GameObject::setHeight(int object_new_height){
    assert(object_new_height != NULL);
    size.second = object_new_height;
}

/**
    @brief It enables the object.
    @param[in] paramEnabled object utilization status.
*/

void GameObject::setEnabled(bool param_enabled){
    assert(param_enabled != NULL);
    enabled = param_enabled;
}

/**
    @brief It makes the object visible.
    @param[in] paramVisible status of visibility of the object.
*/

void GameObject::setVisible(bool param_visible){
    assert(param_visible != NULL);
    visible = param_visible;
}

/**
    @brief It tells if the object is enable.
    @return enabled state of the object.
*/

bool GameObject::isEnabled(){
    return enabled;
}

/**
    @brief It tells if the object is visible.
    @return enabled state of visibility the object.
*/

bool GameObject::isVisible(){
    return visible;
}
