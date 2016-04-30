#include<iostream>

int main(){

  int N;
  std::cin >> N;
  int* A = new int[N];
  int* B = new int[N];
  bool* isMarkedA = new bool[N];
  int count = 0;

  for (int i = 0; i < N; i++){
    std::cin >> A[i];
    isMarkedA[i] = false;
  }
  for (int j = 0; j < N; j++){
    std::cin >> B[j];
  }

  bool isfreeB = false;
  for (int i = 0; i < N; i ++)
  {
    bool foundBi = false;
    for (int j = 0; j < N; j++){
      if (B[i] == A[j] && isMarkedA[j] == false){
        isMarkedA[j] = true;
        count++;
        foundBi = true; 
        break;
      }  
    }
    if (foundBi == false){
      isfreeB = true;
    }
  }
  if (isfreeB == true){
    count ++;
  }
  else {
    count --;
  }
  std::cout << count;
}   
