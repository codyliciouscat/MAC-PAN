#ifndef CHARACTER_H
#define CHARACTER_H
#include "graphing/graphify.h"

/*
=================================================
--------------------CHARACTER--------------------
================================================= */
class Character
{
// VARIABLES:
  string symbol, symbol_prev, covered, backdrop, color;
  bool life, juiced;
  double x_coord, y_coord, x_coord_prev, y_coord_prev;
  double y_velocity, x_velocity, speed;

public:

// PARAMETRIZED CONSTRUCTOR:
  Character(const string sym, const string col, const string back, const double x, const double y, const double vroom)
  {
    symbol = sym;
    symbol_prev = "O";
    color = col;
    backdrop = back;
    x_coord = x;
    y_coord = y;
    speed = vroom;
    x_velocity = speed;
    y_velocity = 0;;
    life = true;
    juiced = false;
    covered = BACKGROUND;
  }

// GET X COORDINATE:
  int get_x_coord()
    {return (int)x_coord;}

// GET Y COORDINATE:
  int get_y_coord()
    {return (int)y_coord;}

// WAKA
  void waka()
  {
    string tmp = symbol;
    symbol = symbol_prev;
    symbol_prev = tmp;
  }

// UPDATE:
  void update_character(World& map, TimeManager time)
  {
    if(x_velocity < 0)
    {
      if(symbol == "O")
        symbol_prev = "Ͻ";
      else if(symbol_prev == "O")
        symbol = "Ͻ";
    }
    else if(x_velocity > 0)
    {
      if(symbol == "O")
        symbol_prev = "C";
      else if(symbol_prev == "O")
        symbol = "C";
    }
    else if(y_velocity < 0)
    {
      if(symbol == "O")
        symbol_prev = "U";
      else if(symbol_prev == "O")
        symbol = "U";
    }
    else if(y_velocity > 0)
    {
      if(symbol == "O")
        symbol_prev = "∩";
      else if(symbol_prev == "O")
        symbol = "∩";
    }

    // Y POSITION:
    y_coord_prev = y_coord;
    y_coord += y_velocity * time.get_delta_time();
    // X POSITION:
    x_coord_prev = x_coord;
    x_coord += x_velocity * time.get_delta_time();
    // CHECKS X DIRECTION
    double x = x_coord_prev;
    bool moving = true;
    if(x < x_coord)
    {
      while(moving)
      {
        if(!is_solid(map.map[(int)y_coord_prev][(int)x + 1]) && x < x_coord)
        {
          x += 1;
          if(x > x_coord)
            x = x_coord;
        }
        else
          moving = false;
      }
    }
    else if(x > x_coord)
    {
      while(moving)
      {
        if(!is_solid(map.map[(int)y_coord_prev][(int)x - 1]) && x > x_coord)
        {
          x -= 1;
          if(x < x_coord)
            x = x_coord;
        }
        else
          moving = false;
      }
    }
    x_coord = x;
    // CHECKS Y DIRECTION
    double y = y_coord_prev;
    moving = true;
    if(y < y_coord)
    {
      while(moving)
      {
        if(!is_solid(map.map[(int)y + 1][(int)x_coord]) && y < y_coord)
        {
          y += 1;
          if(y > y_coord)
            y = y_coord;
        }
        else
        {
          if(y != y_coord)
            y_velocity = 0;
          moving = false;
        }
      }
    }
    else if(y > y_coord)
    {
      while(moving)
      {
        if(!is_solid(map.map[(int)y - 1][(int)x_coord]) && y > y_coord)
        {
          y -= 1;
          if(y < y_coord)
            y = y_coord;
        }
        else
        {
          if(y != y_coord)
            y_velocity = 0;
          moving = false;
        }
      }
    }
    y_coord = y;
    x_coord = (((int)x_coord_prev == 1 && x_velocity < 0) || ((int)x_coord_prev == map.WORLD_WIDTH && x_velocity > 0)) ? map.WORLD_WIDTH - (int)x_coord + 1 : x_coord;

    // OUTPUTS CHARACTER
    if(!((int)y_coord == (int)y_coord_prev && (int)x_coord == (int)x_coord_prev))
    {
      map.insert((int)x_coord_prev, (int)y_coord_prev, covered);
      covered = map.map[(int)y_coord][(int)x_coord];
      covered = (covered == POINT || covered == POWER) ? BACKGROUND : covered;
    }
    map.insert((int)x_coord, (int)y_coord, backdrop + color + symbol);
  }

// MOVE:
  void move(const char input, World& map, TimeManager time)
  {
    if(input == 'a' && !is_solid(map.map[(int)y_coord][(int)x_coord - 1]))
    {
      x_velocity = -speed;
      y_velocity = 0;
    }
    else if(input == 'd' && !is_solid(map.map[(int)y_coord][(int)x_coord + 1]))
    {
      x_velocity = speed;
      y_velocity = 0;
    }
    else if(input == 'w' && !is_solid(map.map[(int)y_coord - 1][(int)x_coord]))
    {
      y_velocity = -speed;
      x_velocity = 0;
    }
    else if(input == 's' && !is_solid(map.map[(int)y_coord + 1][(int)x_coord]))
    {
      y_velocity = speed;
      x_velocity = 0;
    }
   }
};

#endif
