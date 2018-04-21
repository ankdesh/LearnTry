#ifndef __TENSOR_H__ 
#define __TENSOR_H__ 

#include <cstdint>
#include <iostream>

enum class PrecisionType{
  FP32 = 0,
  FP16 = 1,
  INT8 = 2
};

typedef struct Dim4{
  uint32_t n;
  uint32_t c;
  uint32_t h;
  uint32_t w;
} Dim4;

typedef struct Dim2{
  uint32_t h;
  uint32_t w;
} Dim2; 

template<typename DataType>
struct Tensor {
  PrecisionType precision_type;
  Dim4 dims;
  float scale;
  uint32_t offset;
  DataType* data;
};  

enum class Status {
  SUCCESS = 0,
  FAIL = 1
};

#endif
