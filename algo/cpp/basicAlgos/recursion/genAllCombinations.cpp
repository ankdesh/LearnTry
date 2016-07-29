#include<iostream>

const int N = 4; 
const int K = 2;

int arr[N];

void printComb(){
  for (int i = 0; i < N; i++){
    std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
}

void genComb(int k){
  if (k == K){
    printComb();   
    return;
  }
  arr[k] = 0;
  genComb(k+1);
  arr[k] = 1;
  genComb(k+1);
}


int main(){
  for (int i = 0; i < N; i++){
    arr[i] = 0;
  }
  genComb(0);

}
