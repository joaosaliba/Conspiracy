/**
 * @file camera.cpp
 * @brief class to object of camera, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

 //#define NDEBUG *uncomment to disable assertions

#include "camera.hpp"
#include <assert.h>

#define FILENAME "assets/sprites/camera(11X8).png"
#define WIDTH 11
#define HEIGHT 8
#define MAX_STRANGE_POSITION 1000
#define MIN_STRANGE_POSITION 0
#define HALF 2
#define MAX_STRANGE_ANGLE 1000
#define MAX_SIZE 100
/**
 * @brief Camera object constructor.
 * @param[in] double-camera_position_x it sets the x coordinate of the object.
 * @param[in] double-camera_position_y it sets the y coordinate of the object.
 * @param[in] width it sets the width dimension of the object.
 * @param[in] height it sets the height dimension of the object.
 * @param[in] direction set the new direct of the camera lever
 *
 */

Camera::Camera(double camera_position_x, double camera_position_y, std::string direction) : Enemy(FILENAME,camera_position_x,
                                                                 camera_position_y,
                                                                 WIDTH, HEIGHT){

    assert (camera_position_x != NULL);
    assert (camera_position_y != NULL);
    assert (WIDTH > 11);
    assert (HEIGHT > 8);

    if(camera_position_x > MAX_STRANGE_POSITION || camera_position_x < MIN_STRANGE_POSITION) {
      ERROR("Strange camera position");
      exit(-1);
    }else {
      //nothing to do
    }
    if(camera_position_y > MAX_STRANGE_POSITION || camera_position_y < MIN_STRANGE_POSITION) {
      ERROR("Strange camera position");
      exit(-1);
    }else {
      //nothing to do
    }
    if(WIDTH > MAX_SIZE || WIDTH < MIN_STRANGE_POSITION) {
      ERROR("Strange camera width");
      exit(-1);
    }else {
      //nothing to do
    }
    if(HEIGHT > MAX_SIZE || HEIGHT < MIN_STRANGE_POSITION) {
      ERROR("Strange camera height");
      exit(-1);
    }else {
      //nothing to do
    }

    initialize_animator(FILENAME);
    animator->set_interval(direction);
    turned_on = true;

    int default_range = 180;
    int default_angle_of_vision = 80;
    initialize_vision(default_range, default_angle_of_vision, direction);
}

/**
 * @brief Camera object constructor.
 * @param[in] double-camera_position_x it sets the x coordinate of the object.
 * @param[in] double-camera_position_y it sets the y coordinate of the object.
 * @param[in] width it sets the width dimension of the object.
 * @param[in] height it sets the height dimension of the object.
 * @param[in] direction set the new direct of the camera lever
 * @param[in] int-p_angle_of_vision
 * @param[in] int-p_range
 * @param[in] int-p_initial_angle
 */

Camera::Camera(double camera_position_x, double camera_position_y, std::string direction,
               int p_angle_of_vision, int p_range, int p_initial_angle): Enemy(FILENAME,camera_position_x,
                                                                     camera_position_y,
                                                                     WIDTH, HEIGHT){
    assert (camera_position_x != NULL);
    assert (camera_position_y != NULL);
    assert (WIDTH >= 11);
    assert (HEIGHT >= 8);

    if(camera_position_x > MAX_STRANGE_POSITION || camera_position_x < MIN_STRANGE_POSITION) {
      ERROR("Strange camera position");
      exit(-1);
    }else {
      //nothing to do
    }
    if(camera_position_y > MAX_STRANGE_POSITION || camera_position_y < MIN_STRANGE_POSITION) {
      ERROR("Strange camera position");
      exit(-1);
    }else {
      //nothing to do
    }
    if(WIDTH > MAX_SIZE || WIDTH < MIN_STRANGE_POSITION) {
      ERROR("Strange camera width");
      exit(-1);
    }else {
      //nothing to do
    }
    if(HEIGHT > MAX_SIZE || HEIGHT < MIN_STRANGE_POSITION) {
      ERROR("Strange camera height");
      exit(-1);
    }else {
      //nothing to do
    }

    initialize_animator(FILENAME);
    animator->set_interval(direction);
    turned_on = true;

    initialize_vision(p_range, p_angle_of_vision, direction);
    if(p_initial_angle != -1) {
        initial_angle = p_initial_angle;
        fieldOfVision->set_angle(initial_angle);

    }
}

