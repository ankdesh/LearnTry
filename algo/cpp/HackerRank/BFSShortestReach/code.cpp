#include<iostream>


struct Vertex{
  int color;
  int dist;
  int id;
  Vertex* parent;
  Vertex(){
    color = 0; 
    dist = -1; 
    id = 0;
    parent = NULL;
  }
};

struct AdjNode{
  Vertex* vert;
  AdjNode* next;
}; 

struct Queue{
  Queue(int size){
    queue = new int[size];
    head = -1;
    tail = -1;
  }

  void push (int v){
    if(head == -1){
      head = 0;
      tail = 0;
      queue[tail] = v; 
    }
    else {
      tail++;
      queue[tail] = v;
    }
  }

  int pop(){
    if (tail == head){
      if (tail == -1){
        std::cout << "Underflow";
      }
      int v = queue[head];
      tail = -1;
      head = -1;
      return v;
    }
    else {
      int v = queue[head];
      head++;
      return v;
    }
  }

  int* queue;
  int head;
  int tail;
};


struct Graph{
  AdjNode* adjList;
  int numVerts;
  Queue* q;

  Graph(int numv){
    numVerts = numv;
    adjList = new AdjNode[numv];
    for ( int i = 0; i < numv; i++){
      adjList[i].vert = new Vertex;
      adjList[i].next = NULL;
      adjList[i].vert->id = i;
    }
    q = new Queue(numv);
  }
  
  void addEdge(int src, int dest){
    AdjNode* newNode = new AdjNode;
    newNode->vert = adjList[dest].vert;
    newNode->next = adjList[src].next;
    adjList[src].next = newNode;
    // Undirected graph
    newNode = new AdjNode;
    newNode->vert = adjList[src].vert;
    newNode->next = adjList[dest].next;
    adjList[dest].next = newNode;
  }

  void bfs(int src){
    adjList[src].vert->color = 1;
    adjList[src].vert->dist = 0;
    q->push(src);
    while (q->tail != -1){
      int nodeInt = q->pop();
      AdjNode& node = adjList[nodeInt];
      int dist = node.vert->dist;
      AdjNode* currNode = node.next;
      while(currNode != NULL){
        if (currNode->vert->color == 0){
          currNode->vert->color = 1;
          currNode->vert->dist = (dist+1);
          q->push(currNode->vert->id);
          //std::cout << ">>" << currNode->vert->id;
        }
        currNode = currNode->next;
      }
    }
  }
    
  void printGraph(){
      for (int i=0; i < numVerts; i++){
        std::cout << std::endl << adjList[i].vert->id << ":" ;
        AdjNode* currNode = adjList[i].next;
        while(currNode != NULL){
          std::cout << currNode->vert->id << " ";
          currNode = currNode->next;
        }
      }
  }
};

int main(){
  int T;
  std::cin>>T;
  for (int t = 0; t < T; t++){
    int N,M,S;
    std::cin >> N >> M;
    Graph* gph = new Graph(N);

    for (int e=0; e < M; e++){
      int src, dest;
      std::cin >> src >> dest;
      gph->addEdge(src-1,dest-1);
    }
    std::cin >> S;
    // gph->printGraph();
    gph->bfs(S-1);
    for (int i = 0; i < N; i++){
      if (i != S -1){
        int distVal = gph->adjList[i].vert->dist;
        if (distVal != -1)
          std::cout << distVal*6 << " ";
        else
          std::cout << "-1 ";
      }
    }
    std::cout << std::endl;
  }
}


