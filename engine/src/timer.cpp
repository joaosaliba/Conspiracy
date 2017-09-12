/**class to object of Timer, where you can find some variables, files, others objects
 *and meths to the same, here the user can control the flux of the game, he can pause and start.
 */

#include "timer.hpp"

using namespace engine;

/**
* Método start
* <p>Esse método executa a função de dar partida no game</p>
*/
void Timer::start() {
    ticks = step_ticks = SDL_GetTicks();
}

/**
* Método stop
* <p>Esse método executa a função parar o game</p>
*@param unsigned int-ticks
*@param unsigned int-step_ticks
*/

void Timer::stop() {
    ticks = 0;
    step_ticks = 0;
}

/**
* Método step
* <p></p>
*@param unsigned int-ticks
*@param unsigned int-step_ticks
*/
void Timer::step() {
    step_ticks = SDL_GetTicks();
}

/**
* Método elapsed_time
* <p>Esse método calcula o tempo gasto</p>
*@param unsigned int-elapsed_time
*@param unsigned int-step_ticks
*@return elapsed_time
*/
unsigned int Timer::elapsed_time() {
    return SDL_GetTicks() - step_ticks;
}

/**
* Método total_elapsed_time
* <p>Esse método calcula o tempo total gastono jogo</p>
*@param unsigned int-total_elapsed_time
*@param unsigned int-step_ticks
*@return total_elapsed_time
*/
unsigned int Timer::total_elapsed_time() {
    return SDL_GetTicks() - ticks;
}
