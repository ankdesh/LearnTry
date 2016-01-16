#include <iostream>
#include <fstream>

int arr[100000];
int len;

int a[] = {2,3,5,4};

void init();

void merge(int A[], int l, int m, int r){
  int *left, *right;
  left = new  (std::nothrow) int[m-l+1];
  right = new (std::nothrow) int[r-m];

  if(left == 0 || right == 0){
    std::cout << "Error" ;
    return;
  }

  std::cout << ">>> " << l << " " << m << " " << r << std::endl;
//  std::cout << "### " << m-l << " " << r-m << " " << std::endl;

  for (int i=0; i<m-l+1; i++)
    left[i] = A[i+l];
  for (int j=0; j<r-m; j++)
    right[j] = A[j+m+1];

  int curr_i = 0;
  int curr_j = 0;
  
  for (int i = 0; i < 4; i++)
    std::cout <<" " << a[i];
  std::cout << std::endl;

  for(int k=l; k < r+1; k++){
    if(curr_i == m-l+1){
      A[k] = right[curr_j];
      curr_j++;
    }
    else if (curr_j == r-m){
      A[k] = left[curr_i];
      curr_i++;
    }
    else if(left[curr_i] < right[curr_j]){
      A[k] = left[curr_i];
      curr_i++;
    }
    else{
      A[k] = right[curr_j];
      curr_j++;
    }
  }
  for (int i = 0; i < 4; i++)
    std::cout <<" " << a[i];
  std::cout << std::endl;
//  std::cout << "(" << m-l+1 << "," << r-m << ") -> ";
//  std::cout << "(" << curr_i << "," << curr_j << ")" << std::endl;
  delete[] left;
  delete[] right;
} 

void mergesort(int p, int r){
  if (p < r){
    int q = (p+r)/2;
    mergesort(p, q);
    mergesort(q+1,r);
    merge(arr, p, q, r); 
  }
}

int main(){
  init();
  mergesort(0, len/100 - 1);

//  mergesort(0, 3);
//  for (int i = 0; i < 4; i++)
//    std::cout <<" " << a[i];

  for (int i = 0; i < len/100; i++)
    std::cout << "  " << arr[i];
  std::cout << "\nLen " << len;

}

void init(){
  std::fstream inFile("data/100000randInts.txt");
  int a,counter = 0;
  while(inFile >> a){
    arr[counter] = a;
    counter++;
  } 
  len = counter;
}
