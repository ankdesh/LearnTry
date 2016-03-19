#include<iostream>

struct Stack{
  Stack(int maxSize){
    N = maxSize;  
    stack = new int[N];
    top = -1;
  }

  void push(int x){
    top++;
    stack[top] = x;
  }
  
  int pop(){
    top --;
    return stack[top+1];
  }

  int getTop(){
    return stack[top];
  }

  int* stack;
  int N;
  int top;
};


int main(){
  int N;
  std::cin >> N;
  
  Stack* sp = new Stack(N);
  int x;
  std::cin >> x;
  
  int curMin = x;
  int maxCount =1;
  int currCount =1;
    
  for (int i=1; i < N; i++){
    int lastx = x;
    std::cin >> x;

    if (x >= lastx){
      currCount = 1;
    }
    else if (x < lastx && x > curMin){
      currCount++; if(currCount > maxCount) {maxCount = currCount;}
    }
    else if (x < lastx && x < curMin){
      curMin = x;
    }
  }
  std::cout << maxCount;

//  sp->push(x);
//
//  int maxCount = 0;
//
//  for (int i=1; i < N; i++){
//  int leftx = x;
//  std::cin >> x;
//    if (x <= sp->getTop() && ){
//      sp->push(x);
//    }
//    else {
//      if (count > maxCount){
//        maxCount = count;
//      }
//    }
//  }
//
//  std::cout << maxCount;
}
