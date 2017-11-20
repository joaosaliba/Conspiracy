/**
 * @file timer.hpp
 * @brief class to object of timer, where you can find some values, files,
 * others objects used in this class and methods to the same.
 * @copyright  GNU GENERAL PUBLIC LICENSE.
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include "log.h"
#include "sdl2includes.hpp"

namespace engine {
    class Timer {


    public:
        Timer() : ticks(0), step_ticks(0) {}
        void start();
        void stop();
        void step();

        unsigned int elapsed_time();
        unsigned int total_elapsed_time();

    private:
        unsigned int ticks;
        unsigned int step_ticks;
    };
}
#endif
