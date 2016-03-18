#include <iostream>

struct Stack{
  Stack(int N){
    maxSize = N;
    stackVal = new int[N];
    stackIndex = new int[N];
    top = 0;
  }

  void push(int x,int i){
    //std::cout << "Pushing " << x << std::endl;
    top ++;
    stackVal[top] = x;
    stackIndex[top] = i;
  }

  int pop(){
    top--;
    //std::cout << "Pop (" << stackIndex[top+1] << ", " << stackVal[top+1] << std::endl;
    return stackVal[top+1];
  } 

  int getTop(){
    return stackVal[top];
  }

  int getTopIndex(){
    return stackIndex[top];
  }

  int maxSize;
  int top;
  int* stackVal;
  int* stackIndex;

};


int main(){
  int N;
  std::cin >> N;
  Stack sp(N+1);

  int x;
  std::cin >> x;
  sp.push(x,0);
  int maxArea = 0;
 

  for (int i = 1; i < N; i++){
    std::cin >> x;
    if (x >= sp.getTop()){
      sp.push(x,i);
    }
    else{
      //int areaCurr = x; // Area using current and last larger num from stack
      //if (areaCurr > maxArea) maxArea = areaCurr;
      int topidx = sp.getTopIndex();
      int maxH = sp.pop();
      while ( x < sp.getTop() && sp.top != 0){
        int area = sp.getTop() * (topidx - sp.getTopIndex() + 1 );
        if (area > maxArea){
          maxArea = area;
        }
        sp.pop();
      }
      sp.push(x,i);
    }
  }
  
  int topidx ; // = sp.getTopIndex();
  if (sp.top !=0){  
    topidx = sp.getTopIndex();
    sp.pop();
  }
  
  while(sp.top != 0){
    int area = sp.getTop() * (topidx - sp.getTopIndex() + 1 );
    if (area > maxArea){
      maxArea = area;
    }
    sp.pop();
  }
 
  std::cout << maxArea;
}

