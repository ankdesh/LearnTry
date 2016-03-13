#include<iostream>

//struct QNode{
//  int val;
//  QNode next*;
//};
//
//struct Queue{
//  QNode* q;
//  
//  push(int x){
//    Qnode* newNode = new Qnode;
//    newNode->val = 


struct Heap{
  Heap(int N){
    heap = new int[N];
    maxLen = N;
    len = 0;
  }


  void heapify(int i){
    int l = 2*i+1; 
    int r = 2*i+2;
    
    int largest = i;
    if (heap[r] > heap[largest] && r < len){
      largest = r;
    }
    if (heap[l] > heap[largest] && l < len){
      largest = l;
    }
    if(i != largest){
      int temp = heap[i];
      heap[i] = heap[largest];
      heap[largest] = temp;
      heapify(largest);
    }
  }
    
  void insert(int x){
    heap[len] = x;
    int i = len;
    len++;
    while(i > 0){
      int p = (i-1)/2;
      if (heap[p] < heap[i]){
        int temp = heap[p];
        heap[p] = heap[i];
        heap[i] = temp;
      }
      else{
        break;
      }
      i = p;
    }
  }

  int max(){
    return heap[0];
  }

  int findPos(int x){
    //int l = 2*i+1;
    //int r = 2*r+2;
  
    //int lpos, rpos;

    //if (heap[i] == x){
    //  return x;
    //}
    //if (l < len && heap[l] < x){
    //  lpos = findPos(x,l);
    //}
    //if (r < len && heap[r] < x){
    //  rpos = findPos(x,r);
    //}
    //if (
    for(int i = 0; i < len; i++){
      if(heap[i] == x) return i;
    }
  }

  void del(int x){
    int pos = findPos(x);
    heap[pos] = heap[len-1];
    len--;
    heapify(pos);
  }

  int* heap;
  int len;
  int maxLen;
};

struct Stack{
  Stack(int N){
    stack = new int[N];
    maxLen = N;
    len = 0;
  }

  void push(int x){
    stack[len] = x;
    len++;
  }

  int pop(){
    int retVal = stack[len-1];
    len--;
    return retVal;

  }

  int maxLen;
  int* stack;
  int len;
};



int main(){
  int N;
  std::cin >> N;
  Heap heap(N);
  Stack stack(N);

  int command;
  for (int i=0; i < N; i++){
    std::cin >> command;
    if (command == 1){
      int val;
      std::cin >> val;
      heap.insert(val);
      stack.push(val);
    }
    else if (command == 2){
      int max = stack.pop();
      heap.del(max);
    }
    else {
      std::cout << heap.max() << std::endl;
    }
  }
}


