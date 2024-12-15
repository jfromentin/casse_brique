#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <fstream>

using namespace std;

enum Block {Empty, Border, Loose, Type1, Type2, Type3};

struct World{
  size_t height;
  size_t width;
  Block* blocks;
  int racket_left;
  int racket_right;
  int racket_y;
};

Block get_block(World* world, size_t x, size_t y);
void set_block(World* world, size_t x, size_t y, Block b);
void load_world(World* world, string filename);
void delete_world(World* world);

#endif
