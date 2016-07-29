#include <iostream>

const int N = 4;
const int K = 2;

int arr[N];

void printComb(){
  for (int i = 0; i < N; i++){
    std::cout << arr[i];
  }
  std::cout << std::endl;
}

void genKComb(int level, int k){
  if (k == K){
    printComb();
    return;
  }
  if (level == N){
    return;
  } 

  arr[level] = 1;
  genKComb(level + 1, k + 1);
  arr[level] = 0;
  genKComb(level + 1, k);
}



int main(){
  for(int i = 0; i < N; i++){
    arr[i] = 0;
  }
  genKComb(0,0);
}
