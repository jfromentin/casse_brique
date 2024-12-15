#include "window.hpp"

void init_window(Window* window, int width, int height, string title) {
  // Initialise SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    cerr << "Could not initialize SDL2: error " << SDL_GetError() << endl;
    SDL_Quit();
  }

  // Set window geometry
  window -> width = width;
  window -> height = height;

  // Init SDL window and renderer
  int ret = SDL_CreateWindowAndRenderer(width, height, 0, &window -> sdl_window, &window -> sdl_renderer);
  if (ret < 0) {
    cerr << " Could not create SDL window: error " << SDL_GetError() << endl;
    SDL_Quit();
  }

  // Set title
  SDL_SetWindowTitle(window -> sdl_window, title.c_str());

  // Set backgrund color to white
  set_sdl_color(&window -> background, 255, 255, 255, 255);

  // Set color to black
  set_sdl_color(&window -> color, 0, 0, 0, 0);
  
  // Clear the window
  clear_window(window);

  // Refresh the window
  refresh_window(window);
}

void set_sdl_color(SDL_Color* dst, int r, int g, int b, int a) {
  dst -> r = r;
  dst -> g = g;
  dst -> b = b;
  dst -> a = a;
}

void clear_window(Window* window) {
  // Select the background color
  SDL_SetRenderDrawColor(window -> sdl_renderer,
			 window -> background.r,
			 window -> background.g,
			 window -> background.b,
			 window -> background.a);
  
  // We fill the window
  SDL_RenderClear(window -> sdl_renderer);  
}

void draw_fill_rectangle(Window* window, int x, int y, int w, int h, SDL_Color* c) {
  SDL_SetRenderDrawColor(window -> sdl_renderer, c -> r, c -> g, c -> b, c -> a);
  SDL_Rect rectangle;
  rectangle.x = x;
  rectangle.y = window -> height - y - h;
  rectangle.w = w;
  rectangle.h = h;
  SDL_RenderFillRect(window -> sdl_renderer, &rectangle);
}

void display_world(Window* window, World* world) {
  // Clear everything
  clear_window(window);

  // Compute size of a block
  int xb = window -> width / world -> width;
  int yb = window -> height / world -> height;

  // Display all non empty blocks
  SDL_Color* c;
  for (int i = 0; i < world -> width; ++ i) {
    for (int j = 0; j < world -> height; ++ j) {
      Block b = get_block(world, i, j);
      if (b != Empty) {
	int x = i * xb;
	int y = j * yb;
	switch (b) {
	case Border:
	  c = &window -> border_color;
	  break;
	case Loose:
	  c = &window -> loose_color;
	  break;
	case Type1:
	  c = &window -> block1_color;
	  break;
	case Type2:
	  c = &window -> block2_color;
	  break;
	case Type3:
	  c = &window -> block3_color;
	  break;
	default:
	  break;
	};
	draw_fill_rectangle(window, x, y, xb, yb, c);
      }
    }
  }

  // Display the racket
  int racket_width = world -> racket_right - world -> racket_left;
  draw_fill_rectangle(window, world -> racket_left * xb, world -> racket_y * yb, racket_width * xb, yb, &window-> racket_color);
  
  // Refresh
  refresh_window(window);
}

void refresh_window(Window* window){
  SDL_RenderPresent(window -> sdl_renderer);
}

void close_window(Window* window) {
  SDL_DestroyWindow(window -> sdl_window);
  SDL_DestroyRenderer(window -> sdl_renderer);
  SDL_Quit();
}

