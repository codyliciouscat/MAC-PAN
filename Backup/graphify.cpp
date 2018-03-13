#include "map.h"
#include <vector>
using namespace std;

/*
==============================================
--------------------VERTEX--------------------
============================================== */
class Vertex
{
public:
  unsigned x_coord, y_coord;

  Vertex() {}

  Vertex(const unsigned int x, const unsigned int y)
  {
    x_coord = x;
    y_coord = y;
  }
};

/*
============================================
--------------------EDGE--------------------
============================================ */
class Edge
{
public:
  unsigned int weight;
  Vertex start_vertex, stop_vertex;
  char move;
  bool empty;

  Edge() { empty = true; }

  Edge(const Vertex & v_init, const Vertex & v_fin, const unsigned int w, const char m)
  {
    start_vertex = v_init;
    stop_vertex = v_fin;
    weight = w;
    move = m;
    empty = false;
  }

  bool operator<(const Edge & rhs) const
    { return weight < rhs.weight; }

  bool operator>(const Edge & rhs) const
    { return weight > rhs.weight; }

  /*
  =========================
  ----------PRINT----------
  ========================= */
  void print()
  {
    cout << "(" << start_vertex.x_coord << ", " << start_vertex.y_coord << ") (" 
         << stop_vertex.x_coord << ", " << stop_vertex.y_coord << ") Weight: " << weight << "; Input: " << move << endl;
  }

  /*
  ===========================
  ----------F PRINT----------
  =========================== */
  void f_print(const string & o_file)
  {
    ofstream fout;
    fout.open(o_file.c_str());
    fout << start_vertex.x_coord << " " << start_vertex.y_coord << " " << stop_vertex.x_coord << " " << stop_vertex.y_coord << " " << weight << " " << move << endl;
    fout.close();
  }
};

/*
==================================
----------IS TRANSPARENT----------
================================== */
bool is_transparent(const string & cell)
  { return (cell == BACKGROUND || cell == POWER || cell == POINT || cell == VERTEX); }

/*
=============================
----------IS CORNER----------
============================= */
bool is_corner(const string & cell)
  { return (cell == lCEILING_CORNER || cell == rCEILING_CORNER || cell == lFLOOR_CORNER || cell == rFLOOR_CORNER); }

/*
=============================
----------IS VERTEX----------
============================= */
bool is_vertex(World graph, const unsigned int x_coord, const unsigned int y_coord)
{
  if(is_transparent(graph.map[y_coord][x_coord]))
  {
    // checks if vertex has at least 2 paths intersecting
    if((is_transparent(graph.map[y_coord + 1][x_coord]) || is_transparent(graph.map[y_coord - 1][x_coord])) && (is_transparent(graph.map[y_coord][x_coord - 1]) || is_transparent(graph.map[y_coord][x_coord +1])))
    {
      // returns whether or not vertex has at least 2 corners diagnol of its position
      return (1 < is_corner(graph.map[y_coord + 1][x_coord + 1]) + is_corner(graph.map[y_coord + 1][x_coord - 1]) + 
              is_corner(graph.map[y_coord - 1][x_coord + 1]) + is_corner(graph.map[y_coord - 1][x_coord - 1]));
    }
  }

  return false;
}

/*
=================================
----------FIND VERTICES----------
================================= */
vector<Vertex> find_vertices(World & graph)
{
  vector<Vertex> vertices;

  // runs through graph and pushes vertices into a vector
  for(unsigned int y = 1; y <= graph.WORLD_LENGTH; y++)
  {
    for(unsigned int x = 1; x <= graph.WORLD_WIDTH; x++)
    {
      if(is_vertex(graph, x, y))
        vertices.push_back(Vertex(x, y));
    }
  }

  return vertices;
}

/*
==================================
----------PLACE VERTICES----------
================================== */
void place_vertices(World & graph)
{
  vector<Vertex> vertices;
  
  vertices = find_vertices(graph);
  for(unsigned int i = 0; i < vertices.size(); i++)
    graph.insert(vertices[i].x_coord, vertices[i].y_coord, VERTEX);
}

/*
=============================
----------FIND PATH----------
============================= */
Edge find_path(World & graph, const unsigned int x_coord, const unsigned int y_coord, const bool positive, const bool x_direction)
{
  unsigned int tmp = x_direction ? x_coord : y_coord;
  bool loop = true;
  char move;
  unsigned int weight;
  Edge empty;

  
  while(loop)
  {
    tmp += positive ? 1 : -1;
    // if another vertex is found in the x direction
    if(x_direction && graph.map[y_coord][tmp] == VERTEX)
    {
      move = positive ? 'd' : 'a';
      weight = positive ? tmp - x_coord : x_coord - tmp;
      return Edge(Vertex(x_coord, y_coord), Vertex(tmp, y_coord), weight, move);
    }
    // if another vertex is found in the y direction
    else if(!x_direction && graph.map[tmp][x_coord] == VERTEX)
    {
      move = positive ? 's' : 'w';
      weight = positive ? tmp - y_coord : y_coord - tmp;
      return Edge(Vertex(x_coord, y_coord), Vertex(x_coord, tmp), weight, move);
    }
    // if an impass is reached
    else if(x_direction && !is_transparent(graph.map[y_coord][tmp]) || !(x_direction || is_transparent(graph.map[tmp][x_coord])))
      return empty;
  }
}

/*
==============================
----------FIND EDGES----------
============================== */
vector<Edge> find_edges(World & graph)
{
  vector<Vertex> vertices;
  vector<Edge> edges;
  Edge tmp;

  vertices = find_vertices(graph);
  for(unsigned int i = 0; i < vertices.size(); i++)
  {
    // downward path from vertex
    if(is_transparent(graph.map[vertices[i].y_coord + 1][vertices[i].x_coord]))
    {
      tmp = find_path(graph, vertices[i].x_coord, vertices[i].y_coord, true, false);
      if(tmp.empty == false)
        edges.push_back(tmp);
    }
    // upward path from vertex
    if(is_transparent(graph.map[vertices[i].y_coord - 1][vertices[i].x_coord]))
    {
      tmp = find_path(graph, vertices[i].x_coord, vertices[i].y_coord, false, false);
      if(tmp.empty == false)
        edges.push_back(tmp);
    }
    // right path from vertex
    if(is_transparent(graph.map[vertices[i].y_coord][vertices[i].x_coord + 1]))
    {
      tmp = find_path(graph, vertices[i].x_coord, vertices[i].y_coord, true, true);
      if(tmp.empty == false)
        edges.push_back(tmp);
    }
    // left path from vertex
    if(is_transparent(graph.map[vertices[i].y_coord][vertices[i].x_coord - 1]))
    {
      tmp = find_path(graph, vertices[i].x_coord, vertices[i].y_coord, false, true);
      if(tmp.empty == false)
        edges.push_back(tmp);
    }
  }

  for(unsigned int i = 0; i < edges.size(); i++)
    edges[i].print();

  return edges;
}

int main()
{
  World graph("level.txt");
  vector<Edge> paths;

  place_vertices(graph);
  graph.print();
  find_edges(graph);

  return 0;
}
