#include<iostream>


class Heap{
  int N;
  int* d;
  int* id;
 
  Heap(){
    N = 0;
    d = new int[N];
    id = new int[N];
    for (int i = 0; i < N; i++){
      id[i] = i;
      d[i] = INT_MAX;
    }
  }  
  
 
  void heapify(int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    int smallest = i;
    if (l < N && d[l] < d[smallest]){
      smallest = l;
    }
    if (r < N && d[r] < d[smallest]){
      smallest = r;
    }

    if (smallest != i){
      int temp;
      temp = d[smallest];
      d[smallest] = d [i];
      d[i] = temp;
      temp = id[smallest];
      id[smallest] = id [i];
      id[i] = temp;
      heapify(smallest);
    }
  }

  void decIndex(int idx, int val){
    for (int i = 0; i < N; i++){
      if (id[i] == idx){
        int j = i;
        int pj = (j-1)/2;
        while( j > 0 && d[j] < d[pj] ){
          int temp;
          temp = d[j];
          d[j] = d[pj];
          d[pj] = temp;
          temp = id[j];
          id[j] = id[pj];
          id[pj] = temp;
          pj = (j-1)/2;
        } 
      }
    }
  }

  void insert(int idx, int d){
    N++;
    id[N-1] = idx;
    d[N-1] = d;
    int j = N-1;
    int pj = (j-1)/2;
    while( j > 0 && d[j] < d[pj] ){
      int temp;
      temp = d[j];
      d[j] = d[pj];
      d[pj] = temp;
      temp = id[j];
      id[j] = id[pj];
      id[pj] = temp;
      pj = (j-1)/2;
    } 
  }

  void delTop(){
    id[0] = id[N-1];
    d[0]  = d[N-1];
    N--;
    heapify(0);
  }

};

struct Vert {
  Vert( int x){
    id = x;
    d = INT_MAX;
    visited = false;
  }
  int id;
  int d;
  boolVisited;
};
  
struct AdjNode {
  Vert* vert; 
  int w;
  AdjNode* next;
};

class Graph{
public:
  int N, M;  
  AdjNode* adjList;

  Graph(int n, int m){
    N = n;
    M = m;
    adjList = new AdjNode[N];
    for (int i = 0; i < N; i++){
    adjList[i].vert = new Vert(i);  
    adjList[i].next = NULL;
  }

  void addEdge (int src, int dest, int w){
    AdjNode* newNode = new Adjnode;
    newNode->vert = adjList[src].vert;
    newNode->next = adjList[src].next;
    newNode->w = w;
    adjList[src].next = newNode;
  }
};

void main(){
  int N,M;
  std::cin >> N >> M;
  Graph gph = new Graph(N,M);
  
  for (int i = 0; i < M; i++){
    int u,v,w;
    std::cin >> u >> v >> w;
    gph.addEdge(u-1,v-1,w);
  }

  Heap hp;
  hp.insert(0,0);

  while(hp.N != 0){
    int minD = hp.d[0];
    int minIdx = hp.idx[0];
    
    hp.delTop();

    AdjNode* currNode = gph.adjList[minIdx]->next;
    while(currNode != NULL){
      if (minD + currNode->w < currNode->vert->d){
        

      }

    }
  

  } 

}

//  Queue q; 
//
//  gph.adjList[0].vert->d = 0;
//  q.insert(0);

//  Heap heap;
//  heap.insert(0,0);
 
//  while(q.head != NULL){
//    Qnode* currNode = head;
//    int min = -1;
//    Qnode* minNode = head;
//    while(currNode != NULL){
//      if (adjList[currNode->idx].vert->d < min){
//        min = adjList[currNode->idx].vert->d;
//        minNode = currNode;
//      }
//      currNode = currNode->next;
//    }
    


//struct Qnode{
//  int idx;
//  Qnode* next;
//};
//
//struct Queue{
//  Qnode* head;
//
//  Queue(){
//    head = NULL;
//  }
//
//  void insert(int idx){
//    Qnode* newNode = new Qnode;
//    newNode->idx = idx;
//    if (head == NULL){
//      newNode->next = NULL;
//      head = newNode;
//    }
//    else {
//      newNode->next = head;
//      head = newNode;
//    }
//  }
//
//};

