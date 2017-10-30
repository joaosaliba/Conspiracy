//#define NDEBUG *uncomment to disable assertions
#include "alien_bilu.hpp"
#include "collision_manager.hpp"
#include "paper.hpp"
#include "door_switch.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/bilu_sheet.png"
#define WIDTH 19
#define HEIGHT 22
#define SCREEN_WIDTH 1000
#define SCREEN_INITIAL 0
#define VELOCITY_BILU 0.15
#define ACTION_SPECIAL_LEFT "special_left"
#define SPRITE_INITIAL_SPECIAL_LEFT 10
#define SPRITE_FINAL_SPECIAL_LEFT 13
#define ACTION_SPECIAL_RIGHT "special_right"
#define SPRITE_INITIAL_SPECIAL_RIGHT 14
#define SPRITE_FINAL_SPECIAL_RIGHT 17
#define TOTAL_TIME_1 0.3
#define TOTAL_TIME_2 0.6
#define ANIMATION_NUMBER 5
#define CENTER_CHARACTER_1 11
#define CENTER_CHARACTER_2 20
#define ANIMATION_IDLE "idle"
#define ACTION_IDLE_LEFT "idle_left"
#define ACTION_IDLE_RIGHT "idle_right"
#define INITIAL_HACKING_BAR_PERCENT 0.0
#define INITIAL_BAR_PERCENT 0.0
#define NAME_CHARACTER "B"


/** Objects included in the alien_bilu.hpp, door_switch.hpp classes found on lines 1 to
* line 4, where the methods will be responsible for the manipulation and organization
* of these objects
*@param unsigned double-bilu_position_x
*@param unsigned double-bilu_position_y
*@param unsigned bool-hacking
*@param unsigned bool-editing
*@param unsigned bool-last_action
*@param unsigned bool-is_selected
*@param unsigned bool-in_position
*/

Bilu::Bilu(double bilu_position_x, double bilu_position_y) :
Alien(FILENAME, bilu_position_x, bilu_position_y, WIDTH, HEIGHT) {
   
    INFO("Bilu constructor init");
    
    double bilu_position_x = 0.0;
    double bilu_position_y = 0.0;
    bool hacking = true;
    bool editing = true;
    bool last_action = true;
    bool is_selected = true;
    bool in_position = true;  
   
    assert (bilu_position_x !=NULL);
    assert (bilu_position_y !=NULL);
    assert (WIDTH !=NULL);
    assert (WIDTH > 19);
    assert (HEIGHT !=NULL);
    assert (HEIGHT > 22);

    DEBUG("bilu position x : "+bilu_position_x);
    DEBUG("bilu position y : "+bilu_position_y);

    
    //verifies the position x of the character Bilu
    if(bilu_position_x > SCREEN_WIDTH || bilu_position_x < SCREEN_INITIAL) {
        ERROR("Strange Bilu position x");
        exit(-1);
    }else {
       //nothing to do
       INFO("Bilu position x ok");
    }

    //verifies the position y of the character Bilu
    if(bilu_position_y > SCREEN_WIDTH || bilu_position_y < SCREEN_INITIAL) {
       ERROR("Strange Bilu position y");
       exit(-1);
     }else {
       //nothing to do
       INFO("Bilu position y ok");
     }
      
    animator->add_action(ACTION_SPECIAL_RIGHT,SPRITE_INITIAL_SPECIAL_RIGHT,SPRITE_FINAL_SPECIAL_RIGHT);
    animator->add_action(ACTION_SPECIAL_LEFT,SPRITE_INITIAL_SPECIAL_LEFT,SPRITE_FINAL_SPECIAL_LEFT);
    
    hacking = false;
    editing = false;
    last_action = false;
    is_selected = false;
    in_position = false;

    INFO("Bilu constructor ok");
}
/**
* Update method
* <p>movement and special actions of the character, in addition to checking the finishi point</p>
*@param unsigned double-time_elapsed
*@param unsigned bool-in_position
*@return void
*/

