#include "save_manager.hpp"

using namespace engine;
//#define NDEBUG *uncomment to disable assertions
#include <assert.h>

SaveManager SaveManager::instance;

int SaveManager::getStageNumberUnlock(){
  return stageNumberUnlock;
}

void SaveManager::verifySave(){
  std::fstream save(path.c_str());

  if(save.is_open()) {
        save.read(reinterpret_cast<char*>(&stageNumberUnlock), sizeof(int));
  }else{
        stageNumberUnlock = 1;
  }
  save.close();
}

void SaveManager::saveActualSituation(int unlockNumber){
  std::ofstream save(path.c_str());
  assert(unlockNumber != NULL);
  stageNumberUnlock = unlockNumber;

  if(save.is_open()){
      save.write(reinterpret_cast<const char *>(&unlockNumber), sizeof(unlockNumber));
  }

  save.close();
}
