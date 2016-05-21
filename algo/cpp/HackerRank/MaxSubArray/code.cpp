#include <iostream>
#include <climits>

int* arr;
bool* present;
int N;

int maxVal = 0;

bool isContigous(){
  bool transToOne = false;
  for (int i = 0; i < N; i++){
    if ((i == 0 && present[i] == true) 
          || ( i != 0 && present[i] == true && present[i-1] == false)){
      if (transToOne == true) {
        return false;
      }
      else {
        transToOne = true;
      }
    }
  } 
  return true;
}

bool allNeg(){
  int biggest = -INT_MAX;
  for (int i = 0; i < N; i++){
    if (arr[i] > 0){
      return false;
    }
    if (arr[i] > biggest){
      biggest = arr[i];
    }
  }
  maxVal = biggest;
  return true;
}

bool allPos(){
  int sum = 0;
  for (int i = 0; i < N; i++){
    if (arr[i] < 0){
      return false;
    }
    sum += arr[i];
  }
  maxVal = sum;
  return true;
}

void permute(int l){
  if (l == N){
    if (isContigous()){
      int sum = 0;
      for (int i = 0 ; i < N ; i++){
        if (present[i])
          sum += arr[i];
      }

      if (sum > maxVal){
        maxVal = sum;
      }
      //for (int i = 0; i < N; i++){
      //  std::cout << present[i] << " ";
      //}
      //std::cout << std::endl;
    }
    return;
  }
    present[l] = false;
    permute(l+1);
    present[l] = true;
    permute(l+1);
}

int main(){
  int T;
  std::cin >> T;

  for (int t = 0; t < T; t++){
    std::cin >> N;
    arr = new int[N];
    present = new bool[N];
    for (int i = 0; i < N; i++){
      std::cin >> arr[i];
      present[i] = false;
    }
    if (allNeg())
      std::cout << maxVal << " " << maxVal << std::endl;
    else if (allPos()){
      std::cout << maxVal << " " << maxVal << std::endl;
    }
    else {
      permute(0); 
  
      int sum = 0;
      for(int i = 0; i < N ;i++){
        if (arr[i] > 0)
          sum += arr[i];
      }
      std::cout << maxVal << " " << sum << std::endl;
    }
  }
}
