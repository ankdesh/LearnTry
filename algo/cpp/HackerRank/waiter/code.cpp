#include<iostream>


struct Stack{
  Stack(int maxVal){
    N = maxVal;
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

  int get(){
    return stack[top];
  }

  void freeStack(){
    delete stack;
  }

  int N;
  int top;
  int* stack;
};

int findNextPrime(){
  static int currPrime = 2;
  static bool firstTime = true;

  if (firstTime) {
    firstTime = false;
    return 2;
  }

  while(true){
    currPrime++;
    bool isPrime = true;
    for (int i = 2; i < currPrime/2 + 1; i++){
      if (currPrime % i == 0) {
        isPrime = false;
        break;
      }
    }
    if (isPrime){ 
      return currPrime;
    }
  }
}

int main(){
  int N, Q;
  std::cin >> N >> Q;

  //int* arr = new int[N];

  Stack* currSp = new Stack(N);

  currSp->top = N-1;
  for (int i = N-1; i >= 0; i--){
    int temp;
    std::cin >> temp;
    currSp->stack[i] = temp;
  }

  for (int i = 0; i < Q; i++)
  {
    int prime = findNextPrime();
    //std::cout << std::endl << prime;
    Stack* nextStack = new Stack(N);
    //Stack* divStack = new Stack(N);
    while(currSp->top != -1){
      int val = currSp->pop();
      //std::cout << val << " " << prime << std::endl;
      if (val % prime == 0){
        std::cout << val << std::endl;
      }
      else {
        nextStack->push(val);
      }
    }
    currSp->freeStack();
    currSp = nextStack;
    //while(divStack->top != -1){
    //  std::cout << divStack->pop() << std::endl;
    //}
  }
  for (int i = 0; i <= currSp->top; i++){
    int val = currSp->stack[i];
    std::cout << val << std::endl;
  }
}

