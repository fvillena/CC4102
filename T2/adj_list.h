#pragma once
#include <vector>

#include "utils.h"

using namespace std;

// https://www.geeksforgeeks.org/graph-and-its-representations/

void addEdge(vector<pair<int, int>> adj[], int u, int v, int w) {
  adj[u].push_back(make_pair(v, w));
}

pair<int, int> get_min(vector<int> arreglo, vector<int> auxiliar) {
  int tamanho = arreglo.size();
  int minimo = INT_MAX;  // INT64_MAX;
  int indice = 0;
  for (int i = 0; i < auxiliar.size(); i++) {
    if (arreglo[auxiliar[i]] <= minimo) {
      minimo = arreglo[auxiliar[i]];
      indice = auxiliar[i];
    }
  }
  return make_pair(indice, minimo);
}

vector<vector<pair<int, int>>> make_adj_list(int n,
                                             vector<array<int, 3>> edges) {
  const int vertices_n = n;
  vector<pair<int, int>> adj[vertices_n];
  for (array<int, 3> edge : edges) {
    addEdge(adj, edge[0], edge[1], edge[2]);
  }
  vector<vector<pair<int, int>>> v;
  for (int i = 0; i < vertices_n; i++) {
    v.push_back(adj[i]);
  }
  return v;
}