void Bilu::update(double time_elapsed) {
    
    INFO("Bilu update init");

    double time_elapsed = 0.0;
    bool in_position = true;
    
    assert ( time_elapsed != NULL);

    //check the elapsed time
    DEBUG("time elapsed : "+time_elapsed);

    if(time_elapsed == -1) {
       ERROR("Strange time Bilu update");
       exit(-1);
     }else {
       //nothing to do
       INFO("time elapsed Bilu ok");
     }

    in_position = false;
    animator->set_total_time(TOTAL_TIME_1);
    auto move_bilu_in_y = VELOCITY_BILU*time_elapsed;//velocidade bilu
    auto move_bilu_in_x = VELOCITY_BILU*time_elapsed;

    //checks conditions to move the player Bilu
    if(!block_movement && is_selected) {
        walk_in_x(move_bilu_in_x);
        walk_in_y(move_bilu_in_y, move_bilu_in_x);
        INFO("walk ok");
    }else {
        //nothing to do
        INFO("walk strange");
    }

    //check atributes to move the player Bilu
    if(move_bilu_in_x == 0 && move_bilu_in_y == 0) {
        INFO("check whether move_bilu receives such values");
        DEBUG("move bilu in x : "+move_bilu_in_x);
        DEBUG("move bilu in y : "+move_bilu_in_y);
        //if idle animation number
        if(idle_animation_number) {
            animator->set_interval(ACTION_IDLE_RIGHT);
            INFO("action idle right ok");
        //Assigns a default animator
        }else {
            animator->set_interval(ACTION_IDLE_LEFT);
            INFO("action idle left ok");
        //check atributes to move the player Bilu
        }
}
    special_action();
    
    //Check the collisions with the cameras
    if(CollisionManager::instance.verify_collision_with_guards(this) ||
    CollisionManager::instance.verify_collision_with_cameras(this)) {
        
        INFO("check the collisions with the cameras and guards");

        setEnabled(false);
        //Assigns a default true
        }else {
            setEnabled(true);          
    }
    FinishPoint* finish_point = (FinishPoint*)
    CollisionManager::instance.verify_collision_with_finish_points(this);
    
    //Check if the finish point is different from null
    check_final_position(finish_point,&in_position);

    animator->update();
}

void Bilu::check_final_position(FinishPoint* finish_point,bool &in_position){
    
    INFO("Bilu check final position");
    
    if(finish_point != NULL) {
    DEBUG("finish point in check_final_position : "+finish_point);    
        if(finish_point->get_alien_names().find(NAME_CHARACTER) != std::string::npos) {
            in_position = true;
            INFO("final position ok");
        //Assigns a default in_position true
        }else {
            in_position(false);
            INFO("final position false");
        }
    }else{
        //nothing to do
    }
}

/**
* Special action method
* <p>verifies the interaction of both paper and pc</p>
*@param unsigned bool-hacking
*@param unsigned bool-editing
*@return void
*/

