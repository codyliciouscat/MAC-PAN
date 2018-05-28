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

vector<char> dijkstra(const Vertex source, const vector<Edge> edges, const vector<Vertex> vertices, World & graph)
{
  map<Vertex, unsigned int> dist;
  map<Vertex, Vertex> predecessor;
  vector<Vertex> visited;
  //vector<Vertex> neighbors;
  vector<char> stuff;
  unsigned int counter = 0;

  //unvisited = verticess
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
  //  while(visited.size() < vertices.size())
  while(counter < vertices.size() - 1)
  {
    Vertex tmp = visited[counter];
    cout << "VERTEX USED: ";
    tmp.print(true);
    vector<Vertex> neigh = neighbors(tmp, edges);

    for(int i = 0; i < neigh.size(); i++)
    {
      if(!member(visited, neigh[i]))
        visited.push_back(neigh[i]);
    }
    for(int n = 0; n < neigh.size(); n++)
    {
      tmp.print();
      cout << " TO ";
      neigh[n].print();
      cout << " = " << distance(tmp, neigh[n], graph) << endl;
      unsigned int sum = distance(tmp, neigh[n], graph) + (dist[tmp] == -1 ? 0 : dist[tmp]);
      cout << "SUM: " << sum << "; DISTANCE: " << dist[neigh[n]] << endl;
      if(sum < dist[neigh[n]])
      {
        cout << "SUM < DISTANCE" << endl;
        dist[neigh[n]] = sum;
        predecessor[neigh[n]] = tmp;
      }
    }
    counter++;
    
  cout << "DISTANCE"
       << "==========" << endl;
  map<Vertex, unsigned int>::iterator ti;
  for(ti = dist.begin(); ti != dist.end(); ti++)
  {
    cout << ti->second;
    cout << " FROM ";
    cout << "(" << ti->first.x_coord << ", " << ti->first.y_coord << ") TO ";
    source.print();
    cout << endl;
  }

  cout << "PRECEDES"
       << "=========" << endl;
  map<Vertex, Vertex>::iterator it;
  for(it = predecessor.begin(); it != predecessor.end(); it++)
  {
    it->second.print();
    cout << " PRECEDES ";
    cout << "(" << it->first.x_coord << ", " << it->first.y_coord << ")";
    cout << endl;
  }
  cout << endl << endl;

  }

  /*map<Vertex, Vertex>::iterator it;
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
  cout << "EDGES: " << edges.size() << endl;
  cout << "SOURCE VERTEX: (8, 6)" << endl << endl;

  cout << "----------EDGES----------" << endl
       << "=========================" << endl;
  for(int i = 0; i < edges.size(); i++)
    edges[i].print();
  dijkstra(v, edges, vertices, graph);

  return 0;
}
