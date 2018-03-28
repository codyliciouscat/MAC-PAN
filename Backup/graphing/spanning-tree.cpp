#include "graphify.h"

/*
==================================================
--------------------PATH TABLE--------------------
================================================== */
class PathTable
{
public:
  map<Vertex, map<Vertex, vector<Edge> > > table;

};

/*
============================================
--------------------NODE--------------------
============================================ */
class Node
{
public:
  Vertex vertex;
  unsigned int label;

  Node(const Vertex v, const unsigned int l) : vertex(v), label(l) {}

// flipped the signs in order to sort from least to greatest with my heapsort
  bool operator<(const Node & rhs) const
    { return label > rhs.label; }

  bool operator>(const Node & rhs) const
    { return label < rhs.label; }

  bool operator<=(const Node & rhs) const
    { return label >= rhs.label; }
};

/*
============================================
--------------------SWAP--------------------
============================================ */
// Swaps the position of two elements in the data set
template <typename T>
void swap(vector<T>& data, const int x, const int y)
{
  T tmp = data[x];

  data[x] = data[y];
  data[y] = tmp;

  return;
}

/*
==================================================================
--------------------PRESERVE MAX HEAP PROPERTY--------------------
================================================================== */

// Adjusts data in an array in order to preserve the Max Heap property
template <typename T>
void PreserveMaxHeap(vector<T>& data, const int node, const unsigned int& size)
{
  unsigned int tmp = 2 * node + 1;

  if(tmp > size - 1) // checks whether the passed node is a leaf node or not
    return;      // if node is a leaf node it preserves the Max Heap property
  else if(tmp < size - 1) // checks whether the passed node possesses children
  {
    // sets tmp equal to the smaller child of the passed node
    if(tmp + 1 < size && data[tmp + 1] < data[tmp])
      tmp = tmp + 1;
  }

  // if parent node is less than child node
  if(data[node] > data[tmp])
  {
    swap(data, node, tmp);
    PreserveMaxHeap(data, tmp, size);
  }
  return;
}

/*
=======================================================
--------------------CREATE MAX HEAP--------------------
======================================================= */

// Creates a Max Heap out of data in an array
template <typename T>
void CreateMaxHeap(vector<T>& data, const unsigned int size)
{
  // runs from last internal node to first element of data set
  for(int tmp = (size / 2) - 1; tmp >= 0; tmp--)
    PreserveMaxHeap(data, tmp, size); // changed tmp + 1 to tmp

  return;
}

/*
=================================================
--------------------HEAP SORT--------------------
================================================= */

// Sorts data in an array, based on value, from least to greatest
template <typename T>
void HeapSort(vector<T>& data, unsigned int& size)
{
  CreateMaxHeap(data, size);

  for(int tmp = size - 1; tmp >= 1; tmp--)
  {
    swap(data, 0, tmp);
    size -= 1;
    PreserveMaxHeap(data, 0, size);
  }
  return;
}

/*
=================================================
--------------------EDGE LIST--------------------
================================================= */
/*
vector<Edge> edge_list(AdjacencyMatrix graph)
{
  vector<Edge> edges;
  int counter = 0;

  for(int y = 0; y < graph.num_vertices; y++)
  {
    for(int x = y; x < graph.num_vertices; x++)
    {
      if(graph.graph[y][x] != 0)
      {
        Edge tmp(graph.graph[y][x], y, x);
        edges.push_back(tmp);
      }
    }
  }
  return edges;
}
*/

