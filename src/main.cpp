#include "window.hpp"
#include "world.hpp"
#include "control.hpp"

int main(int argc, char* args[]) {
  // Init the window
  Window window;
  init_window(&window, 1200, 900, "Casse briques");

  // Init the world
  World world;
  load_world(&world, "bin/data/world1.dat");

  // The main loop
  bool quit = false;

  int time_for_move = 100;
  int time_before_move = time_for_move;
  
  while(not quit) {
    // Move the ball
    if (time_before_move == 0) { 
      move_ball(&world);
      time_before_move = time_for_move;
    }
    else {
      -- time_before_move;
    }
    
    // Display the world 
    display_world(&window, &world);

    // Handle event. The viariable quit get the value true is a quit event has occured 
    quit = event_handler(&window, &world);

    
    // Wait for a delay before a new step of the loop
    wait(5);
  }
  close_window(&window);
  delete_world(&world);
}
