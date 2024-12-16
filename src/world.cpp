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
  world -> nb_blocks = 0;
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
	b = Lose;
	break;
      case '1':
	b = Type1;
	++ world -> nb_blocks;
	break;
      case '2':
	b = Type2;
	++ world -> nb_blocks;
	break;
      case '3':
	b = Type3;
	++ world -> nb_blocks;
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

  // Set fail to false
  world -> fail = false;
  world -> score = 0;
}

void move_ball(World* world) {
  if (world -> ball_status == Lock or world -> fail) return;
  int x = world -> ball_x;
  int y = world -> ball_y;
  int nx = x + world -> ball_dx;
  int ny = y + world -> ball_dy;

  // Check loose
  Block b = get_block(world, nx, ny);
  if (b == Lose) {
    world -> fail = true;
    cout << "You lose !" << endl; 
    return;
  }

  // Check touch racket
  if (ny == world -> racket_y) {
    if (x <= world -> racket_x + world -> racket_width and x >= world -> racket_x - world -> racket_width) {
      if (x == world -> racket_x) {
	world -> ball_dx = 0;
	world -> ball_dy = 1;
	return;
      }
      if (world -> ball_dx == 0) {
	if (x < world -> racket_x) {
	  world -> ball_dx = -1;
	}
	else {
	  world -> ball_dx = 1;
	}
      }
      world -> ball_dy = 1;
      return;
    }
    else if (nx == world -> racket_x + world -> racket_width or nx == world -> racket_x - world -> racket_width) {
      world -> ball_dx *= -1;
      world -> ball_dy = 1;
      return;
    }
	   
  }
  // Check horizontal touch
  b = get_block(world, nx, y);
  if (b != Empty) {
    world -> ball_dx *= -1;
    if (b == Type1 or b == Type2 or b == Type3) {
      set_block(world, nx, y, Empty);
      world -> score += 1;
    }
    return;
  }
  
  // Check vertical touch
  b = get_block(world, x, ny);
  if (b != Empty) {
    world -> ball_dy *= -1;
    if (b == Type1 or b == Type2 or b == Type3) {
      set_block(world, x, ny, Empty);
      world -> score += 1;
    }
    return;
  }

  // Check diagonal touch
  b = get_block(world, nx, ny);
  if (b != Empty) {
    world -> ball_dx *= -1,
    world -> ball_dy *= -1;
    if (b == Type1 or b == Type2 or b == Type3) {
      set_block(world, nx, ny, Empty);
      world -> score += 1;
    }
    return;
  }

  // The ball touch nothing
  world -> ball_x = nx;
  world -> ball_y = ny;
}

void make_rebound(World* world) {
  int ball_nx = world -> ball_x + world -> ball_dx;
  int ball_ny = world -> ball_y + world -> ball_dy;
}

void delete_world(World* world) {
  delete[] world -> blocks;
}
