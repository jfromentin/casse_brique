#include "window.hpp"

void init_window(Window* win, int width, int height, string title) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "Could not initialize SDL2: error " << SDL_GetError() << endl;
    exit(-1);
  }
  win -> width = width;
  win -> height = height;
  win -> sdl_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (win -> sdl_window == NULL) {
    cerr << " Could not create SDL window: error " << SDL_GetError() << endl;
    exit(-1);
  }
  win -> sdl_surface = SDL_GetWindowSurface(win -> sdl_window);
  SDL_FillRect(win -> sdl_surface, NULL, SDL_MapRGB(win -> sdl_surface -> format, 0xFF, 0xFF, 0xFF));
  SDL_UpdateWindowSurface(win -> sdl_window);
  SDL_Delay(2000);
  SDL_DestroyWindow(win -> sdl_window);
  SDL_Quit();
}
