#include "guard.hpp"
#define ZERO_ANGLE 0
#define PLANE_ANGLE 180
#define STRAIGHT_ANGLE 90
#define REVERSE_STRAIGHT_ANGLE 270
#define MAKE_SECONDS 100.0

Guard::Guard(std::string objectName, double position_x, double position_y,
             int width, int height, std::string initialDirection,int newQuantityRepeatWay, double newWaitingTime) : Enemy(objectName,
                                                                          position_x,
                                                                          position_y,
                                                                          width, height){

        animator = new Animation(objectName, 1, 10, 0.5);
        exclamation = new Animation("assets/sprites/exclamation.png",1, 1, 0.5);

        animator->add_action("right",6,9);
        animator->add_action("left",1,4);
        animator->add_action("up",6,9);
        animator->add_action("down",1,4);
        animator->add_action("idle_right",5,5);
        animator->add_action("idle_left",0,0);
        animator->add_action("idle_up",5,5);
        animator->add_action("idle_down",0,0);



        quantityRepeatWay = newQuantityRepeatWay;
        currentRepeat = 0;

        int angleOfVision = 60;
        range = 150;
        fieldOfVision = new FieldOfVision(position_x+width/2,position_y-7, range, angleOfVision);
        talkingBar = new ProgressBar(position_x, position_y, 45, 5, 0.0025);

        std::vector<unsigned int> backColor = {255, 0, 0, 255};
        std::vector<unsigned int> frontColor = {0, 0, 0, 255};
        detectionBar = new ProgressBar(position_x, position_y, 30, 5, 0.01, backColor, frontColor);

        idle_animation_number = 0;
        waitingTime = newWaitingTime;
        wayActive = false;
        talking = false;
        wayActual = 1;
        direction = initialDirection;
        lastDirection = initialDirection;

        timerHorizontal = new Timer();
        timerVertical = new Timer();

        timerHorizontal->start();
        timerVertical->start();
}

Guard::~Guard(){
}

void Guard::update(double time_elapsed){
        auto inc_y = 0.1*time_elapsed;
        auto inc_x = 0.1*time_elapsed;

        // To Do: Use Time Elapsed in angleOfVision.
        if(talking) {
                wayActive = false;
                inc_x = 0.0;
                inc_y = 0.0;
        }else{
                if(wayActive) {
                        inc_y = 0.15*time_elapsed;
                        inc_x = 0.15*time_elapsed;
                }else{
                        stop(inc_x, inc_y);
                }

                walk_in_x(inc_x);
                walk_in_y(inc_y);
                fieldOfVision->updateCenter(inc_x,inc_y);
        }
        if(inc_x == 0.0 && inc_y == 0.0) {
                if(idle_animation_number) {
                        animator->set_interval("idle_right");
                }else{
                        animator->set_interval("idle_left");
                }
        }

        if(talking){
                talkingBar->update(time_elapsed);
        }
        if(detecting){
            detectionBar->update(time_elapsed);
            if(detectionBar->getPercent() <= 0.0){
                detecting = false;
                wayActive = true;
            }
        }

        animator->update();
        exclamation->update();
        selectLine();
}

void Guard::walk_in_x(double & inc_x){


        if(wayActive) {
                walk_in_xSpecial(inc_x);
        }else{
                if(direction == "right") {
                        inc_x = inc_x * (1);
                        idle_animation_number = 5;
                        animator->set_interval(direction);
                }else if(direction == "left") {
                        inc_x = inc_x * (-1);
                        idle_animation_number = 0;
                        animator->set_interval(direction);
                }else {
                        inc_x = 0;
                }
        }

        setposition_x(get_position_x()+inc_x);
        int beforeWay = wayActual;
        if(CollisionManager::instance.verify_collisionWithWallsAndChairs(this)) {
                if (!wayActive) {
                        verifyDeadLockHorizontal();

                        if(direction == "left") {
                                direction = "right";
                        }else if(direction == "right"){
                                direction = "left";
                        }
                }

                setposition_x(get_position_x()+(inc_x*(0-1)));
                inc_x = 0;
                if (beforeWay == wayActual){
                    nextWay();
                }
        }
}

void Guard::walk_in_y(double & inc_y){


        if(wayActive) {
                walk_in_ySpecial(inc_y);
        }else{
                if(direction == "down") {
                        inc_y = inc_y * (1);
                        idle_animation_number = 5;
                        animator->set_interval(direction);
                }else if(direction == "up") {
                        inc_y = inc_y * (-1);
                        idle_animation_number = 0;
                        animator->set_interval(direction);
                }else {
                        inc_y = 0;
                }
        }

        setposition_y(get_position_y()+inc_y);
        int beforeWay = wayActual;
        if(CollisionManager::instance.verify_collisionWithWallsAndChairs(this)) {
                if (!wayActive) {
                        verifyDeadLockVertical();

                        if(direction == "down") {
                                direction = "up";
                        }else if(direction == "up"){
                                direction = "down";
                        }
                }

                setposition_y(get_position_y()+(inc_y*(0-1)));
                inc_y = 0;

                if (beforeWay == wayActual){
                    nextWay();
                }
        }
}

