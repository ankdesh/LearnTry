#define N 100
typedef float float16 __attribute__((ext_vector_type(16)));

int* func(float16 *a, float16 *b, float16 *c){
  for (int i = 0; i < N; i++){
    c[i] = a[i] * b[i];
  }
  return c;
}
