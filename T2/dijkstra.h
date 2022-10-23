#pragma once

#include <bits/stdc++.h>

#include <vector>

#include "adj_list.h"

using namespace std;

vector<int> dijkstra_1(int n, vector<array<int,3>> edges) {
  vector<vector<pair<int, int>>> grafo = make_adj_list(n, edges);
  int maximo_entero = INT_MAX;
  vector<int> distancias(n);
  vector<int> previos(n);
  vector<int> auxiliar;
  for (int i = 0; i < n; i++) {
    distancias[i] = maximo_entero;
    previos[i] = -1;
    auxiliar.push_back(i);
  }

  distancias[0] = 0;  // asumimos el nodo 0 como raiz

  while (auxiliar.empty() == false) {
    pair<int, int> w_nodo = get_min(distancias, auxiliar);
    int dist_nodo = w_nodo.second;
    int index_nodo = w_nodo.first;
    auxiliar.erase(find(auxiliar.begin(), auxiliar.end(), index_nodo));
    int cant_vecinos = grafo[index_nodo].size();

    for (int i = 0; i < cant_vecinos; i++) {
      int u = grafo[index_nodo][i].first;
      int v_u_dist = grafo[index_nodo][i].second + distancias[index_nodo];
      if (v_u_dist < distancias[u]) {
        distancias[u] = v_u_dist;
        previos[u] = index_nodo;
      }
    }
  }
  return distancias;
}