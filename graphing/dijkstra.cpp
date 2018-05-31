#include "graphify.h"
#include <algorithm>

// going to need label/vertex node
// need find neighbor with shortest distance using distance function and sort

/*
================================================
--------------------DIJKSTRA--------------------
================================================ */

PathTable dijkstra(const Vertex source, const vector<Edge> edges, const vector<Vertex> vertices, World & graph)
{
  map<Vertex, unsigned int> dist;
  map<Vertex, Vertex> predecessor;
  vector<Vertex> visited;
  vector<char> input;
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
  cout << counter << endl;
  cout << endl << endl;

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
  return input;
}

/*
===================================================
--------------------CREATE PATH--------------------
=================================================== */
void create_path(const Vertex source, const Vertex to, PathTable path_table, const map<Vertex, Vertex> & precedes)
{
  // create find nearest vertex function for character
  
  vector<Node> path;
  char input;
  
  if(source == to)
    return;
  else if(precedes[to] == source)
  {
    if(source.x_coord == to.x_coord)
      input = source.y_coord < to.y_coord ? s : w;
    else if(source.y_coord == to.y_coord)
      input = source.x_coord < to.x_coord ? d : a;
    path.push_back(Node(source, input));
  }
  else
  {
    if(path_table.table[source][to].size() == 0)
      create_path(source, precedes[to], path_table, precedes);
    path = path_table.table[source][precedes[to]];
     
    if(source.x_coord == to.x_coord)
      input = source.y_coord < to.y_coord ? s : w;
    else if(source.y_coord == to.y_coord)
      input = source.x_coord < to.x_coord ? d : a;
    path.push_back(Node(source, input));
  }
  path_table.table[source][to] = input;

  return;
}

int main()
{
  World graph("../level.txt");
  vector<Edge> edges;
  vector<Vertex> vertices = find_vertices(graph);
  Vertex v = Vertex(8, 6);

  edges = find_edges(graph);
  place_vertices(graph, vertices);
  graph.print();

  cout << "VERTICES: " << vertices.size() << endl;
  sort(edges.begin(), edges.end());
  cout << "EDGES: " << edges.size() << endl;
  cout << "SOURCE VERTEX: (8, 6)" << endl << endl;

  cout << "----------EDGES----------" << endl
       << "=========================" << endl;
  for(int i = 0; i < edges.size(); i++)
    edges[i].print();
  dijkstra(v, edges, vertices, graph);

  return 0;
}
