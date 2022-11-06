#pragma once
#include <vector>

using namespace std;

class MinHeap {
 public:  // private
  int _size = 0;
  vector<pair<int, int>> vect;
  vector<int> Keys;

  int padre(int i) { return i / 2; };
  int left(int i) { return i * 2; };
  int right(int i) { return i * 2 + 1; };
  // public:
  bool isEmpty() const { return _size == 0; };
  pair<int, int> getMin() const { return vect[1]; };
  void insertItem(pair<int, int> val);
  void shiftUp(int i);
  pair<int, int> extractMin();
  void shiftDown(int i);
  void heapify(int i);
  void decreaseKey(int nodo, int valor);
};

void MinHeap::shiftUp(int i) {
  if (i > _size) return;
  if (i == 1) return;
  if (vect[i].first <
      vect[padre(i)].first) {         // si el padre es mayor, hacemos swap
    Keys[vect[padre(i)].second] = i;  // intercambian llaves
    Keys[vect[i].second] = padre(i);
    swap(vect[padre(i)], vect[i]);

    shiftUp(padre(i));  // meti adentro de este if esto
  }
}

void MinHeap::insertItem(pair<int, int> val) {
  if (_size + 1 >= vect.size()) {
    vect.push_back(make_pair(0, 0));
  }
  vect[++_size] = val;
  Keys[val.second] =
      _size;  // la llave actual del elemento ingresado es la ultima
  shiftUp(_size);
  return;
}

void MinHeap::shiftDown(int i) {
  if (i > _size) return;
  int swapId = i;

  if (right(i) <= _size &&
      vect[i].first >
          vect[right(i)].first) {  // subimos el valor del nodo hijo izquierdo
                                   // si es menor que su padre
    swapId = right(i);
  }
  if (left(i) <= _size && vect[swapId].first > vect[left(i)].first) {
    swapId = left(i);
  }
  if (swapId != i) {
    Keys[vect[i].second] = swapId;  // intercambian llaves
    Keys[vect[swapId].second] = i;
    swap(vect[i], vect[swapId]);
    shiftDown(swapId);
  }
  return;
}

pair<int, int> MinHeap::extractMin() {
  pair<int, int> minPair = vect[1];
  Keys[vect[_size].second] = 1;  // el ultimo elemento obtiene la llave 1
  swap(vect[1], vect[_size--]);
  shiftDown(1);
  return minPair;
}

void MinHeap::heapify(int i) {
  int swapId = i;

  if (left(i) <= _size &&
      vect[i].first >
          vect[left(i)].first) {  // subimos el valor del nodo hijo izquierdo si
                                  // es menor que su padre
    swapId = left(i);
  }
  if (right(i) <= _size && vect[swapId].first > vect[right(i)].first) {
    swapId = right(i);
  }
  if (swapId != i) {
    Keys[vect[i].second] = swapId;
    Keys[vect[swapId].second] = i;
    swap(vect[i], vect[swapId]);
    shiftDown(swapId);
  }
  heapify(i - 1);
  return;
}

void MinHeap::decreaseKey(int nodo, int valor) {
  int pos_nodo_en_heap = Keys[nodo];
  vect[pos_nodo_en_heap] = make_pair(valor, nodo);
  shiftUp(pos_nodo_en_heap);
}