/**
    @file game_object.cpp
    @brief It sets all game objects.
*/

#include "game_object.hpp"
#include "log.h"

using namespace engine;

/**
    @brief Game object constructor.
    @param[in] objectName name Key of the targeted object.
    @param[in] positionX it sets the x coordinate of the object.
    @param[in] positionY it sets the y coordinate of the object.
    @param[in] width it sets the width dimension of the object.
    @param[in] height it sets the height dimension of the object.
*/

GameObject::GameObject(std::string objectName, double positionX, double positionY,
                                               int width, int height){
        setName(objectName);
        setPositionX(positionX);
        setPositionY(positionY);
        setWidth(width);
        setHeight(height);
        setEnabled(true);
        setVisible(true);
}

/**
    @brief Game object constructor.
    @param[in] positionX it sets the x coordinate of the object.
    @param[in] positionY it sets the y coordinate of the object.
    @param[in] width it sets the width dimension of the object.
    @param[in] height it sets the height dimension of the object.
*/

GameObject::GameObject(double positionX, double positionY,int width, int height){
    setPositionX(positionX);
    setPositionY(positionY);
    setWidth(width);
    setHeight(height);
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
    return name;
}

/**
    @brief Provides the x coordinate of the object.
    @return position.first x coordinate value.
*/

double GameObject::getPositionX(){
    return position.first;
}

/**
    @brief Provides the y coordinate of the object.
    @return position.second y coordinate value.
*/

double GameObject::getPositionY(){
    return position.second;
}

/**
    @brief Provides the width dimension of the object.
    @return size.first width dimension value.
*/

int GameObject::getWidth(){
    return size.first;
}

/**
    @brief Provides the height dimension of the object.
    @return size.second height dimension value.
*/

int GameObject::getHeight(){
    return size.second;
}

/**
    @brief Provides a new name to game object.
    @param[in] newName the new name of the object.
*/

void GameObject::setName(std::string newName){
    name = newName;
}

/**
    @brief Provides a new x coordinate of the object.
    @param[in] newX the new x coordinate of the object.
*/

void GameObject::setPositionX(double newX){
    position.first = newX;
}

/**
    @brief Provides the coordinate pair of the center of the object.
    @return center coordinate pair of the center of the object.
*/

std::pair<double,double> GameObject::getCenter(){
    std::pair<double,double> center;
    center.first = (position.first + size.first/2);
    center.second = (position.second + size.second/2);
    return center;
}

/**
    @brief Provides a new y coordinate of the object.
    @param[in] newY the new y coordinate of the object.
*/

void GameObject::setPositionY(double newY){
    position.second = newY;
}

/**
    @brief Provides a new width dimension of the object.
    @param[in] newWidth the new object width dimension.
*/

void GameObject::setWidth(int newWidth){
    size.first = newWidth;
}

/**
    @brief Provides a new height dimension of the object.
    @param[in] newHeight the new object height dimension.
*/

void GameObject::setHeight(int newHeight){
    size.second = newHeight;
}

/**
    @brief It enables the object.
    @param[in] paramEnabled object utilization status.
*/

void GameObject::setEnabled(bool paramEnabled){
    enabled = paramEnabled;
}

/**
    @brief It makes the object visible.
    @param[in] paramVisible status of visibility of the object.
*/

void GameObject::setVisible(bool paramVisible){
    visible = paramVisible;
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
