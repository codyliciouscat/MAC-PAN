// Cody Moore
// CS2500
// Section: A

#include "graphify.h"
#include <assert.h>

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
=========================================================
--------------------MAX HEAP PROPERTY--------------------
========================================================= */
/*
// Check whether or not the passed node preserves the Max Heap property
template <typename T>
bool MaxHeapProperty(vector<T>& data, const int node, const unsigned int size)
{
  int index;

  if(node > (size / 2) - 1) // if passed node is a leaf node
    return true;
  else if((node * 2) + 1 < size - 1) // if passed node has two children
    index = (data[(node * 2) + 1] < data[(node * 2) + 2]) ? (node * 2) + 1 : (node * 2) + 2;
  else // if passed node has one child
    index = (node * 2) + 1;

  return(data[node] <= data[index]);
}
*/

/*
==============================================
--------------------SORTED--------------------
============================================== */
// Check whether or not the passed element to the end of the data set is sorted
/*
template <typename T>
bool sorted(vector<T>& data, const unsigned int node)
{
  bool sort = true;

  for(int tmp = 0; tmp < data.size(); tmp++)
  {
    if(tmp + 1 < data.size())
      sort = (data[tmp] > data[tmp + 1]) ? true : false;
  }

  return sort;
}
*/

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
  // Invariant: Array data[] is not empty
  assert(size != 0);
  // Invariant: All leaf nodes must preserve Max Heap property
  //for(int i = size - 1; i > (size / 2) - 1; i--)
  //  assert(MaxHeapProperty(data, i, size));

  // runs from last internal node to first element of data set
  for(int tmp = (size / 2) - 1; tmp >= 0; tmp--)
  {
    // Invariant: All nodes from tmp + 1 to last node
    //for(int i = size - 1; i >= tmp + 1; i--)
    //  assert(MaxHeapProperty(data, i, size));

    PreserveMaxHeap(data, tmp, size); // changed tmp + 1 to tmp

    // Invariant: Elements from tmp to the end of the data set preserve Max Heap
    //for(int i = size - 1; i >= tmp; i--)
    //  assert(MaxHeapProperty(data, tmp, size));
  }

  return;
}
// Post-Condition: All elements in the data set preserve Max Heap property

/*
=================================================
--------------------HEAP SORT--------------------
================================================= */

// Sorts data in an array, based on value, from least to greatest
template <typename T>
void HeapSort(vector<T>& data, unsigned int& size)
{
  CreateMaxHeap(data, size);

  // Invariant: last element in data set is sorted
  assert(data.back() <= data.back());

  for(int tmp = size - 1; tmp >= 1; tmp--)
  {
    // Invariant: All elements starting at 0 and ending at tmp preserve Max Heap property
    //            & the data set from tmp - 1 to the last node is sorted
    for(int i = 0; i < tmp + 1; i++)
      assert(MaxHeapProperty(data, i, size));
    for(int i = tmp + 1; i < size; i++)
      assert(sorted(data, i));

    swap(data, 0, tmp);
    size -= 1;
    PreserveMaxHeap(data, 0, size);
  }
  return;
}
// Post-Condition: All elements in data set are sorted, based on value,
//

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
===============================================
--------------------KRUSKAL--------------------
=============================================== */
/*
vector<Edge> Kruskal(AdjacencyMatrix graph)
{
  unsigned int size;
  vector<Edge> solution;
  vector<Edge> edges;
  vector<vector<int> > set;

  // puts every vertice into a set
  // Invariant: number of vertices in graph is greater than 0
  assert(graph.num_vertices > 0);
  for(int i = 0; i < graph.num_vertices; i++)
  {
    set.push_back({});
    set[i].push_back(i);
  }
  // Invariant: there is a set for every vertice in the graph
  assert(set.size() == graph.num_vertices);

  edges = edge_list(graph); // creates a list of edges
  size = edges.size();
  HeapSort(edges, size); // sorts list of edges
  // Invariant: the number of edges is greater than 0
  assert(edges.size() > 0);
  for(int i = 0; i < edges.size(); i++)
  {
    // checks to see if vertices in edge are in different sets
    bool in_set = false;
    int set_num_start, set_num_stop;

    // Invariant: the size of set is greater than 0
    assert(set.size() > 0);
    // Determines whether start and stop vertices are in the same set
    for(int y = 0; y < set.size(); y++)
    {
      bool start = false, stop = false;
      for(int x = 0; x < set[y].size(); x++)
      {
        if(set[y][x] == edges[i].start)
        {
          start = true;
          set_num_start = y;
        }
        if(set[y][x] == edges[i].stop)
        {
          stop = true;
          set_num_stop = y;
        }
        if(start && stop)
        {
          in_set = true;
          break;
        }
      }
      if(start && stop)
        break;
    }

    // inserts edges into solution and combines lists
    if(in_set == false)
    {
      solution.push_back(edges[i]);
      for(int k = 0; k < set[set_num_start].size(); k++)
        set[set_num_stop].push_back(set[set_num_start][k]);
      set.erase(set.begin() + set_num_start);
    }
  }
  // Invariant: size of solution is greater than zero
  assert(solution.size() > 0);
  return solution;
}
// Post-Condition: a Minimum Spanning Tree for the graph has been found
*/

/*
=======================================================
--------------------DIJKSTRA'S SSSP--------------------
======================================================= */
/*
vector<unsigned int> Dijkstra(AdjacencyMatrix graph, int source)
{
  // vector<Edge> solution;
  vector<unsigned int> distance;
  vector<unsigned int> predecessor;
  vector<Node> labels;

  distance.push_back(0);
  labels.push_back(Node(source, 0));\
  predecessor.push_back(-1);
  // Invariant: the number of vertices in the graph is greater than 0
  assert(graph.num_vertices > 0);
  for(int i = 1; i < graph.num_vertices; i++)
  {
    distance.push_back(-1);
    labels.push_back(Node(i, -1));
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

    for(int k = 0; k < graph.num_vertices; k++)
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
  vector<Edge> edges;
  unsigned int size = 0;

  place_vertices(graph);
  edges = find_edges(graph);
  size = edges.size();

  cout << "SIZE: " << size << endl;
  HeapSort(edges, size);
  for(unsigned int i = 0; i < edges.size(); i++)
    edges[i].print();

  return 0;
}
