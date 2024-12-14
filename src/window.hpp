#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

struct Window{
  SDL_Window* sdl_window;
  SDL_Surface* sdl_surface;
  int width;
  int height;
};

//! Initialize a window
//! \param win a pointer to Window struct to initialize
//! \param width width of the window
//! \param height heigh haight of the window
//! \param title title of th window
void init_window(Window* win, int width, int height, string title);

//! Wait for a given time
//! \param delay time to wait in ms
void wait(Window* win, int delay);
#endif
