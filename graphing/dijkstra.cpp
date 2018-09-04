#include "graphify.h"
#include <algorithm>

// going to need label/vertex node
// need find neighbor with shortest distance using distance function and sort

/*
===================================================
--------------------CREATE PATH--------------------
=================================================== */
void create_path(const Vertex source, const Vertex to, PathTable & path_table, map<Vertex, Vertex> & predecessor, World & graph)
{
  // create find nearest vertex function for character
  
  vector<Node> path;
  char input;
  
  if(source == to)
    return;
  else if(predecessor[to] == source)
  {
    // if there is a teleport between vertices
    if((is_transparent(graph.map[source.y_coord][1]) && is_transparent(graph.map[to.y_coord][graph.WORLD_WIDTH])) ||
         (is_transparent(graph.map[source.y_coord][graph.WORLD_WIDTH]) && is_transparent(graph.map[to.y_coord][1])))
    {
      // ONLY WORKS FOR HORIZONTAL TELEPORTS; FOR VERTICAL, CHANGE IF STATEMENT
      //if(source.x_coord == to.x_coord)
        //input = source.y_coord < to.y_coord ? 'w' : 's';
      //else if(source.y_coord == to.y_coord)
        input = source.x_coord < to.x_coord ? 'a' : 'd';
    }
    // there is no teleport
    else
    {
      if(source.x_coord == to.x_coord)
        input = source.y_coord < to.y_coord ? 's' : 'w';
      else if(source.y_coord == to.y_coord)
        input = source.x_coord < to.x_coord ? 'd' : 'a';
    }
    path.push_back(Node(source, input));
    path.push_back(Node(to, 'x'));
  }
  else
  {
    if(path_table.table[source][to].size() == 0)
      create_path(source, predecessor[to], path_table, predecessor, graph);
    path = path_table.table[source][predecessor[to]];
     
    // if there is a teleport between vertices
    if((is_transparent(graph.map[predecessor[to].y_coord][1]) && is_transparent(graph.map[to.y_coord][graph.WORLD_WIDTH])) ||
         (is_transparent(graph.map[predecessor[to].y_coord][graph.WORLD_WIDTH]) && is_transparent(graph.map[to.y_coord][1])))
    {
      //if(predecessor[to].x_coord == to.x_coord)
        //input = predecessor[to].y_coord < to.y_coord ? 'w' : 's';
      //else if(predecessor[to].y_coord == to.y_coord)
        input = source.x_coord < to.x_coord ? 'a' : 'd';
    }
    // there is no teleport
    else
    {
      if(predecessor[to].x_coord == to.x_coord)
        input = predecessor[to].y_coord < to.y_coord ? 's' : 'w';
      else if(predecessor[to].y_coord == to.y_coord)
        input = predecessor[to].x_coord < to.x_coord ? 'd' : 'a';
    }
    path.back().move = input;
    path.push_back(Node(to, 'x'));
  }
  path_table.table[source][to] = path;

  return;
}

/*
================================================
--------------------DIJKSTRA--------------------
================================================ */

void dijkstra(const Vertex source, const vector<Edge> edges, const vector<Vertex> vertices, World & graph, PathTable & path_table)
{
  map<Vertex, unsigned int> dist;
  map<Vertex, Vertex> predecessor;
  vector<Vertex> visited;
  unsigned int counter = 0;

  // sets distance to all vertices equal to -1
  // sets predecessor to all vertices as undefined
  for(int i = 0; i < vertices.size(); i++)
  {
    dist[vertices[i]] = -1;
    predecessor[vertices[i]] = Vertex(0, 0);
  }
  dist[source] = 0;
  visited.push_back(source);

  // loops until all nodes have been visited
  while(counter < vertices.size() - 1)
  {
    Vertex tmp = visited[counter];
    vector<Vertex> neigh = neighbors(tmp, edges);

    for(int i = 0; i < neigh.size(); i++)
    {
      if(!member(visited, neigh[i]))
        visited.push_back(neigh[i]);
    }
    for(int n = 0; n < neigh.size(); n++)
    {
      unsigned int sum = distance(tmp, neigh[n], graph) + (dist[tmp] == -1 ? 0 : dist[tmp]);
      if(sum < dist[neigh[n]])
      {
        dist[neigh[n]] = sum;
        predecessor[neigh[n]] = tmp;
      }
    }
    counter++;
  }
  for(int i = 0; i < vertices.size(); i++)
  {
    create_path(source, vertices[i], path_table, predecessor, graph);
  }
  //path_table.print();
//}

 /* map<Vertex, Vertex>::iterator it;
  cout << "PREDECESSOR SIZE: " << predecessor.size() << endl;
  for(it = predecessor.begin(); it != predecessor.end(); it++)
  {
    it->second.print();
    cout << " PRECEDES ";
    cout << "(" << it->first.x_coord << ", " << it->first.y_coord << ")";
    cout << endl;
  }*/
 /* map<Vertex, unsigned int>::iterator ti;
  cout << "DISTANCE SIZE: " << dist.size() << endl;
  for(ti = dist.begin(); ti != dist.end(); ti++)
  {
    cout << ti->second;
    cout << " FROM ";
    cout << "(" << ti->first.x_coord << ", " << ti->first.y_coord << ") TO ";
    source.print();
    cout << endl;
  }*/
  return;
}

int main()
{
  World graph("../level.txt");
  vector<Edge> edges;
  vector<Vertex> vertices = find_vertices(graph);
  PathTable path_table;//, path_table_2("level_path.txt");

  edges = find_edges(graph);
  place_vertices(graph, vertices);
  graph.print();

  cout << "VERTICES: " << vertices.size() << endl;
  sort(edges.begin(), edges.end());
  cout << "EDGES: " << edges.size() << endl;
  for(int i = 0; i < vertices.size(); i++)
    dijkstra(vertices[i], edges, vertices, graph, path_table);
  cout << "====================================================" << endl
       << "--------------------PATH TABLE 1--------------------" << endl
       << "====================================================" << endl;
  path_table.f_print("level_path.txt");

  return 0;
}
