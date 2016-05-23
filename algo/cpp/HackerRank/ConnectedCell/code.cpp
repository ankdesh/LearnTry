#include <iostream>

int maxCells = 0;

struct AdjNode{
  int dest;
  AdjNode* next; 
};

struct Graph{
  int* color;
  int* startTime;
  int* endTime;
  int time;
  AdjNode* adjList;
  int countEachDfs;  

  int N;

  Graph(int numVert){
    N = numVert;
    countEachDfs = 0;
    time = 0;
    color = new int[N];
    startTime = new int[N];
    endTime = new int[N];
    adjList = new AdjNode[N];
    
    for(int i = 0; i < N; i++){
      color[i] = 0;
      startTime[i] = 0;
      endTime[i] = 0;
      adjList[i].dest = -1;
      adjList[i].next = NULL;
    }
  }
  
  void addEdge(int x, int y){
    AdjNode* newNode = new AdjNode;
    newNode->dest = y;
    newNode->next = adjList[x].next;
    adjList[x].next = newNode;
  }

  void dfs(int vert){
    color[vert] = 1;
    countEachDfs ++;
    startTime[vert] = time;
    time++;
    AdjNode* currNode = adjList[vert].next;
      
    while(currNode != NULL){
      if (color[currNode->dest] == 0){
        dfs(currNode->dest);
      }
      currNode = currNode->next;
    }
    endTime[vert] = time;
    color[vert] = 2;
    time++;
  }
};


int main1(){ // Using Graph DS
  int r,c;
  std::cin >> r >> c;

  int** arr = new int*[r];
  for(int i = 0; i < r; i++){
    arr[i] = new int[c];
  }

  for (int i = 0; i < r ; i++)
    for(int j = 0; j < c; j++){
      std::cin >> arr[i][j]; 
  }

  Graph gph(r*c);

  for (int i = 0; i < r ; i++)
    for(int j = 0; j < c; j++){
      if (arr[i][j] == 1){
        if (i - 1 >= 0 && j - 1 >= 0 && arr[i-1][j-1] == 1){
          gph.addEdge(i*c + j, (i-1)*c + (j-1));
        }
        if (i - 1 >= 0 && j >= 0 && arr[i-1][j] == 1){
          gph.addEdge(i*c + j, (i-1)*c + (j));
        }
        if (i - 1 >= 0 && j + 1 < c && arr[i-1][j+1] == 1){
          gph.addEdge(i*c + j, (i-1)*c + (j+1));
        }
        if (i >= 0 && j - 1 >= 0 && arr[i][j-1] == 1){
          gph.addEdge(i*c + j, (i)*c + (j-1));
        }
        if (i >= 0 && j + 1 < c && arr[i][j+1] == 1){
          gph.addEdge(i*c + j, (i)*c + (j+1));
        }
        if (i + 1 < r && j - 1 >= 0 && arr[i+1][j-1] == 1){
          gph.addEdge(i*c + j, (i+1)*c + (j-1));
        }
        if (i + 1 < r && j >= 0 && arr[i+1][j] == 1){
          gph.addEdge(i*c + j, (i+1)*c + (j));
        }
        if (i + 1 < r && j + 1 < c && arr[i+1][j+1] == 1){
          gph.addEdge(i*c + j, (i+1)*c + (j+1));
        }
      }
    }

    for(int i = 0; i < r ; i++)
      for(int j = 0; j < c; j++){
      
      gph.countEachDfs = 0;
      if (arr[i][j] == 1 && gph.color[i*c+j] == 0){
        gph.dfs(i*c+j);
        if (gph.countEachDfs > maxCells){
          maxCells = gph.countEachDfs;
        }
      }
    }

    std::cout << maxCells;
}

int** arr;
bool** visit;
int currCells; 
int r,c;

void dfs(int i, int j){
  if (visit[i][j] == false){
    currCells ++;
    visit[i][j] = true;
    if (i - 1 >= 0 && j - 1 >= 0 && arr[i-1][j-1] == 1){
      dfs(i-1, j-1);
    }
    if (i - 1 >= 0 && j >= 0 && arr[i-1][j] == 1){
      dfs(i-1, j);
    }
    if (i - 1 >= 0 && j + 1 < c && arr[i-1][j+1] == 1){
      dfs(i-1, j+1);
    }
    if (i >= 0 && j - 1 >= 0 && arr[i][j-1] == 1){
      dfs(i, j-1);
    }
    if (i >= 0 && j + 1 < c && arr[i][j+1] == 1){
      dfs(i, j+1);
    }
    if (i + 1 < r && j - 1 >= 0 && arr[i+1][j-1] == 1){
      dfs(i+1, j-1);
    }
    if (i + 1 < r && j >= 0 && arr[i+1][j] == 1){
      dfs(i+1, j);
    }
    if (i + 1 < r && j + 1 < c && arr[i+1][j+1] == 1){
      dfs(i+1, j+1);
    }
  }
}


int main(){ // Direct DFS 
  std::cin >> r >> c;

  arr = new int*[r];
  visit = new bool*[r];
  for(int i = 0; i < r; i++){
    arr[i] = new int[c];
    visit[i] = new bool[c];
  }

  for (int i = 0; i < r ; i++)
    for(int j = 0; j < c; j++){
      std::cin >> arr[i][j]; 
      visit[i][j] = false;
  }

    for(int i = 0; i < r ; i++)
      for(int j = 0; j < c; j++){
        currCells = 0;
        if (arr[i][j] == 1 && visit[i][j] == false){
          dfs(i,j);
          if (currCells > maxCells){
            maxCells = currCells;
          }
        }
    }

    std::cout << maxCells;
}
