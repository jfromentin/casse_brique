#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <fstream>

using namespace std;

enum Block {Empty, Border, Lose, Type1, Type2, Type3};
enum BallStatus {Lock, Free};

struct World{
  size_t height;
  size_t width;
  Block* blocks;
  int nb_blocks;
  int racket_x;
  int racket_width;
  int racket_y;
  BallStatus ball_status;
  int ball_x;
  int ball_y;
  int ball_dx;
  int ball_dy;
  bool fail;
  int score;
};

Block get_block(World* world, size_t x, size_t y);
void set_block(World* world, size_t x, size_t y, Block b);
void load_world(World* world, string filename);
void move_ball(World* world);
void make_rebound(World* world);
void delete_world(World* world);

#endif
