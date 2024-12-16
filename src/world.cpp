#include "world.hpp"

Block get_block(World* world, size_t x, size_t y) {
  return world -> blocks[y * world -> width + x];
}

void set_block(World* world, size_t x, size_t y, Block b) {
  world -> blocks[y * world -> width + x] = b;
}

void load_world(World* world, string filename) {
  // Open file
  fstream file;
  file.open(filename.c_str(), ios::in);

  // Read width
  int width;
  file >> width;
  world -> width = width;

  // Read height
  int height;
  file >> height;
  world -> height = height;

  // Create world value
  world -> blocks = new Block[width * height];

  string line;
  Block b;
  for (int j = 0; j < height; ++ j) {
    file >> line;
    for (int i = 0; i < width; ++ i) {
      switch(line[i]) {
      case '.':
	b = Empty;
	break;
      case '#':
	b = Border;
	break;
      case '$':
	b = Loose;
	break;
      case '1':
	b = Type1;
	break;
      case '2':
	b = Type2;
	break;
      default:
	cerr << "Unkown block" << endl;
	b = Empty;
	break;
      }
      set_block(world, i, height - 1 - j, b);
    }
  }
  file.close();

  // Set racket coordinate
  world -> racket_x = width / 2;
  world -> racket_width = 3;
  world -> racket_y = 1;

  // Set ball parameters
  world -> ball_status = Lock;
  world -> ball_x = world -> racket_x;
  world -> ball_y = 2;
}

void move_ball(World* world) {
  if (world -> ball_status == Lock) return;
  int ball_nx = world -> ball_x + world -> ball_dx;
  int ball_ny = world -> ball_y + world -> ball_dy;
  Block b = get_block(world, ball_nx, ball_ny);
  if (b == Empty) {
    world -> ball_x = ball_nx;
    world -> ball_y = ball_ny;
  } 
}

void delete_world(World* world) {
  delete[] world -> blocks;
}