void Bilu::special_action() {

    INFO("Bilu special action init");

    bool hacking = true;
    bool editing = true;

    std::pair<int, int> interval;

    GameObject* paper = CollisionManager::instance.verify_collision_with_papers(this);
    GameObject* doorSwitch = CollisionManager::instance.verify_collision_with_switches(this);

    if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_SPACE) && is_selected) {
    // Paper interaction
        editing_paper(paper,editing,block_movement);
        INFO("Bilu editing paper");
    // PC interaction
        //Check if the door switch is different from null 
        if(doorSwitch != NULL) {
            INFO("check if doorSwitch receives values ​​other than null");
            DEBUG("doorSwitch in special_action : "+doorSwitch);
            if(!hacking) {
                hacking = true;
                block_movement = true;
                ((DoorSwitch*)(doorSwitch))->play_effect();
                INFO("hacking ok, doorSwitch receives play_effect");
            //Assigns a default hacking and block_movement false
            }else {
                hacking = false;
                block_movement = false;
                INFO("hacking false");
            }
        }else{
            //nothing to do
        }

//Chech if instance was selected
}else if(InputManager::instance.is_key_pressed(InputManager::KEY_PRESS_ESC)&& is_selected) {
    // If hacking
    if(hacking) {
        INFO("hacking where the instance was selected");
        hacking = false;
        block_movement = false;
        ((DoorSwitch*)(doorSwitch))->stop_effect();
        ((DoorSwitch*)(doorSwitch))->stop_animation();
        ((DoorSwitch*)(doorSwitch))->reset_hacking_progress();
        //Assigns a default hacking and block_movement false, and paper receives actions
        }else if (editing) {
            INFO("editing where the instance was selected");
            editing = false;
            block_movement = false;
            ((Paper*)(paper))->stop_effect();
            ((Paper*)(paper))->stop_animation();
            ((Paper*)(paper))->reset_editing_progress();
        }
}
    // If hacking
    if(hacking) {
        INFO("hacking init");
        ((DoorSwitch*)(doorSwitch))->animate();
        set_special_action_animator();
            // doorSwitch receives actions
        if(((DoorSwitch*)(doorSwitch))->get_hacking_bar_percent() <= INITIAL_HACKING_BAR_PERCENT) {
            INFO("initial hacking bar percent");
            hacking = false;
            ((DoorSwitch*)(doorSwitch))->stop_animation();
            ((DoorSwitch*)(doorSwitch))->stop_effect();
            ((DoorSwitch*)(doorSwitch))->reset_hacking_progress();
            Alien::animator->set_interval(ANIMATION_IDLE);
            block_movement = false;
            //Assigns a default hacking and block_movement false
            }else {
                hacking = true;
                block_movement = true;
                INFO("hacking ok");
            }
// If editing receives actions
}else if(editing) {
    INFO("editing init");
    ((Paper*)(paper))->animate();
    set_special_action_animator();
        if(((Paper*)(paper))->get_editing_bar_percent() <= INITIAL_BAR_PERCENT) {
             INFO("initial editing bar percent");
            editing = false;
            ((Paper*)(paper))->stop_animation();
            //((Paper*)(paper))->stop_effect();
            ((Paper*)(paper))->reset_editing_progress();
            Alien::animator->set_interval(ANIMATION_IDLE);
            block_movement = false;
        //Assigns a default hacking and block_movement false    
        }else {
            editing = true;
            block_movement = true;
            INFO("editing ok"); 
        }
}
    last_action = hacking;
}
void Bilu::editing_paper(Paper* paper,bool &editing, bool &block_movement){
    INFO("Editing paper");
    if(paper != NULL) {
        DEBUG("paper in editing_paper : "+paper);
        // If editing
        if(! editing) {
            editing = true;
            block_movement = true;
            ((Paper*)(paper))->play_effect();
            INFO("editing_paper ok");
            //Assigns a default editing and block_movement false
            }else {
                editing = false;
                block_movement = false;
                INFO("editing_paper false");
            }
        }else {
            //nothing to do
        }
}
/**
* Draw method
* <p>draws the animation of the character according to its position</p>
*@param unsigned double-bilu_position_x
*@param unsigned double-bilu_position_y
*@return void
*/

void Bilu::draw() {

    INFO("Bilu draw init");

    double bilu_position_x = 0.0;
    double bilu_position_y = 0.0;

    DEBUG("bilu draw position x : "+bilu_position_x);
    DEBUG("bilu draw position y : "+bilu_position_y);

    INFO("Bilu DRAW");
    animator->draw(get_position_x() - CENTER_CHARACTER_1, get_position_y() - CENTER_CHARACTER_2);
    animator->draw_collider(get_position_x(), get_position_y(), get_width(), get_height());
}

/**
* Special action animator
* <p>special character animation</p>
*@return void
*/

void Bilu::set_special_action_animator() {

    INFO("Bilu set special action animator init");
    
    // Check if idle_animation_number is equals 5
    if(idle_animation_number == ANIMATION_NUMBER) {
        animator->set_interval(ACTION_SPECIAL_RIGHT);
        INFO("Bilu idle animation number == animation number ok");
    // If you do not receive an action
    }else {
        animator->set_interval(ACTION_SPECIAL_LEFT);
        INFO("Bilu idle animation number receives action special left");
    }
        animator->set_total_time(TOTAL_TIME_2);
}