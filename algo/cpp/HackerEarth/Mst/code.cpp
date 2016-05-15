#include <iostream>

class UnionFind{
  public:
    UnionFind(int len){
      N = len;
      id = new int[N];
      sz = new int[N];
      for (int i = 0; i < N; i++){
        id[i] = i;
        sz[i] = 1;
      }
    }

    
    int root(int i){
      while (id[i] != i){
        id[i] = id[id[i]];
        i = id[i];
      }
      return i;
    }

    bool find(int x, int y){
      return (root(x) == root(y));
    }
    
    void Union(int x, int y){
      int px = root(x);
      int py = root(y);
      if (sz[px] > sz[py]){
        id[py] = px;
        sz[px] += sz[py]; 
      }
      else {
        id[px] = py;
        sz[py] += sz[px];
      }
    }

    int N;
    int* id;
    int* sz;
};


class Heap{
public:
  int N;
  int* w;
  int* u;
  int* v;

  Heap(int size){
    N = size;
    w = new int[N];
    u = new int[N];
    v = new int[N];
  }  
  
  void heapify(int i){
    int l = 2*i + 1;
    int r = 2*i + 2;

    int smallest = i;
    if (l < N && w[l] < w[smallest]){
      smallest = l;
    }
    if (r < N && w[r] < w[smallest]){
      smallest = r;
    }

    if (smallest != i){
      int temp;
      temp = w[smallest];
      w[smallest] = w[i];
      w[i] = temp;
      temp = u[smallest];
      u[smallest] = u[i];
      u[i] = temp;
      temp = v[smallest];
      v[smallest] = v[i];
      v[i] = temp;
      heapify(smallest);
    }
  }
    
  void createHeap(){
    for (int i = N/2+1 ; i>=0; i--){
      heapify(i); 
    }
  }
  
  void heapSort(){
    createHeap();
    int sz = N;
    for (int i = N-1; i >= 0; i --){
      int temp;
      temp = w[i];
      w[i] = w[0];
      w[0] = temp;
      temp = u[i];
      u[i] = u[0];
      u[0] = temp;
      temp = v[i];
      v[i] = v[0];
      v[0] = temp;
      N--;
      heapify(0);
    }
      N = sz;
  }

};

int main(){
  int M,N;
  std::cin >> N >> M;
  Heap hp(M);
  UnionFind uf(N);
  for (int i = 0; i < M; i++){
    int u,v,w; 
    std::cin >> u >> v >> w;
    hp.u[i] = u;
    hp.v[i] = v;
    hp.w[i] = w;
  }
  hp.heapSort();

  int sum = 0;
  for (int i = hp.N -1; i >= 0; i--){
  //  std::cout << " >> " << hp.w[i] << " : " << hp.u[i] << " : " << hp.v[i] << std::endl;
    if (! uf.find(hp.u[i], hp.v[i])){
      uf.Union(hp.u[i], hp.v[i]);
      sum += hp.w[i];
    }
  }

  std::cout << sum;
}
