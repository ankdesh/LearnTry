#include <iostream>


class Heap{
public:
  Heap(long long int size){
    N = size;
    heap = new long long int[N];
  }


  void heapify(long long int i){
    long long int l = 2 * i + 1;
    long long int r = 2 * i + 2;

    long long int smallest = i;
    if ( l < N -1 && heap[l] < heap[smallest]){
      smallest = l;
    }
    if ( r < N -1 && heap[r] < heap[smallest]){
      smallest = r;
    }
    if ( smallest != i ){
      long long int temp = heap[smallest];
      heap[smallest] = heap[i];
      heap[i] = temp;
      heapify(smallest);
    }
  }

  void sort(){
    for (int i = N/2 + 1; i >= 0; i--){
      heapify(i);
    }
     
    int origN = N;  
    for (long long int i = N-1; i >= 0 ; i--){
      long long int temp = heap[N-1];
      heap[N-1] = heap[0];
      heap[0] = temp;
      heapify(0);
      N--;
    }
    N = origN;
  }

  long long int* heap;
  int N;
};

int main(){
  int T,n,m;
  std::cin >> T;
  for (int p = 0 ; p < T ; p++){ 
    std::cin >> m >> n;
    Heap heapX(m-1);
    Heap heapY(n-1);
    for (int q = 0 ; q < m - 1; q++){
      std::cin >> heapX.heap[q];
    }
    for (int q = 0 ; q < n - 1; q++){
      std::cin >> heapY.heap[q];
    }
    heapX.sort();
    heapY.sort();

    int cx = 1;
    int cy = 1;
    int i = 0;
    int j = 0;
    long long int cost = 0;
    while(i < heapX.N && j < heapY.N){
      if (heapX.heap[i] >= heapY.heap[j]){
        cost += (heapX.heap[i] * cx);
        i++;
        cy++;
      } 
      else {
        cost += (heapY.heap[j] * cy);
        j++;
        cx++;
      }
    }
    while(i < heapX.N){
        cost += (heapX.heap[i] * cx);
        i++;
    }
    while(j < heapY.N){
        cost += (heapY.heap[j] * cy);
        j++;
    }
    long long int ans = (cost % (1000000000 + 7));
    std::cout << ans << std::endl;
  }
}

