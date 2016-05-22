#include <iostream>
#include <climits>

const int V = 9;
  
int w[V][V] =     {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                   {4, 0, 8, 0, 0, 0, 0, 11, 0},
                   {0, 8, 0, 7, 0, 4, 0, 0, 2},
                   {0, 0, 7, 0, 9, 14, 0, 0, 0},
                   {0, 0, 0, 9, 0, 10, 0, 0, 0},
                   {0, 0, 4, 0, 10, 0, 2, 0, 0},
                   {0, 0, 0, 14, 0, 2, 0, 1, 6},
                   {8, 11, 0, 0, 0, 0, 1, 0, 7},
                   {0, 0, 2, 0, 0, 0, 6, 7, 0}
                  };


int d[V];
int p[V];
bool visit[V]; 

int findMinVert(){
  int smallestVal = INT_MAX;
  int smallestIndex = -1;
  
  for (int i = 0; i < V; i++){
    if (visit[i] == false && d[i] < smallestVal){
      smallestVal = d[i];
      smallestIndex = i;
    }
  }

  return smallestIndex;
}

void dijkstra(){
  d[0] = 0;
  //p[0] = 0;
  //visit[0] = true;

  for (int i = 0; i < V; i++){
    int nextVert = findMinVert();
    // std::cout << ">>" << nextVert << std::endl;
    visit[nextVert] = true;
    for (int j = 1; j < V; j ++){
      if (w[nextVert][j] > 0
          && visit[j] == false
          && (d[nextVert] + w[nextVert][j] < d[j])){
            d[j] = d[nextVert] + w[nextVert][j];
            p[j] = nextVert;
      }
    }
  }
}


int main(){
  for (int i = 0; i < V; i++){
    d[i] = INT_MAX;
    p[i] = i;
    visit[i] = false;
  }
  dijkstra();
    
  for (int i = 0; i < V; i++){
    std::cout << i << ": " 
              << d[i] << " " << p[i]
              << std::endl;
  }
}
