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
  
  // Initialise SDL_TTF for TTF font rendering
  if (TTF_Init() == -1){
    cout << "Could not initialize SDL_TTF: error " << TTF_GetError() << endl;
    SDL_Quit();
  }
  
  // Spécifie la police
  window -> sdl_font = TTF_OpenFont("VeraMono.ttf", 20);
  if (window -> sdl_font == NULL) {
    cout << "Could not load font: error " << TTF_GetError() << endl;
    SDL_Quit();
  }

  // Set title
  SDL_SetWindowTitle(window -> sdl_window, title.c_str());

  // Set backgrund color to white
  set_sdl_color(&window -> background, &window -> empty_color);

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

void set_sdl_color(SDL_Color* dst, SDL_Color* src) {
  dst -> r = src -> r;
  dst -> g = src -> g;
  dst -> b = src -> b;
  dst -> a = src -> a;
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

void draw_text(Window* window, string text, int x, int y) {
  // Make a SDL Surface to draw the text
  SDL_Surface* surface = TTF_RenderText_Shaded(window -> sdl_font, text.c_str(), window -> color, window -> background);

  // If an error occured
  if (surface == NULL) {
    cout << "Could not init the SDL surface for TTF: " << TTF_GetError() << endl;
    exit(0);
  }

  // Retrieve he width and the height of the surface
  int h = surface -> h;
  int w = surface -> w;
  
  // Make a SDL Texture from the Surface
  SDL_Texture* texture = SDL_CreateTextureFromSurface(window -> sdl_renderer, surface);

  // Free the SDL surface
  SDL_FreeSurface(surface);
  
  // Dispaly an error if we cannot make the texture
  if (texture == NULL){
    cout << "Could not init the SDL Texture for TTF: " << SDL_GetError() << endl;
    SDL_Quit();
  }

  // Compute rendering rectangle of the texture
  SDL_Rect dst;
  dst.x = x;
  dst.y = window -> height - y - h;
  dst.w = w;
  dst.h = h;

  // Show the SDL texture
  SDL_RenderCopy(window -> sdl_renderer, texture, NULL, &dst);

  // Free the SDL texture
  SDL_DestroyTexture(texture);
}


void display_world(Window* window, World* world) {
  // Clear everything
  set_sdl_color(&window -> background, &window -> empty_color);
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
	case Lose:
	  c = &window -> lose_color;
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
  draw_fill_rectangle(window, (world -> racket_x - world -> racket_width) * xb, world -> racket_y * yb, (2 * world -> racket_width + 1) * xb, yb, &window-> racket_color);

  // Display the ball
  draw_fill_rectangle(window, world -> ball_x * xb, world -> ball_y * yb, xb, yb, &window -> ball_color);

  // Display score
  set_sdl_color(&window -> color, 255, 255, 255, 255);
  set_sdl_color(&window -> background, &window -> border_color);
  draw_text(window, "Score : "  + to_string(world -> score) + " / " + to_string(world -> nb_blocks) , 5, window -> height - 25) ;

  
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

