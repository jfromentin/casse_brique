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
  world -> racket_left = width / 2 - 3;
  world -> racket_right = width / 2 + 3;
  world -> racket_y = 1;
  
}

void delete_world(World* world) {
  delete[] world -> blocks;
}
