#include "button.hpp"

Button::Button(std::string objectName, double position_x, double position_y,
                                     int width, int height, std::string title, int sizeTitle) : GameObject(objectName,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){

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

void Button::setTextColor(Color * new_text_color){
    text->setTextColor(new_text_color);
}

Text * Button::getText(){
    return text;
}
