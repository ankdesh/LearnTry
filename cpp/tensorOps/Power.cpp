#include "tensor.hpp"
#include "utilities.hpp"
#include <string>
#include <algorithm>
#include <cassert>
#include <memory>

template <typename T>
struct ApplyPower{

  ApplyPower(T power, T scale, T shift):
    power_(power),
    scale_(scale),
    shift_(shift){
  }

  T power_;
  T scale_;
  T shift_;

  void operator () (T& inVal, T& outVal){
    outVal = T(std::pow( double(scale_ * inVal + shift_), power_));
  }
};


template <typename DataType> 
Status power(const Tensor<DataType>& input,  
                   Tensor<DataType>& output,
                   const DataType& power,
                   const DataType& scale,
                   const DataType& shift){

  // Copy input to output if not in place computation
  if (std::addressof(input) != std::addressof(output)){
    tensor_utils::tensorDeepCopy<DataType>(input, output);
  }

  ApplyPower<DataType> applypower(power, scale, shift);
  tensor_utils::foreach_pixelInTensors<DataType>(input, output, applypower);

}


int main(){

  Tensor<int8_t> tensor;
  tensor.precision_type = PrecisionType::INT8;
  tensor.dims = {1, 10, 15, 20};
  tensor.offset = 0;
  tensor.data = new int8_t[10 * 15 *20]; // c * h * w
 
  // Initialize Data
  for (uint32_t c = 0; c < 10; c ++){
    for (uint32_t h = 0; h < 15; h++){
      for (uint32_t w = 0; w < 20; w++){
        tensor_utils::writeTensorVal<int8_t>(tensor, 0, c, h, w, (c % 2 == 0? c:-1*c ));
      }
    }
  }
  
  Tensor<int8_t> slope;
  slope.precision_type = PrecisionType::INT8;
  slope.dims = {1, 10, 1, 1};
  slope.offset = 0;
  slope.data = new int8_t[10]; // c 
 
  // Initialize Data
  for (uint32_t c = 0; c < 10; c ++){
    tensor_utils::writeTensorVal<int8_t>(slope, 0, c, 0, 0, c * 100 );
  }


  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 2, 0, 0))  << std::endl;

  power<int8_t>(tensor, tensor, 2, 2, 2);
  
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 2, 0, 0))  << std::endl;

}