/*
=======================================================
--------------------DIJKSTRA'S SSSP--------------------
======================================================= */
/*
vector<unsigned int> Dijkstra(const vector<Vertex> & vertices, const vector<Edge> & edges, int source)
{
  // vector<Edge> solution;
  vector<unsigned int> distance;
  vector<Vertex> predecessor;
  vector<Node> labels;

  distance.push_back(0);
  labels.push_back(Node(vertices[source], 0));\
  predecessor.push_back(-1);
  // Invariant: the number of vertices in the graph is greater than 0
  assert(graph.num_vertices > 0);
  for(int i = 1; i < vertices.size(); i++)
  {
    distance.push_back(-1);
    labels.push_back(Node(Vertex(vertices[i], -1));
    predecessor.push_back(-1);
  }
  // Invariant: distance, labels and predecessor are not empty
  assert(distance.size() != 0);
  assert(labels.size() != 0);
  assert(predecessor.size() != 0);

  for(int i = 0; i < labels.size(); i++)
  {
    unsigned int size = labels.size();
    HeapSort(labels, size);
    int root = labels[0].vertex;

    labels.erase(labels.begin());

    for(int k = 0; k < vertices.size(); k++)
    {
      if(graph.graph[root][k] != 0)
      {
        unsigned int tmp = distance[root] + graph.graph[root][k];

        if(tmp < distance[k])
        {
          distance[k] = tmp;
          predecessor[k] = root;
          for(int j = 0; j < labels.size(); j++)
          {
            if(labels[j].vertex == k)
              labels[j].label = tmp;
          }
        }
      }
    }
  }
  // Invariant: each vertice in the graph has a Distance
  for(int i = 0; i < graph.num_vertices; i++)
    assert(distance[i] != -1);
  return distance;
}
*/

/*
============================================
--------------------MAIN--------------------
============================================ */
/*
int main(int argc, char* argv[])
{
  ifstream fin;
  ofstream fout;
  int vertices, total_weight = 0;
  vector<Edge> solution;
  vector<unsigned int> distance;
  clock_t stop, start;
  float total_time;

  fout.open("result.txt");

  for(int arg = 1; arg <= argc; arg++)
  {
    fin.open(argv[arg]);
    fin >> vertices;
    AdjacencyMatrix graph(vertices);

    for(int y = 0; y < vertices; y++)
    {
      for(int x = 0; x < vertices; x++)
      {
        int tmp;
        fin >> tmp;
        graph.graph[y][x] = tmp;
      }
    }

    fout << "==================================================\n"
         << setw(50) << left << argv[arg] << endl
         << "==================================================\n"
         << setw(25) << left << "KRUSKAL'S MST" << endl
         << "=========================\n";

    start = clock();
    solution = Kruskal(graph);
    stop = clock();

    for(int i = 0; i < solution.size(); i++)
    {
      fout << "From: " << solution[i].start << "; To: " << solution[i].stop << "; Weight: " << solution[i].weight << endl;
      total_weight += solution[i].weight;
    }
    total_time = (stop - start) / static_cast<float>(CLOCKS_PER_SEC);
    fout << endl << "WEIGHT OF SPANNING TREE: " << total_weight << endl;
    fout << "TIME ELAPSED: " << total_time << " seconds" << endl << endl;


    fout << "=========================\n"
         << setw(25) << left << "DIJKSTRA SSSP" << endl
         << "=========================\n";
    start = clock();
    distance = Dijkstra(graph, 0);
    stop = clock();

    for(int i = 0; i < distance.size(); i++)
    {
      fout << "Vertex: " << i << "; Distance: " << distance[i] << endl;
    }
    total_time = (stop - start) / static_cast<float>(CLOCKS_PER_SEC);
    fout << endl << "TIME ELAPSED: " << total_time << " seconds" << endl << endl;
    fin.close();
  }
  fout.close();
  return 0;
}
*/

int main()
{
  World graph("../level.txt");
  vector<Vertex> vertices;
  vector<Edge> edges;
  unsigned int size = 0;

  Vertex tmp1(12, 31);
  Vertex tmp2(tmp1);
  cout << "x_coord: " << tmp2.x_coord << "; y_coord: " << tmp2.y_coord << endl;
/*
  place_vertices(graph);
  edges = find_edges(graph);
  size = edges.size();

  vertices = find_vertices(graph);

  cout << "SIZE: " << size << endl;
  HeapSort(edges, size);
  for(unsigned int i = 0; i < edges.size(); i++)
    edges[i].print(); */

  return 0;
}
