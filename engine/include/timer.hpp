/**class to object of Timer, where you can find some variables, files, others objects
 *and meths to the same.
 */

#ifndef TIMER_HPP
#define TIMER_HPP

#include "log.h"
#include "sdl2includes.hpp"

namespace engine {
    class Timer {
/**
* Método construtor
* <p>Esse método executa a ação de construir os métodos e passar as variáreis
*utilizadas na classe timer.hpp</p>
* @param unsigned int-elapsed_time
* @param unsigned int-total_elapsed_time
* @param unsigned int-ticks
* @param unsigned int-step_ticks
*/

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
