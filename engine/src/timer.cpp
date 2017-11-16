/**
 * @file timer.cpp
 * @brief class to object of timer, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

  //#define NDEBUG *uncomment to disable assertions

#include "timer.hpp"

using namespace engine;

/**
* @brief start method
* <p>initialize the timer</p>
*/
void Timer::start() {
    ticks = step_ticks = SDL_GetTicks();
}

/**
* @brief method stop
* <p>this function put the zero value in ticks and step tickis, stopping the timer</p>
*/

void Timer::stop() {
    ticks = 0;
    step_ticks = 0;
}

/**
* @brief Método step
* @param unsigned int-ticks
* @param unsigned int-step_ticks
*/

void Timer::step() {
    step_ticks = SDL_GetTicks();
}

/**
* @brief Methodo elapsed_time
* <p>this method calculate the spent time in determinated step</p>
* @param unsigned int-elapsed_time
* @param unsigned int-step_ticks
*/

unsigned int Timer::elapsed_time() {
    assert(step_ticks > -100000 && step_ticks < 200000);

    if (SDL_GetTicks() == NULL){
        ERROR("the return of this function can not be null");
        exit(-1);
    }

    return SDL_GetTicks() - step_ticks;
}

/**
* @brief Method total_elapsed_time
* <p>this method calculate the elapsed_time</p>
* @param unsigned int-total_elapsed_time
* @param unsigned int-step_ticks
* @return total_elapsed_time
*/
unsigned int Timer::total_elapsed_time() {
    assert(ticks > -200000 && ticks < 200000);

    if (SDL_GetTicks() == NULL){
        ERROR("the return of this function can not be null");
        exit(-1);
    }

    if(ticks == NULL){
      ERROR("this value can not be null");
      exit(-1);
    }

    return SDL_GetTicks() - ticks;
}
