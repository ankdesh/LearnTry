#define N 100

int* func(int *a, int *b, int *c){
  for (int i = 0; i < N; i++){
    c[i] = a[i] * b[i];
  }
  return c;
}
