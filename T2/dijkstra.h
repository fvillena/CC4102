#pragma once

#include <bits/stdc++.h>

#include <vector>

#include "adj_list.h"
#include "minheap.h"

using namespace std;

vector<int> dijkstra_1(int n, vector<array<int, 3>> edges) {
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
      int v_u_dist;
      if (grafo[index_nodo][i].second == maximo_entero || distancias[index_nodo] == maximo_entero)
      {
        v_u_dist = maximo_entero;
      } else
      {
        v_u_dist = grafo[index_nodo][i].second + distancias[index_nodo];
      }
      if (v_u_dist < distancias[u]) {
        distancias[u] = v_u_dist;
        previos[u] = index_nodo;
      }
    }
  }
  return distancias;
}

vector<int> dijkstra_2(int n, vector<array<int, 3>> edges) {
  vector<vector<pair<int, int>>> grafo = make_adj_list_2(n, edges);
  int maximo_entero = INT_MAX;
  vector<int> distancias(n);
  vector<vector<int>> previos(n);
  vector<int> auxiliar;

  MinHeap* ElMinHeap = new MinHeap();
  vector<int> las_llaves(n);
  ElMinHeap->Keys = las_llaves;
  (ElMinHeap->vect)
      .push_back(make_pair(maximo_entero, maximo_entero));  // elemento dummy

  for (int i = 0; i < n; i++) {
    distancias[i] = maximo_entero;
    // previos[i]=NULL;
  }

  distancias[0] = 0;  // asumimos el nodo 0 como raiz
  ElMinHeap->insertItem(make_pair(0, 0));
  while (!(ElMinHeap->isEmpty())) {
    pair<int, int> w_nodo = ElMinHeap->extractMin();
    int dist_nodo = w_nodo.first;
    int index_nodo = w_nodo.second;
    distancias[index_nodo] = dist_nodo;
    int cant_vecinos = grafo[index_nodo].size();

    for (int i = 0; i < cant_vecinos; i++) {
      int vecino_i = grafo[index_nodo][i].second;
      int v_u_dist = grafo[index_nodo][i].first + distancias[index_nodo];
      if (v_u_dist < distancias[vecino_i]) {
        if (distancias[vecino_i] ==
            maximo_entero) {  // no lo he visitado nunca, por ende no esta en el
                              // heap
          ElMinHeap->insertItem(make_pair(v_u_dist, vecino_i));
          distancias[vecino_i] = v_u_dist;

        } else {  // estaba en el heap antes
          distancias[vecino_i] = v_u_dist;
          ElMinHeap->decreaseKey(vecino_i, v_u_dist);
        }
        previos[vecino_i].push_back(index_nodo);
      }
    }
  }
  return distancias;
}