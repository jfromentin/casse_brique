#include "window.hpp"
#include "world.hpp"
#include "control.hpp"

int main(int argc, char* args[]) {
  // Init the window
  Window window;
  init_window(&window, 1600, 1200, "Casse briques");

  // Init the world
  World world;
  load_world(&world, "bin/data/world1.dat");

  // The main loop
  bool quit = false;
  while(not quit) {
    // Display the world 
    display_world(&window, &world);
    // Handle event. The viariable quit get the value true is a quit event has occured 
    quit = event_handler(&window, &world);
    // Wait for a delay before a new step of the loop
    wait(10);
  }
  close_window(&window);
  delete_world(&world);
}
