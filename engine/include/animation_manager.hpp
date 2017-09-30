#ifndef ANIMATION_MANAGER_HPP
#define ANIMATION_MANAGER_HPP

#include "animation_quad.hpp"
#include "window_manager.hpp"
#include "progress_bar.hpp"
#include "input_manager.hpp"
#include "field_of_vision.hpp"
#include "line.hpp"
#include "color.hpp"
#include <algorithm>
#include <vector>
#include "log.h"

namespace engine {
class fiels_of_vision;

class animation_manager {
public:
    static animation_manager instance;
    void add_animation_quad(animation_quad *new_quad);
    void draw_quads();
    void add_collider(SDL_Rect* render_quad);
    void add_progress_bar(progress_bar* new_progress_bar);
    void addfiels_of_vision(fiels_of_vision* field);
    void add_guard_vision(fiels_of_vision* field);
    void add_line(Line* line);
    void set_background_color(color* background_color);
private:
    animation_manager(): color(new color(100,100,100,0)){};
    bool is_active;
    Color * color;
    std::vector<animation_quad*> animation_quads;
    std::vector<SDL_Rect*> collider_rects;
    std::vector<progress_bar*> progress_bars;
    std::vector<fiels_of_vision*> fields;
    std::vector<fiels_of_vision*> guards_vision;
    void clear_animation_quads();
    void draw_colliders();
    void draw_lines_of_vision();
    void draw_progress_bars();
    void draw_line(Line* line);
    void draw_triangle_vision(std::vector<Line*> lines);
};

}
#endif
