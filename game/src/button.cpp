/*
Objective: this class implements a button.
Author of the last update: lucas kishima dos santos.
Date:27/08/2017.
*/

#include "button.hpp"

Button::Button(std::string object_name, double position_x, double position_X, int width,
               int height, std::string title, int size_title) : GameObject(object_name, position_x,
                                                                           position_y, width,
                                                                           height) {
    text = new Text(title, object_name, size_title, true, new Color(0,0,0,0), new Color(0,0,0,0));
}

Button::~Button(){}

void Button::update(double time_elapsed){
    time_elapsed = time_elapsed;
    INFO(time_elapsed);

}

void Button::draw(){
    INFO("TEXT DRAW");
    text->draw(getPositionX(), getPositionY());
}

void Button::setTextColor(Color * newTextColor){
    text->setTextColor(newTextColor);
}

Text * Button::getText(){
    return text;
}
