#include <iostream>

struct Vert{
  int index;
  int initTime;
  int finishTime;
  int color;
  int parentId;
  Vert(){
    index = 0;
    initTime = 0;
    finishTime = 0;
    color = 0;
  }
};


struct AdjListNode{
  Vert* destVert;
  AdjListNode* next;
};


struct Graph{
  int             numVerts;
  AdjListNode*    adjList;
  int             time;
  
  Graph(int numVerts){
    this->numVerts = numVerts;
    this->time = time;
    adjList = new AdjListNode[numVerts];
    
    for (int i = 0; i < numVerts; i++){
      adjList[i].destVert = new Vert;
      adjList[i].destVert->parentId = i;
      adjList[i].destVert->index = i;
    }
  }

  void addEdge(int src, int dest){
    AdjListNode* newEdge = new AdjListNode;
    newEdge->destVert = adjList[dest].destVert;
    newEdge->next = adjList[src].next;
    adjList[src].next = newEdge;
  }
  
  void dfs_visit(int vertId){
    if (adjList[vertId].destVert->color == 0){
      adjList[vertId].destVert->color = 1; 
      time ++;
      adjList[vertId].destVert->initTime = time;
      AdjListNode* traverseNode = adjList[vertId].next;
      while (traverseNode != NULL){
        if (traverseNode->destVert->color == 0){
          traverseNode->destVert->parentId = vertId;
          dfs_visit(traverseNode->destVert->index);\
        }
        traverseNode = traverseNode->next;
      }
      adjList[vertId].destVert->color = 2;
      time++;
      adjList[vertId].destVert->finishTime = time;
    }
  }

  void printGraph(){
    for (int i=0; i < numVerts; i++){
      std::cout << "Vertex (" << adjList[i].destVert->index ;
      std::cout << ": " << adjList[i].destVert->initTime;
      std::cout << ", " << adjList[i].destVert->finishTime;
      std::cout << ", " << adjList[i].destVert->color;
      std::cout << ", " << adjList[i].destVert->parentId;
      std::cout << " )" << std::endl ;
      AdjListNode* traverseNode = adjList[i].next; 
      while (traverseNode != NULL){
        std::cout << " " << traverseNode->destVert->index;
        traverseNode = traverseNode->next;
      }
      std::cout << std::endl ;
    }
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
  
  for (int i = 0; i < gph->numVerts; i++){
    if(gph->adjList[i].destVert->color == 0){
      gph->dfs_visit(i);
    }
  }
  gph->printGraph();
  
}
