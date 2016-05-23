#include <iostream>

int sumWeight = 0;

void swap(int& x, int &y){
  int temp = x;
  x = y;
  y = temp;
}

struct Heap{
  int* u;
  int* v;
  int* w;
  int N;
  
  Heap(int size){
    u = new int[size];
    v = new int[size];
    w = new int[size];
    N = size;
  }

  void heapify(int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    
    int smallest = i;
    if(l < N && w[l] < w[smallest]){
      smallest = l;
    }
    if (r < N && w[r] < w[smallest]){
      smallest = r;
    }
 
    if (smallest != i){
      swap(w[i], w[smallest]);
      swap(u[i], u[smallest]);
      swap(v[i], v[smallest]);
      heapify(smallest);
    }  
  }

  void createHeap(){
    for (int i = N/2 + 1; i >= 0; i--){
      heapify(i);
    } 
  }

  void sort(){
    int sz = N;
    for (int i = N - 1; i >= 0; i--){
      swap(w[i], w[0]);
      swap(u[i], u[0]);
      swap(v[i], v[0]);
      N --;
      heapify(0);
    }
      N = sz;
  }
};

struct UnionFind{
  int* id;
  int N;

  UnionFind(int size){
    id = new int[size];
    N = size;
    for (int i = 0; i < N; i++){
      id[i] = i;
    } 
  }

  int root(int x){
    while(id[x] != x){
      id[x] = id[id[x]];
      x = id[x];
    }
    return x;
  }

  void Union(int x, int y){
    int rx = root(x);
    int ry = root(y);

    if (rx == ry){
      return;
    }
    else {
      id[rx] = ry;
    }
  }

  int find(int x){
    return root(x);
  }
};



int main(){
  int N,M;
  std::cin >> N >> M;

  Heap heap(2 * M);

  for (int i = 0; i < M; i++){
    int u, v, w;
    std::cin >> u >> v >> w;
    heap.u[i] = u;
    heap.v[i] = v;
    heap.w[i] = w;
    
    heap.u[i+M] = v;
    heap.v[i+M] = u;
    heap.w[i+M] = w;
  }

  //for (int i = 0; i < 2 * M ; i++){
  //  std::cout << heap.w[i] << " ";
  //}
  //std::cout << std::endl; 
 
  heap.createHeap();
  heap.sort();
  //for (int i = 0; i < 2 * M; i++){
  //  std::cout << heap.w[i] << " ";
  //}
  //std::cout << std::endl; 

  UnionFind uf(N);

  for (int i = 2 * M - 1 ; i >= 0; i--){
    if ( uf.find(heap.u[i]) != uf.find(heap.v[i])){
      uf.Union(heap.u[i], heap.v[i]);
      sumWeight += heap.w[i];
      //std::cout << ">> " << heap.u[i] << " " << heap.v[i] << " " << heap.w[i] << std::endl;
    }
  }

  std::cout << sumWeight;

  //for (int i = 0; i < 2 * M; i++){
  //  std::cout << heap.w[i] << " ";
  //}
  //std::cout << std::endl; 
}