void Guard::walk_in_xSpecial(double & inc_x){
        if(ways[wayActual].first == "right") {
                inc_x = inc_x * (1);
                idle_animation_number = 5;
                animator->set_interval("right");
                direction = "right";
                if(get_position_x()+inc_x > ways[wayActual].second) {
                        inc_x = 0.0;
                        nextWay();
                }
        }else if(ways[wayActual].first == "left") {
                inc_x = inc_x * (-1);
                idle_animation_number = 0;
                animator->set_interval("left");
                direction = "left";
                if(get_position_x()+inc_x < ways[wayActual].second) {
                        inc_x = 0.0;
                        nextWay();
                }
        }else {
                inc_x = 0;
        }
}

void Guard::walk_in_ySpecial(double & inc_y){
        if(ways[wayActual].first == "down") {
                inc_y = inc_y * (1);
                idle_animation_number = 5;
                animator->set_interval("down");
                direction = "down";
                if(get_position_y()+inc_y > ways[wayActual].second) {
                        inc_y = 0.0;
                        nextWay();
                }
        }else if(ways[wayActual].first == "up") {
                inc_y = inc_y * (-1);
                idle_animation_number = 0;
                animator->set_interval("up");
                direction = "up";
                if(get_position_y()+inc_y < ways[wayActual].second) {
                        inc_y = 0.0;
                        nextWay();
                }
        }else {
                inc_y = 0;
        }
}

void Guard::draw(){
        animator->draw(get_position_x()-10, get_position_y()-10);
        animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());

        if(detecting) {
            detectionBar->setposition_x(get_position_x() - 10);
            detectionBar->setposition_y(get_position_y() - 20);
            AnimationManager::instance.addProgressBar(detectionBar);
        }
        if(wayActive){
            exclamation->draw(get_position_x(), get_position_y()-30);
        }
        if(talking) {
                AnimationManager::instance.addProgressBar(talkingBar);
                if(talkingBar->getPercent() <= 0.0) {
                        notTalkingToETemer();
                }
        }
        AnimationManager::instance.addGuardVision(fieldOfVision);
        //fieldOfVision->draw();
}

void Guard::addWay(int key, std::pair<std::string, int> way){
        ways[key] = way;
}

void Guard::verify_distance(GameObject* alien){
        double distance = sqrt((pow(get_position_x() - alien->get_position_x(), 2.0)) +  (pow(get_position_y() - alien->get_position_y(), 2.0)));
// TODO Definir quando irá iniciar o percurso especial do guarda
    //std::cout << alien->getName() << std::endl;
    if(alien->getName().compare("assets/sprites/varginha_sheet.png") == 0){
        //std::cout << "AQUI" << std::endl;
        if(distance < 150 && alien->isVisible() && !wayActive){
            detecting = true;
        }else{
            detectionBar->resetPercent();
            detecting = false;
        }
    }else if(distance < 150){
        wayActive = true;
    }
}

void Guard::selectLine(){
        std::string action = animator->getCurrentAction();
        if(lastDirection != action) {
                lastDirection = action;
                if(action == "right" || action == "idle_right") {
                        fieldOfVision->setAngle(ZERO_ANGLE);//00
                }else if(action == "left" || action == "idle_left") {
                  fieldOfVision->setAngle(PLANE_ANGLE); //180
                }else if(action == "up") {
                        fieldOfVision->setAngle(STRAIGHT_ANGLE); //90
                }else if(action == "down") {
                        fieldOfVision->setAngle(REVERSE_STRAIGHT_ANGLE);//270
                }
              }
}
int Guard::getRange(){
        return range;
}
FieldOfVision* Guard::getFieldOfVision(){
        return fieldOfVision;
}

void Guard::talkingToETemer(std::string status){
        talking = true;
        if(status == "right") {
                idle_animation_number = 5;
        }else{
                idle_animation_number = 0;
        }
        talkingBar->resetPercent();
        talkingBar->setposition_x(get_position_x() - 10);
        talkingBar->setposition_y(get_position_y() - 20);
}

void Guard::notTalkingToETemer(){
        talking = false;
}
double Guard::getTalkingBarPercent(){
        return talkingBar->getPercent();
}


void Guard::verifyDeadLockHorizontal(){
  if(timerHorizontal->elapsed_time()/MAKE_SECONDS < (waitingTime + 3)){
          if(direction == "right") {
                  direction = "up";
          }else if(direction == "left"){
                  direction = "down";
          }
  }
  timerHorizontal->step();
}

void Guard::verifyDeadLockVertical(){
  if(timerVertical->elapsed_time()/MAKE_SECONDS  < (waitingTime + 3)){
          if(direction == "down"){
                  direction = "left";
          }else if(direction == "up"){
                direction = "right";
          }
  }
  timerVertical->step();
}

void Guard::stop(double &inc_x, double &inc_y){
      if(((timerVertical->elapsed_time()/MAKE_SECONDS) < waitingTime || (timerHorizontal->elapsed_time()/MAKE_SECONDS) < waitingTime) && !wayActive){
        inc_x = 0.0;
        inc_y = 0.0;
      }
}

void Guard::setWaitingTime(double newWaitingTime){
      waitingTime = newWaitingTime;
}

void Guard::nextWay(){
    search = ways.find(wayActual + 1);

    if(wayActive){
        if(search != ways.end()){
                wayActual++;
        }else{
                currentRepeat ++;
                wayActual = 1;
                if (currentRepeat >= quantityRepeatWay){
                    wayActive = false;
                    currentRepeat = 0;
                }
        }
    }
}
