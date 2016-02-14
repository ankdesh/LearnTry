#include <iostream>

struct Vert {
  int index;
  int color;  
  unsigned int dist;
  int parentId;
};

struct AdjListNode {
  Vert* destVert;
  AdjListNode* next;
};

struct QueueNode{
  int vertIndex;
  QueueNode* next;
};

struct Queue{
  Queue(){
    head = NULL;
    tail = NULL;
  }

  void push(int vertIndex){
    QueueNode* newNode = new QueueNode();
    newNode->vertIndex = vertIndex;
    newNode->next = NULL;
    if (tail == NULL){  
      head = newNode;
      tail = newNode;
    }
    else{
      tail->next = newNode;
      tail = newNode;
    }
  }

  int pop(){
    if (head == NULL){
      std::cout << "WTF" << std::endl;
      return 0;
    }
    QueueNode* currNode = head;
    if (head->next == NULL){
      head = NULL;
      tail = NULL;
    }
    else {
      head = head->next;
    }
    return currNode->vertIndex;
  }

  QueueNode* head;
  QueueNode* tail;
};

struct Graph{
  Graph(int numV):
    numV(numV){ 
      adjListHeads = new AdjListNode[numV];
      for (int i = 0; i < numV; i++){
        adjListHeads[i].next = NULL;
        adjListHeads[i].destVert = new Vert;
        adjListHeads[i].destVert->index = i; 
        adjListHeads[i].destVert->color = 0; 
        adjListHeads[i].destVert->dist = 0xFFFFFFFF; 
        adjListHeads[i].destVert->parentId = i; 
      }
  } 

  void addEdge(int src, int dest){
    AdjListNode* newEdge = new AdjListNode;
    newEdge->destVert = adjListHeads[dest].destVert;
    newEdge->next = adjListHeads[src].next;
    adjListHeads[src].next = newEdge; 
  }

  void printGraph(){
    for (int i = 0; i < numV; i++){
      std::cout << std::endl << "Vertex " ;
      Vert* destVert = adjListHeads[i].destVert;
      std::cout <<"(" << destVert->index << " :"
                << destVert->parentId << "," 
                << destVert->color << ","
                << destVert->dist << ")  " << std::endl;
      AdjListNode* currNode = adjListHeads[i].next;
      while (currNode != NULL){
        std::cout << currNode->destVert->index << "  " ;
        currNode = currNode->next;
      }
    }
  }

  void bfs(int startIndex);

  int           numV;
  AdjListNode*  adjListHeads; 
  Queue         que;

};

void Graph::bfs(int startIndex){
  que.push(startIndex);
  adjListHeads[startIndex].destVert->dist = 0;
  while (que.head != NULL){
    int currVertIndex = que.pop();
    std::cout << "Start working on Vert" << currVertIndex << std::endl;
    AdjListNode* traverseNode = adjListHeads[currVertIndex].next;

    while (traverseNode != NULL){
      std::cout << "Traversing node" << traverseNode->destVert->index << std::endl;
      if (traverseNode->destVert->color == 0) { // White
        traverseNode->destVert->color = 1;   
        traverseNode->destVert->dist = adjListHeads[currVertIndex].destVert->dist + 1;
        traverseNode->destVert->parentId = adjListHeads[currVertIndex].destVert->index;
        que.push(traverseNode->destVert->index);
      }
      traverseNode = traverseNode->next;
    }
    adjListHeads[currVertIndex].destVert->color = 2 ;
  } 
};


int main () {

  Graph* gph = new Graph(5);
  gph->addEdge(0, 1);
  gph->addEdge(0, 4);
  gph->addEdge(1, 2);
  gph->addEdge(1, 3);
  gph->addEdge(1, 4);
  gph->addEdge(2, 3);
  gph->addEdge(3, 4);

  gph->printGraph();
  gph->bfs(0);
  gph->printGraph();
  
  
  //Queue que; 
  //que.push(gph->adjListHeads[3].destVert);
  //std::cout << que.pop()->index <<  que.pop()->index;
}

