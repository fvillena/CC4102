#include <time.h>

#include <string>

#include "dijkstra.h"
#include "utils.h"

using namespace std;

int main(int argc, char *argv[]) {
  int algorithm = atoi(argv[1]);
  string g = argv[2];
  pair<int,vector<array<int,3>>> graph;
  if (g=="random")
    {
      int vertices = atoi(argv[3]);
      int edges = atoi(argv[4]);
      graph = make_random_graph(vertices,edges);
    } else
    {
      graph = parse_g(g);
    }
  vector<int> distances;
  unsigned long micros = 0;
  clock_t start, end;
  start = clock();
  if (algorithm == 1) {
    distances = dijkstra_1(graph.first, graph.second);
  }
  end = clock();
  micros = end - start;
  cout << micros << "\t";
  for (int i = 0; i < distances.size(); i++) {
    cout << distances[i] << " ";
  }
  cout << "\n";
}