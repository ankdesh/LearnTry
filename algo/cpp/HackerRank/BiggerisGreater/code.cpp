#include <iostream>


struct Heap{
  int N;
  char* heap;

  Heap(){
    heap = new char[100];
    N = 0;
  }
  
  void insert(char x){
    heap[N] = x;
    N++;
  }

  void heapify(int i){
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if (l < N && heap[l] > heap[largest]){
      largest = l;
    }
    
    if (r < N && heap[r] > heap[largest]){
      largest = r;
    }

    if (i != largest){
      int temp = heap[largest];
      heap[largest] = heap[i];
      heap[i] = temp;
      heapify(largest);
    }
  }

  void createHeap(){
    for (int i = N/2 + 1; i >= 0; i --){
      heapify(i);
    }
  }

  void sort(){
    int sz = N;
    for (int i = N-1; i >= 0; i--){
      char temp = heap[0];
      heap[0] = heap[i];
      heap[i] = temp;
      N--;
      heapify(0);
    }
    N = sz;
  }
};


int main(){
  int T;
  std::cin >> T;

  std::string w;
  std::cin.ignore(100,'\n');
  for (int t = 0; t < T; t++){
    //std::cin.clear();
    //std::cin.ignore( 1000, '\n' );
    std::getline(std::cin,w);

    int len = 0;
    while(w[len] != '\0'){
      len++;
    }

    //std::cout << w << std::endl;

    bool nonDec = true;
    for (int i = 0; i <= len - 2; i++){
      if (w[i] < w[i+1]){
        nonDec = false;
      }
    } 

    if (nonDec){
      std::cout << "no answer" << std::endl;
      continue;
    }

    Heap hp;

    int i = len - 1;
    while(i > 0 && w[i] <= w[i-1]){  
      hp.insert(w[i]);
      i--; len --;
    }

    hp.insert(w[i]);
    i--; len --;
    
    hp.createHeap();
    hp.sort();
    if(len > 0 && hp.N > 0){
      char pivot = w[len-1];
      int minGreaterThanPivotPos;
      for (int i = 0; i < hp.N ; i++){
        if (hp.heap[i]>pivot){
          minGreaterThanPivotPos = i;
          break;
        }
      }
      w[len-1] = hp.heap[minGreaterThanPivotPos];
      hp.heap[minGreaterThanPivotPos] = pivot;
      hp.createHeap();
      hp.sort();
    }
    for (int i = 0; i < len; i++){
      std::cout << w[i];
    }
    for (int i = 0; i < hp.N; i++){
      std::cout << hp.heap[i];
    }
    std::cout << std::endl;
  }
}
