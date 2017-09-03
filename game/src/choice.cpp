#include "choice.hpp"

Choice::Choice(std::string objectName, double positionX, double positionY,
                                     int width, int height, std::string title, int size_title) : GameObject(object_name,
                                                                         position_x,
                                                                         position_y,
                                                                         width, height){

    button = new Button("assets/fonts/font.ttf", position_x + (width/2)*0.4, position_y + height, 200, 150, title, size_title);
    sprite = new Sprite(object_name);
    sprite->setDrawSize(200,150);
    padlock = new Sprite("assets/sprites/padlock.png");
    chosen = false;
    unlock = false;
    Color *color = new Color(0, 0, 0, 150);
    rectangle = new Rectangle("Rectangle", position_x, position_y, width, height, true, color);
}

Choice::~Choice(){}

void Choice::update(double time_elapsed){
    if(chosen && unlock){
        rectangle->setEnabled(false);
    }else{
        rectangle->setEnabled(true);
    }
    rectangle->update(time_elapsed);

}

void Choice::draw(){
    INFO("TEXT DRAW");
    sprite->draw(getPositionX(), getPositionY());
    if(!unlock){
        padlock->draw(getPositionX()+ (getWidth()/2)*0.8, getPositionY()+ (getHeight()/2)*0.8);
    }
    button->draw();
    rectangle->draw();
}

void Choice::setTextColor(Color * newTextColor){
    button->setTextColor(newTextColor);
}

void Choice::setBackgroundColor(Color * newBackgroundColor){
    button->setTextColor(newBackgroundColor);
}

Text * Choice::getText(){
    return button->getText();
}

void Choice::setChosen(bool isChosen){
  chosen = isChosen;
}

void Choice::setUnlock(bool isUnlock){
    unlock = isUnlock;
}

bool Choice::getUnlock(){
    return unlock;
}
