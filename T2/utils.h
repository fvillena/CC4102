#pragma once

#include <string>
#include <random>

using namespace std;

vector<string> segment_string(string s, char del) {
  stringstream ss(s);
  string segment;
  vector<string> seglist;
  while (getline(ss, segment, del)) {
    seglist.push_back(segment);
  }
  return seglist;
}

int get_vertices_n(string g) {
  int n = stoi(segment_string(g, *"@")[0]);
  return n;
}

pair<int, vector<array<int, 3>>> parse_g(string g) {
  int vertices_n = get_vertices_n(g);
  string edges_s = segment_string(g, *"@")[1];
  vector<string> edges_s_v = segment_string(edges_s, *",");
  vector<array<int, 3>> edges;
  for (string edge_s : edges_s_v) {
    vector<string> edge_s_v = segment_string(edge_s, *"#");
    edges.push_back({stoi(edge_s_v[0]), stoi(edge_s_v[1]), stoi(edge_s_v[2])});
  }
  return make_pair(vertices_n, edges);
}

pair<int, vector<array<int, 3>>> make_random_graph(int vertices, int edges_n) {
  srand (time(NULL));
  vector<array<int, 3>> edges;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<> distr(0, vertices-1);
  for (int i = 0; i < edges_n; i++) {
    int u = distr(gen);
    int v = distr(gen);
    edges.push_back({u, v, 1});
    // cout << u << "\n";
  }
  return make_pair(vertices, edges);
}