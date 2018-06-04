#ifndef MAP_H
#define MAP_H

#include "/root/GitHub/Cody-Caleb-Collab/Ampersand-Alpha/utility/terminalmanager.h"
#include "/root/GitHub/Cody-Caleb-Collab/Ampersand-Alpha/utility/timemanager.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
using namespace std;

// GLOBAL VARIABLES
  // INTEGERS:
  const unsigned int TERMINAL_LENGTH = 55, TERMINAL_WIDTH = 211;
  const unsigned int MAX_CHARACTER_HEIGHT = 2, MIN_CHARACTER_HEIGHT = 54;
  const double GRAVITY = 50;
  // STRINGS:
  const string BLOCK = "▓";
  const string WALL = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "║" + term::RESET;
  const string CEILING = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "═" + term::RESET;
  const string lCEILING_CORNER = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╔" + term::RESET;
  const string rCEILING_CORNER = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╗" + term::RESET;
  const string lFLOOR_CORNER = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╚" + term::RESET;
  const string rFLOOR_CORNER = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╝" + term::RESET;
  const string EWAY_RIGHT = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╠" + term::RESET;
  const string EWAY_LEFT = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╣" + term::RESET;
  const string EWAY_UP = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╩" + term::RESET;
  const string EWAY_DOWN = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╦" + term::RESET;
  const string EWAY = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 153) + "╬" + term::RESET;
  const string POINT = term::background_color(0, 0, 0) + "." + term::RESET;
  const string BACKGROUND = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 0) + BLOCK + term::RESET;
  const string BLANK_SPACE = term::background_color(0, 0, 0) + term::foreground_color(0, 0, 0) + /*BLOCK*/ /*"▓"*/ "0" + term::RESET;
  const string POWER = term::background_color(0, 0, 0) + /*"ø"*/"●" + term::RESET;
  const string VERTEX = term::background_color(0, 0, 0) + term::foreground_color(0, 255, 0) + "●" + term::RESET;
  const string OPEN = term::background_color(0, 0, 0) + term::foreground_color(255, 0, 0) + "-" + term::RESET;

bool is_solid (const string & block);


/*
=============================================
--------------------WORLD--------------------
============================================= */
class World
{
public:
// MEMBER VARIABLES:
  string** map;
  unsigned int WORLD_LENGTH, WORLD_WIDTH;
  
  World(); // Default Constructor

  World(const string map_file); // Parameterized Constructor

  World(const World & rhs); // Copy Constructor

  ~World(); // Destructor

  void insert(const unsigned int x_coord, const unsigned int y_coord, const string character);

  void remove(const unsigned int x_coord, const unsigned int y_coord, const string character = " ");

  void print();

  void print(const unsigned int x, const unsigned int y);

  void clear();

};

#include "map.hpp"
#endif
