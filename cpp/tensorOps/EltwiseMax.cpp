#include "tensor.hpp"
#include "utilities.hpp"
#include <string>
#include <algorithm>
#include <cassert>
#include <vector>
#include <utility>

template <typename T>
void applyMax(const T& inVal, T& outVal){
  outVal = std::max<T>(inVal, outVal);
}


template <typename DataType> 
Status eltwise_max (const std::vector<Tensor<DataType>>& input,  
                          Tensor<DataType>& output){

  assert (input.size() > 0);
  assert (input[0].dims.n == output.dims.n );  
  assert (input[0].dims.c == output.dims.c );
  assert (input[0].dims.h == output.dims.h );  
  assert (input[0].dims.w == output.dims.w );  

  // Copy input to output
  tensor_utils::tensorDeepCopy<DataType>(input[0], output);
    
  for (uint32_t t = 1; t < input.size() ; t++){
    tensor_utils::foreach_pixelInTensors<DataType>(input[t], output, applyMax<DataType>);
  }

}


int main(){

  Tensor<int8_t> tensor1;
  tensor1.precision_type = PrecisionType::INT8;
  tensor1.dims = {1, 10, 15, 20};
  tensor1.offset = 0;
  tensor1.data = new int8_t[10 * 15 *20]; // c * h * w
 
  Tensor<int8_t> tensor2;
  tensor2.precision_type = PrecisionType::INT8;
  tensor2.dims = {1, 10, 15, 20};
  tensor2.offset = 0;
  tensor2.data = new int8_t[10 * 15 *20]; // c * h * w

  Tensor<int8_t> tensor; // output
  tensor.precision_type = PrecisionType::INT8;
  tensor.dims = {1, 10, 15, 20};
  tensor.offset = 0;
  tensor.data = new int8_t[10 * 15 *20]; // c * h * w
  

  // Initialize Data
  for (uint32_t c = 0; c < 10; c ++){
    for (uint32_t h = 0; h < 15; h++){
      for (uint32_t w = 0; w < 20; w++){
        // First Tensor has alternative positive and negative values in channel
        tensor_utils::writeTensorVal<int8_t>(tensor1, 0, c, h, w, (c % 2 == 0? c:-1*c ));
        
        // Second Tensor have all zeros
        tensor_utils::writeTensorVal<int8_t>(tensor2, 0, c, h, w, 0);
        tensor_utils::writeTensorVal<int8_t>(tensor, 0, c, h, w, 0);
      }
    }
  }
 
  std::vector <Tensor<int8_t>> inpTensors;
  inpTensors.push_back(std::move(tensor1)); 
  inpTensors.push_back(std::move(tensor2)); 

  eltwise_max(inpTensors, tensor);
  
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 2, 0, 0))  << std::endl;

}

