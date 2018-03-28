#include "../map.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
using namespace std;

/*
==============================================
--------------------VERTEX--------------------
============================================== */
class Vertex
{
public:
  unsigned int x_coord, y_coord;

  // default constructor
  Vertex() {}

  // parameterized constructor
  Vertex(const unsigned int x, const unsigned int y)
  {
    x_coord = x;
    y_coord = y;
  }

  // copy constructor
  Vertex(const Vertex & tmp)
    { x_coord = tmp.x_coord; y_coord = tmp.y_coord;  }

  // operator= (with another Vertex)
  void operator=(const Vertex & rhs)
    { x_coord = rhs.x_coord; y_coord = rhs.y_coord; }

  // operator= (with a string)
  void operator=(string rhs)
  {
    size_t pos;
    unsigned int x, y;

    pos = rhs.find(",");
    stringstream tmp1(rhs.substr(pos + 1));
    tmp1 >> y;
    rhs.erase(rhs.begin() + pos, rhs.end());
    stringstream tmp2(rhs);
    tmp2 >> x;
    x_coord = x;
    y_coord = y;
  }

  // operator== (with a another Vertex
  bool operator==(const Vertex & rhs) const
    { return (x_coord == rhs.x_coord && y_coord == rhs.y_coord); }

  // operator== (with a string) Ex. Vertex(1, 2) == "1,2"
  bool operator==(string rhs) const
  {
    size_t pos;
    unsigned int x, y;

    pos = rhs.find(",");
    stringstream tmp1(rhs.substr(pos + 1));
    tmp1 >> y;
    rhs.erase(rhs.begin() + pos, rhs.end());
    stringstream tmp2(rhs);
    tmp2 >> x;

    return (x_coord == x && y_coord == y);
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

  bool operator<=(const Edge & rhs) const
    { return weight <= rhs.weight; }

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
========================================================
--------------------ADJACENCY MATRIX--------------------
======================================================== */
/*
class AdjacencyMatrix
{
  vector<vector<int> > graph;
  int num_vertices;

  AdjacencyMatrix(const int vertices) */
  
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
  unsigned int counter = 0;

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
  unsigned int x = x_coord, y = y_coord;
  unsigned int weight, weight_to_teleport = 0;
  char move;
  bool loop = true;
  Edge empty;

  
  while(loop)
  {
    tmp += positive ? 1 : -1;
    // if another vertex is found in the x direction
    if(x_direction && graph.map[y][tmp] == VERTEX)
    {
      move = positive ? 'd' : 'a';
      weight = tmp > x ? tmp - x + weight_to_teleport : x - tmp + weight_to_teleport;
      return Edge(Vertex(x_coord, y_coord), Vertex(tmp, y_coord), weight, move);
    }
    // if another vertex is found in the y direction
    else if(!x_direction && graph.map[tmp][x] == VERTEX)
    {
      move = positive ? 's' : 'w';
      weight = tmp > y ? tmp - y + weight_to_teleport : y - tmp + weight_to_teleport;
      return Edge(Vertex(x_coord, y_coord), Vertex(x_coord, tmp), weight, move);
    }
    // if a teleport path thing is reached in x direction
    else if((x_direction && tmp > graph.WORLD_WIDTH) || (x_direction && tmp < 2))
    {
      weight_to_teleport = tmp > x_coord ? tmp - x_coord : x_coord - tmp;
      tmp = tmp < 2 ? graph.WORLD_WIDTH : 1;
      x = tmp;
    }
    // if a teleport path thing is reached in y direction
    else if((!x_direction && tmp > graph.WORLD_LENGTH) || (!x_direction && tmp < 2))
    {
      weight_to_teleport = tmp > y_coord ? tmp - y_coord : y_coord - tmp;
      tmp = tmp < 2 ? graph.WORLD_LENGTH : 1;
      y = tmp;
    }
    // if an impass is reached
    else if(x_direction && !is_transparent(graph.map[y][tmp]) || !(x_direction || is_transparent(graph.map[tmp][x])))
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

  return edges;
}

/*
int main()
{
  World graph("../level.txt");
  vector<Edge> edges;

  place_vertices(graph);
  graph.print();
  edges = find_edges(graph);

  cout << edges.size() << " EDGES FOUND IN MAP" << endl;
  for(unsigned int i = 0; i < edges.size(); i++)
    edges[i].print();

  return 0;
} */
