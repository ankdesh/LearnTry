#ifndef __UTILITIES_H__ 
#define __UTILITIES_H__ 

#include "tensor.hpp"
#include <functional>
#include <cassert>

namespace tensor_utils{

template<typename T>
T readTensorVal (const Tensor<T>& tensor, 
                 uint32_t n, 
                 uint32_t c, 
                 uint32_t h, 
                 uint32_t w){
  uint32_t loc =  n * tensor.dims.c * tensor.dims.h * tensor.dims.w
                + c * tensor.dims.h * tensor.dims.w 
                + h * tensor.dims.w 
                + w;

  return tensor.data[loc];
}

template<typename T>
void writeTensorVal (Tensor<T>& tensor, 
                     uint32_t n, 
                     uint32_t c, 
                     uint32_t h, 
                     uint32_t w, 
                     T val){
  uint32_t loc =  n * tensor.dims.c * tensor.dims.h * tensor.dims.w
                + c * tensor.dims.h * tensor.dims.w 
                + h * tensor.dims.w 
                + w;

  tensor.data[loc] = val;
}

template<typename T>
void tensorDeepCopy (const Tensor<T>& input, 
                           Tensor<T>& output){

  assert (input.dims.n == output.dims.n); 
  assert (input.dims.c == output.dims.c); 
  assert (input.dims.h == output.dims.h); 
  assert (input.dims.w == output.dims.w); 
  
  for (int n = 0; n < input.dims.n; n++){
    for (int c = 0; c < input.dims.c; c++){
      for (int h = 0; h < input.dims.h; h++){
        for (int w = 0; w < input.dims.w; w++){
          T val = readTensorVal<T>(input, n, c, h, w);
          writeTensorVal<T>(output, n, c, h, w, val);
        }
      }
    }
  }

}


template <typename T>
  void foreach_pixelInChannel(Tensor<T>& tensor, uint32_t channel, std::function<void(T&)> expr){
  
  uint64_t startIdx = tensor.offset + channel * tensor.dims.h * tensor.dims.w;
  uint64_t size = tensor.dims.h * tensor.dims.w;

  for (uint64_t i = startIdx; i < startIdx + size; i++){
    expr(tensor.data[i]);
  }
}

}
#endif
