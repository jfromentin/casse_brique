#include "control.hpp"

bool event_handler(Window* window, World* world) {
  SDL_Event event;
  
  while(SDL_PollEvent(&event)!= 0){
    // Click on 'close window' button
    if(event.type == SDL_QUIT){
      return true;
    }
    // A key is pressed
    else if(event.type == SDL_KEYDOWN) {
      SDL_KeyboardEvent key_event = event.key;
      switch (key_event.keysym.sym) {
      case SDLK_LEFT:
	move_racket(world, -1);
	break;
      case SDLK_RIGHT:
	move_racket(world, 1);
	break;
      case SDLK_SPACE:
	ball_action(world);
	break;
      default:
	break;
      }
    }
  }
  return false;
}

void move_racket(World* world, int dir) {
  if (get_block(world, world -> racket_x + dir - world -> racket_width, world -> racket_y) == Empty and
      get_block(world, world -> racket_x + dir + world -> racket_width, world -> racket_y) == Empty) {
    world -> racket_x += dir;
    if (world -> ball_status == Lock) {
      world -> ball_x += dir;
    }
  }
}

void ball_action(World* world) {
  if (world -> ball_status == Lock) {
    world -> ball_dy = 1;
    int ratio = (world -> racket_x - world -> width / 2) / (world -> width / 4);
    cout << ratio << endl;
    return;
    if (world -> racket_x > world -> width / 2) {
      world -> ball_dx = -1;
    }
    else if (world -> racket_x < world -> width / 2) {
      world -> ball_dx = 1;
    }
    else {
      world -> ball_dx = 0;
    }
    world -> ball_status = Free;

  }
}

void wait(int delay) {
  SDL_Delay(delay);
}
