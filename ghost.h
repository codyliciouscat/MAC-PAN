#ifndef GHOST_H
#define GHOST_H
#include "pacman.h"
#include <cstdlib>
// RAND
char rand_move()
{
  unsigned int direction = rand() % 4;
  char tmp;

  if(direction == 0)
    tmp = 'a';
  else if(direction == 1)
    tmp = 's';
  else if(direction == 2)
    tmp = 'd';
  else if(direction == 3)
    tmp = 'w';
  return tmp;
}

/*
=============================================
--------------------GHOST--------------------
============================================= */
class Ghost
{
//protected:
public:
// VARIABLES
  const string symbol = "A";
  string color, covered, backdrop;
  double x_coord, y_coord, x_coord_prev, y_coord_prev;
  double y_velocity, x_velocity, speed;

// DEFAULT CONSTRUCTOR
  Ghost()
  {
    backdrop = term::background_color(0, 0, 0);
    x_coord = 2;
    y_coord = 2;
    color = "";
    speed = 10;
    x_velocity = speed;
    y_velocity = 0;
    covered = BACKGROUND;
  }

// GET X COORDINATE
  int get_x_coord()
    { return (int)x_coord; }

// GET Y COORDINATE
  int get_y_coord()
    { return (int)y_coord; }

// UPDATE
  void update_ghost(World & map, TimeManager time)
  {
    // Y POSITION
    y_coord_prev = y_coord;
    y_coord += y_velocity * time.get_delta_time();
    // X POSITION
    x_coord_prev = x_coord;
    x_coord += x_velocity * time.get_delta_time();

    // CHECK X DIRECTION
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

    // CHECK Y DIRECTION
    double y = y_coord_prev;
    if(y < y_coord)
    {
      while(moving)
      {
        if(!is_solid(map.map[(int)y + 1][(int)x_coord_prev]) && y < y_coord)
        {
          y += 1;
          if(y > y_coord)
            y = y_coord;
        }
        else
          moving = false;
      }
    }
    else if(y > y_coord)
    {
      while(moving)
      {
        if(!is_solid(map.map[(int)y - 1][(int)x_coord_prev]) && y > y_coord)
        {
          y -= 1;
          if(y < y_coord)
            y = y_coord;
        }
        else
          moving = false;
      }
    }
    y_coord = y;
    
    // TELEPORT
    x_coord = (((int)x_coord_prev == 1 && x_velocity < 0) || ((int)x_coord_prev== map.WORLD_WIDTH && x_velocity > 0)) ? map.WORLD_WIDTH - (int)x_coord + 1 : x_coord;

    // OUTPUTS CHARACTER
    if(!((int)y_coord == (int)y_coord_prev && (int)x_coord == (int)x_coord_prev))
    {
      map.insert((int)x_coord_prev, (int)y_coord_prev, covered);
      covered = map.map[(int)y_coord][(int)x_coord];
      //covered = (covered == POINT || covered == POWER) ? BACKGROUND : covered;
    }
    map.insert((int)x_coord, (int)y_coord, backdrop + symbol);
  }

// NEAREST VERTEX
  Vertex nearest_vertex(World & map)
  {
    bool loop = true;
    unsigned int counter = 0;
    Vertex vertex;
   
    if(is_vertex(map, x_coord, y_coord))
      vertex = Vertex(x_coord, y_coord);
    else
    {
      while(loop)
      {
        if(x_coord - counter > 1 && is_vertex(map, x_coord - counter, y_coord))
        {
          vertex = Vertex(x_coord - counter, y_coord);
          loop = false;
        }
        else if(x_coord + counter < map.WORLD_WIDTH && is_vertex(map, x_coord + counter, y_coord))
        {
          vertex = Vertex(x_coord + counter, y_coord);
          loop = false;
        }
        else if(y_coord - counter > 1 && is_vertex(map, x_coord, y_coord - counter))
        {
          vertex = Vertex(x_coord, y_coord - counter);
          loop = false;
        }
        else if(y_coord + counter > map.WORLD_LENGTH && is_vertex(map, x_coord, y_coord + counter))
        {
          vertex = Vertex(x_coord, y_coord + counter);
          loop = false;
        }
        counter += 1;
      }
    }
    return vertex; 
  }

// PREPEND PATH
  char prepend_path(World & map, vector<Node> & path)
  {
    char move;
    Vertex tmp;

    if(is_vertex(map, x_coord, y_coord))
    {
      move = path[0].move;
      path.erase(path.begin());
    }
    else
    {
      tmp = nearest_vertex(map);
      if(tmp.x_coord == x_coord)
      {
        move = tmp.y_coord < y_coord ? 'w' : 's';
      }
      else if(tmp.y_coord == y_coord)
      {
        move = tmp.x_coord < x_coord ? 'a' : 'd';
      }
    }
    return move;
  }

// MOVE
  void move(const char input, World & map, TimeManager time)
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
      x_velocity = 0;
      y_velocity = -speed;
    }
    else if(input == 's' && !is_solid(map.map[(int)y_coord + 1][(int)x_coord]))
    {
      x_velocity = 0;
      y_velocity = speed;
    }
  }
};

#endif
