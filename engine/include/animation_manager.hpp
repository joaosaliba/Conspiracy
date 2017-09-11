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
class FieldOfVision;

class AnimationManager {
public:
    static AnimationManager instance;
    void addAnimationQuad(AnimationQuad* new_quad);
    void drawQuads();
    void addCollider(SDL_Rect* render_quad);
    void addProgressBar(ProgressBar* new_progress_bar);
    void addFieldOfVision(FieldOfVision* field);
    void addGuardVision(FieldOfVision* field);
    void addLine(Line* line);
    void setBackgroundColor(Color* background_color);

private:
    AnimationManager(): color(new Color(100,100,100,0)){};
    bool isActive;

    Color * color;

    std::vector<AnimationQuad*> animation_quads;
    std::vector<SDL_Rect*> collider_rects;
    std::vector<ProgressBar*> progress_bars;
    std::vector<FieldOfVision*> fields;
    std::vector<FieldOfVision*> guards_vision;

    void clearAnimationQuads();
    void drawColliders();
    void drawLinesOfVision();
    void drawProgressBars();
    void drawLine(Line* line);
    void drawTriangleVision(std::vector<Line*> lines);
};

}
#endif
