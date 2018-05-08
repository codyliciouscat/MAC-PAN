#include "graphify.h"
#include <algorithm>

// going to need label/vertex node
// need find neighbor with shortest distance using distance function and sort

/*
==================================================
--------------------PATH TABLE--------------------
================================================== */
class PathTable
{
public:
  map<Vertex, map<Vertex, vector<char> > > table;

};

/*
================================================
--------------------DIJKSTRA--------------------
================================================ */

vector<char> dijkstra(const Vertex source, const vector<Edge> edges, const vector<Vertex> vertices)
{
  map<Vertex, unsigned int> dist;
  map<Vertex, Vertex> predecessor;
  vector<Vertex> unvisited;
  //vector<Vertex> neighbors;
  vector<char> stuff;

  unvisited = vertices;
  // sets distance to all vertices equal to -1
  // sets predecessor to all vertices as undefined
  for(int i = 0; i < vertices.size(); i++)
  {
    dist[vertices[i]] = -1;
    predecessor[vertices[i]] = Vertex(0, 0);
  }
  dist[source] = 0;
  // loops until all nodes have been visited
  while(unvisited.size() != 0)
  {
    Vertex tmp = unvisited.front();
    vector<Vertex> neigh = neighbors(tmp, edges);

    unvisited.erase(unvisited.begin());
    for(int n = 0; n < neigh.size(); n++)
    {
      tmp.print();
      cout << "TO ";
      neigh[n].print();
      cout << " = " << distance(tmp, neigh[n]) << endl;
      //unsigned int length = distance(tmp, neigh[n]);
      unsigned int sum = dist[tmp] + distance(tmp, neigh[n]);
      cout << "SUM: " << sum << "; DISTANCE: " << dist[tmp] << endl;
      if(sum < dist[tmp])
      {
        dist[neigh[n]] = sum;
        predecessor[neigh[n]] = tmp;
      }
    }
  }
  map<Vertex, Vertex>::iterator it;
  cout << "PREDECESSOR SIZE: " << predecessor.size() << endl;
  for(it = predecessor.begin(); it != predecessor.end(); it++)
  {
    it->second.print();
    cout << " PRECEDES ";
    cout << "(" << it->first.x_coord << ", " << it->first.y_coord << ")";
    cout << endl;
  }
  map<Vertex, unsigned int>::iterator ti;
  cout << "DISTANCE SIZE: " << dist.size() << endl;
  for(ti = dist.begin(); ti != dist.end(); ti++)
  {
    cout << ti->second;
    cout << " FROM ";
    cout << "(" << ti->first.x_coord << ", " << ti->first.y_coord << ") TO ";
    source.print();
    cout << endl;
  }
  return stuff;
}

int main()
{
  World graph("../level.txt");
  vector<Edge> edges;
  vector<Vertex> vertices = find_vertices(graph);
  Vertex v = Vertex(8, 6);

  edges = find_edges(graph);
  graph.print();
  cout << "VERTICES: " << vertices.size() << endl;
  sort(edges.begin(), edges.end());
  cout << edges.size() << endl;
  for(int i = 0; i < edges.size(); i++)
    edges[i].print();
  dijkstra(v, edges, vertices);
  /*cout << "====================" << endl
       << "NEIGHBORS OF ";
       v.print(true);
  cout << "====================" << endl;
  vertices = neighbors(v, edges);
  for(int i = 0; i < vertices.size(); i++)
    vertices[i].print(true);*/

  return 0;
}
