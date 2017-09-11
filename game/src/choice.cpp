#include "choice.hpp"

Choice::Choice(std::string object_name, double position_x, double position_y, int width, int height,
               std::string title, int size_title) : GameObject(object_name,
                                                              position_x,
                                                              position_y,
                                                              width, height) {

    button = new Button("assets/fonts/font.ttf", position_x + (width/2)*0.4,
                        position_y + height, 200, 150, title, size_title);

    sprite = new Sprite(object_name);
    sprite->setDrawSize(200,150);

    padlock = new Sprite("assets/sprites/padlock.png");

    chosen = false;
    unlock = false;

    Color *color = new Color(0, 0, 0, 150);
    rectangle = new Rectangle("Rectangle", position_x, position_y, width, height, true, color);
}

Choice::~Choice(){}

void Choice::update(double time_elapsed) {
    if(chosen && unlock) {
        rectangle->setEnabled(false);
    }else {
        rectangle->setEnabled(true);
    }
    rectangle->update(time_elapsed);

}

void Choice::draw() {
    INFO("TEXT DRAW");
    sprite->draw(getPositionX(), getPositionY());

    if(!unlock) {
        padlock->draw(getPositionX()+ (getWidth()/2)*0.8, getPositionY()+ (getHeight()/2)*0.8);
    }

    button->draw();
    rectangle->draw();
}

void Choice::setTextColor(Color * new_text_color) {
    button->setTextColor(new_text_color);
}

void Choice::setBackgroundColor(Color * new_background_color) {
    button->setTextColor(new_background_color);
}

Text * Choice::getText() {
    return button->getText();
}

void Choice::setChosen(bool is_chosen) {
  chosen = is_chosen;
}

void Choice::setUnlock(bool is_unlock) {
    unlock = is_unlock;
}

bool Choice::getUnlock() {
    return unlock;
}
