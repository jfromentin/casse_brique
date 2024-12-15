#include "control.hpp"

bool event_handler(Window* window, World* world) {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)!= 0){
    // Click on 'close window' button
    if(event.type==SDL_QUIT){
      return true;
    }
  }
  return false;
}

void wait(int delay) {
  SDL_Delay(delay);
}
