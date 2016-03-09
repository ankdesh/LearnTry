#include<iostream>

struct UF{
  UF(int N){
    id = new int[N];
    sz = new int[N];
    for (int i = 0; i < N ; i++){
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

  bool find(int i, int j){
    return (root(i) == root(j));
  }

  void unionOp(int i, int j){
    if (find(i,j))
      return;
    if (sz[root(i)] < sz[root(j)]){
      sz[root(j)] += sz[root(i)];
      id[root(i)] = root(j); 
    }
    else{
      sz[root(i)] += sz[root(j)];
      id[root(j)] = root(i); 
    }
  }



  int* id;
  int* sz;

};



int main(){
  int N,Q;

  std::cin >> N >> Q;
  

  UF uf(N);
  char ch; 
  int p,q;
  for(int i=0; i < Q; i++){
    std::cin >> ch;
    if (ch == 'M'){
      std::cin >> p >> q;
      uf.unionOp(p-1,q-1);
    }
    else if (ch == 'Q'){
      std::cin >> p;
      std::cout << uf.sz[uf.root(p-1)] << std::endl;
    }
  }




}
