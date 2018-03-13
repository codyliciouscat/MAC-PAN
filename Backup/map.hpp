#ifndef MAP_HPP
#define MAP_HPP

/*
================================================
--------------------IS SOLID--------------------
================================================*/
bool is_solid (const string & block)
{
  return (block != BACKGROUND && block != POINT && block != POWER && block != BLANK_SPACE);
}

/*
===========================================================
--------------------DEFAULT CONSTRUCTOR--------------------
=========================================================== */
World::World()
{
  WORLD_LENGTH = TERMINAL_LENGTH;
  WORLD_WIDTH = TERMINAL_WIDTH;

  // creates 2D array for map
  map = new string*[TERMINAL_LENGTH + 1];
  for(int i = 0; i <= TERMINAL_LENGTH; i++)
    map[i] = new string[TERMINAL_WIDTH + 1];

  for(int x = 1; x <= TERMINAL_WIDTH; x++)
  {
    for(int y = 1; y <= TERMINAL_LENGTH; y++)
    {
      if(x == 1 && y == 1)
        map[y][x] = lCEILING_CORNER;
      else if(x == 1 && y == TERMINAL_LENGTH)
        map[y][x] = WALL;
      else if(x == TERMINAL_WIDTH && y == 1)
        map[y][x] = rCEILING_CORNER;
      else if(x == TERMINAL_WIDTH && y == TERMINAL_LENGTH)
        map[y][x] = WALL;
      else if(x == 1 || x == TERMINAL_WIDTH)
        map[y][x] = WALL;
      else if(y == 1)
        map[y][x] = CEILING;
      else if(y == TERMINAL_LENGTH)
        map[y][x] = POINT;
      else
        map[y][x] = BACKGROUND;
    }
  }
}

/*
=================================================================
--------------------PARAMETERIZED CONSTRUCTOR--------------------
================================================================= */
World::World(const string map_file)
{
  unsigned int length, width;
  string tmp;
  ifstream fin;

  fin.open(map_file.c_str());

  fin >> length >> width;
  WORLD_LENGTH = length;
  WORLD_WIDTH = width;

  map = new string*[length + 1];
  for(int i = 0; i <= length; i++)
    map[i] = new string[width + 1];

  for(int y = 1; y <= length; y++)
  {
    for(int x = 1; x <= width; x++)
    {
      fin >> tmp;
      if(tmp == "x")
        map[y][x] = " ";
      else
        map[y][x] = tmp;
    }
  }

  fin.close();
}

/*
========================================================
--------------------COPY CONSTRUCTOR--------------------
======================================================== */
World::World(const World & rhs)
{
  map = new string*[rhs.WORLD_LENGTH + 1];
  for(int i = 0; i <= rhs.WORLD_LENGTH; i++)
    map[i] = new string[rhs.WORLD_WIDTH + 1];
  WORLD_LENGTH = rhs.WORLD_LENGTH;
  WORLD_WIDTH = rhs.WORLD_WIDTH;
  for(int y = 1; y <= WORLD_LENGTH; y++)
  {
    for(int x = 1; x <= WORLD_WIDTH; x++)
    {
      map[y][x] = rhs.map[y][x];
    }
  }
}

/*
==================================================
--------------------DESTRUCTOR--------------------
================================================== */
World::~World()
{
  clear();
}

/*
==============================================
--------------------INSERT--------------------
============================================== */
void World::insert(const unsigned int x_coord, const unsigned int y_coord, const string character)
{
  map[y_coord][x_coord] = character;
}

/*
==============================================
--------------------REMOVE--------------------
============================================== */
void World::remove(const unsigned int x_coord, const unsigned int y_coord, const string character)
{
  map[y_coord][x_coord] = character;
}

/*
=============================================
--------------------PRINT--------------------
============================================= */
void World::print()
{
  cout << "\e[1;1H";
  for(int y = 1; y <= WORLD_LENGTH; y++)
  {
    for(int x = 1; x <= WORLD_WIDTH; x++)
    {
      cout << map[y][x];
      if(x == WORLD_WIDTH && y != WORLD_LENGTH)
        cout << endl;
    }
  }
  cout << endl;
}

void World::print(const unsigned int x, const unsigned int y)
{
  int length, l_start, l_stop;
  int width, w_start, w_stop;

  term::get_dimensions(length, width);
  width = (width > WORLD_WIDTH) ? WORLD_WIDTH : width;
  length = (length > WORLD_LENGTH) ? WORLD_LENGTH : length;
  w_start = (x - width / 2 <= 1) ? 1 : x - width / 2;
  l_start = (y - 3 <= 1) ? 1 : y - length / 2;
  w_stop = (x + width / 2 >= WORLD_WIDTH) ? WORLD_WIDTH : x + width / 2;
  l_stop = (y + length - 3 >= WORLD_LENGTH) ? WORLD_LENGTH : y + length - 3;

  for(int y = l_start; y <= l_stop; y++)
  {
    for(int x = w_start; x <= w_stop; x++)
    {
      cout << map[y][x];
      if(x == w_stop && y != l_stop)
        cout << endl;
    }
  }
}



/*
=============================================
--------------------CLEAR--------------------
============================================= */
void World::clear()
{
  for(int y = WORLD_LENGTH; y >= 0; y--)
    delete[] map[y];
  delete[] map;
}

#endif
