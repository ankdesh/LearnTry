#include "tensor.hpp"
#include "utilities.hpp"
#include <string>
#include <algorithm>
#include <cassert>

template <typename T>
struct ApplyPrelu{

  ApplyPrelu(T slope){
    slope_ = slope;
  }

  uint32_t slope_;

  void operator () (T& val){
    // std::cout << std::to_string(val) << " " << slope_ << std::endl;
    val = std::max<T>(0,val) + slope_ * std::min<T>(0, val);
    //std::cout << std::to_string(val) << " " << slope_ << std::endl;
  }
};


template <typename DataType> 
Status activation_prelu(const Tensor<DataType>& input,  
                              Tensor<DataType>& output,
                        const Tensor<DataType>& slope,
                        const bool& channel_shared){

  // TODO Check about channel_shared once clarified in the func prototype doc
  
  assert (slope.dims.n == input.dims.n);  
  assert (slope.dims.c == input.dims.c);
  assert (slope.dims.h == 1);  
  assert (slope.dims.w == 1);  

  // Copy input to output
  tensor_utils::tensorDeepCopy<DataType>(input, output);

  for (uint32_t c = 0; c < slope.dims.c; c++){
    DataType slopeVal = tensor_utils::readTensorVal<DataType>(slope, 0, c, 0, 0);
    ApplyPrelu<DataType> applyPrelu(slopeVal);
    
    tensor_utils::foreach_pixelInChannel<DataType>(output, c, applyPrelu);
  }

}


int main(){

  ApplyPrelu<int8_t> applyPrelu(100);

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

  //tensor_utils::foreach_pixelInChannel<int8_t>(tensor, 2, applyPrelu);  
  //std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 2, 0, 0))  << std::endl;
  //
  //tensor_utils::foreach_pixelInChannel<int8_t>(tensor, 1, applyPrelu);  
  //std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 1, 0, 0))  << std::endl;

  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 2, 0, 0))  << std::endl;

  activation_prelu(tensor, tensor, slope, false);
  
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(tensor, 0, 2, 0, 0))  << std::endl;

}