/**
  *    @brief Camera object destructor.
 */

Camera::~Camera() {
}

/**
* @brief Method turn_off
* <p>This method turn off the camera</p>
* @return void
*/
void Camera::turn_off() {
    turned_on = false;
    fieldOfVision->deactivate();
}

/**
* @brief Method turned_on
* <p>This method return the state turned_on of the camera</p>
* @return bool-turned_on
*/
bool Camera::is_turned_on() {
    return turned_on;
}

/**
* @brief Method update
* <p>This method update the animator position</p>
* @return void
*/

void Camera::update(double time_elapsed) {
    assert (time_elapsed != NULL);
    time_elapsed = time_elapsed;
    animator->update();
}

/**
* @brief Method draw
* @return void
*/

void Camera::draw() {
    animator->draw(get_camera_position_x(), get_camera_position_y());
    animator->draw_collider(get_camera_position_x(), get_camera_position_y(), get_width(), get_height());
    fieldOfVision->draw();
}

/**
* @brief Method initialize_animator
* <p>This method put the initial position of the animator</p>
* @return void
*/

void Camera::initialize_animator(std::string filename) {
    state = 1;
    animator = new Animation(filename, 2, 4, 0.1);
    animator->add_animation("right",0,0);
    animator->add_animation("left",2,2);
    animator->add_animation("upright",4,4);
    animator->add_animation("upleft",6,6);
}

/**
* @brief Method initialize_vision
* <p>This method initialize the first algle of the camera</p>
* @return void
*/

void Camera::initialize_vision(int p_range, int p_angle_of_vision, std::string direction) {

    assert (p_range != NULL);
    assert (p_angle_of_vision != NULL);

    if(p_range == NULL) {
        ERROR("Do not have range of the camera");
        exit(-1);
    }else {
      //nothing to do
    }
    if(p_angle_of_vision == NULL) {
        ERROR("Do not have angle of vision");
        exit(-1);
    }else {
      //nothing to do
    }

    range = p_range;
    angle_of_vision = p_angle_of_vision;

    if(direction == "right") {
        fieldOfVision = new fieldOfVision(get_camera_position_x()+4+get_width()/HALF,get_camera_position_y()+7, range, angle_of_vision);
        initial_angle = 305;
    }else if(direction  == "left") {
        fieldOfVision = new fieldOfVision(get_camera_position_x()-4+get_width()/HALF,get_camera_position_y()+7, range, angle_of_vision);
        initial_angle = 220;
    }else if(direction == "upleft") {
        fieldOfVision = new fieldOfVision(get_camera_position_x()-6+get_width()/HALF,get_camera_position_y(), range, angle_of_vision);
        initial_angle = 140;
    }else if(direction == "upright"){
        fieldOfVision = new fieldOfVision(get_camera_position_x()+5+get_width()/HALF,get_camera_position_y(), range, angle_of_vision);
        initial_angle = 45;
    }
    fieldOfVision->set_angle(initial_angle);
}

/**
* @brief Method set_states
* @return void
*/

void Camera::set_states(int angle2, int angle3) {
    assert (angle2 > MAX_STRANGE_ANGLE);
    assert (angle3 > MAX_STRANGE_ANGLE);

    if(angle2 > MAX_STRANGE_ANGLE) {
        ERROR("Strange value by angle2");
        exit(-1);
    }else {
      //nothing to do
    }
    if(angle3 > MAX_STRANGE_ANGLE) {
      ERROR("Strange value by angle3");
      exit(-1);
    }else {
      //nothing to do
    }

    angles.push_back(angle2);
    angles.push_back(initial_angle);
    angles.push_back(angle3);
}

/**
* @brief Method change_state
* <p>This method change the angle of the camera</p>
* @return void
*/

void Camera::change_state(int p_state) {
    assert (p_state != NULL);

    if(p_state == NULL) {
        ERROR("not exist p_state");
        exit(-1);
    }else {
      //nothing to do
    }

    fieldOfVision->set_angle(angles[p_state]);
}

/**
* @brief Method get_range
* <p>This return the range value of the camera</p>
* @return int-range
*/

int Camera::get_range() {
    return range;
}

/**
* @brief Method get_fieldOfVision
* <p>This method take the value of fieldOfVision</p>
* @return void
*/

fieldOfVision* Camera::get_fieldOfVision() {
    return fieldOfVision;
}
