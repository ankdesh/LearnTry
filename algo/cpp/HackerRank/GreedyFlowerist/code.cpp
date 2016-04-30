#include <iostream>

class Heap{
public:
  Heap(int len){
    N = len;
    A = new int[N];
    sortedA = new int[N];
  }
  
  void heapify(int i){
    int l = 2*i+1;
    int r = 2*i+2;

    int largest = i;
    if (l < N && A[l]>A[largest]){
      largest = l;
    }
    if (r < N && A[r]>A[largest]){
      largest = r;
    }

    if(i != largest){
      int temp = A[largest];
      A[largest] = A[i];
      A[i] = temp;
      heapify(largest);
    }
  }

  void createHeap()
  {
    for(int i = N/2+1; i >=0 ; i--){
      heapify(i);
    } 
  }

  void sort(){
    int origN = N;
    for (int i = N-1; i >= 0 ; i--){
      sortedA[origN-1 - i] = A[0];
      A[0] = A[N-1];
      N--;
      heapify(0);
    }
  }  
  
  int* A;
  int* sortedA;
  int N;
};


int main(){
  int N,K;
  std::cin >> N >> K;
  Heap heap(N);
  for (int i = 0; i < N; i++){
    std::cin >> heap.A[i];
  }
  heap.createHeap();
  heap.sort();
//  for (int i = 0; i < N; i++){
//    std::cout << heap.sortedA[i] << " ";
//  }

  int totalCost = 0;
  int floorNByK = N % K == 0? N/K : N/K + 1;
  for (int i = 0; i < floorNByK ; i++){
    for (int j = 0; j < K; j++){
      if(i*K+j < N){
        totalCost += ((1+i) * heap.sortedA[i*K + j]);
      }
    }
  }
  std::cout << totalCost;
}


