#ifndef MENU_SCENE_HPP
#define MENU_SCENE_HPP

#include "engine.hpp"
#include "scene.hpp"
#include "sprite.hpp"
#include "game_object.hpp"
#include "color.hpp"
#include "audio.hpp"
#include "save_manager.hpp"

#include <vector>

using namespace engine;
/** set image and sound without character
*@param scene id.
*@return SaveManager 
*/ 
class MenuScene: public Scene{
public:
    MenuScene(int id);
    ~MenuScene();
    void load();
/** draw the scene background 
*@return gameObject the object game.
*/
    void draw();
/** moves  for  change and select button
*@param timeEleapsed  time which eleapsed.
*@return  gameObject the object game.
*/

    void update(double timeElapsed);
    void unload();/* organize program */
    /** capture the button pressed from the user , if it's a pause do which , 
    *move the pointer and load or quit th scene*/

    void selectAction();
    
private:
    int selectButton;/** select button*/
    std::vector<std::pair<int, GameObject*>> gameObjectsList;/** select color if select */
    Sprite * background;/* stored the background of scene*/
    Color * select;/** select color if diselect*/
    Color * notSelect;/** photo background*/
 
    Audio * buttonEffect;/** audio was pŕoduced by button pressed*/
    Audio * selectEffect;/** select sound*/
    Audio * backgroundMusic;/** background music*/
};
        
#endif
