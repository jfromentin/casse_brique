#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h> 

#include <iostream>

#include "world.hpp"

using namespace std;

struct Window{
  SDL_Window* sdl_window;
  SDL_Renderer* sdl_renderer;
  //SDL_Surface* sdl_surface;
  TTF_Font* sdl_font;
  int width;
  int height;
  SDL_Color background;
  SDL_Color color;
  SDL_Color border_color = {127, 127, 127, 255};
  SDL_Color empty_color = {0, 0, 0, 255};
  SDL_Color lose_color = {0, 0, 0, 255};
  SDL_Color block1_color = {255, 0, 0, 255};
  SDL_Color block2_color = {0, 255, 0, 255};
  SDL_Color block3_color = {0, 0, 255, 255};
  SDL_Color racket_color = {0, 255, 255, 255};
  SDL_Color ball_color = {255, 255, 255, 255};
};

//! Initialize a window
//! \param win a pointer to Window struct to initialize
//! \param width width of the window
//! \param height heigh haight of the window
//! \param title title of th window
void init_window(Window* window, int width, int height, string title);

//! Set SDL_Color
void set_sdl_color(SDL_Color* dst, int r, int g, int b, int a);
void set_sdl_color(SDL_Color* dst, SDL_Color* src);

//! Clear window
void clear_window(Window* window);

//! Draw a rectangle with current window color
//! \param x x-coordinate of bottom left corner
//! \param y y-coordinate of bootom left corner
//! \param w width of the rectangle
//! \param h height of the rectangle
void draw_fill_rectangle(Window* window, int x, int y, int w, int h);

//! Draw a text usinf the current font
//! \param text the text to draw
//! \param x x-coordinate of bottom left corner to draw the text
//! \param y y-ccordinate of bottom left corner to draw the text
void draw_text(Window* window, string text, int x, int y);

//! Display the world
void display_world(Window* window, World* world);

//! Refresh the windo
void refresh_window(Window* window);

//! Close the window
void close_window(Window* window);
#endif
