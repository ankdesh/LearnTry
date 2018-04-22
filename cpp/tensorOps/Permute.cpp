#include "tensor.hpp"
#include "utilities.hpp"
#include <string>
#include <algorithm>
#include <cassert>
#include <memory>
#include <vector>

template <typename DataType> 
Status permute(const Tensor<DataType>& input,  
                     Tensor<DataType>& output,
                     const std::vector<uint32_t>& order,
                     const std::vector<uint32_t>& axis){

  // TODO Check loop extents 

  // Calculate extents for each loop
  //std::pair <uint32_t, uint32_t> extentN = 
  //                      (axis <= 0 ? std::make_pair (offset, output.dims.n):
  //                                  std::make_pair (uint32_t (0), output.dims.n));

  //std::pair <uint32_t, uint32_t> extentC = 
  //                      (axis <= 1 ? std::make_pair (offset, output.dims.c):
  //                                  std::make_pair (uint32_t (0), output.dims.c));


  //std::pair <uint32_t, uint32_t> extentH = 
  //                      (axis <= 2 ? std::make_pair (offset, output.dims.h):
  //                                  std::make_pair (uint32_t (0), output.dims.h));

  //std::pair <uint32_t, uint32_t> extentW = 
  //                      (axis <= 3 ? std::make_pair (offset, output.dims.w):
  //                                  std::make_pair (uint32_t (0), output.dims.w));

  for (int n = 0; n < input.dims.n; n++){
    for (int c = 0; c < input.dims.c; c++){
      for (int h = 0; h < input.dims.h; h++){
        for (int w = 0; w < input.dims.w; w++){
          DataType val = tensor_utils::readTensorVal<DataType>(input, n, c, h, w); // read from nchw 
          tensor_utils::writeTensorVal<DataType>(output, n, w, h, c, val); // write at nhwc
        }
      }
    }
  }
}


int main(){

  Tensor<int8_t> inTensor;
  inTensor.precision_type = PrecisionType::INT8;
  inTensor.dims = {1, 10, 15, 20};
  inTensor.offset = 0;
  inTensor.data = new int8_t[10 * 15 *20]; // c * h * w
 
  // Initialize Data
  for (uint32_t c = 0; c < 10; c ++){
    for (uint32_t h = 0; h < 15; h++){
      for (uint32_t w = 0; w < 20; w++){
        tensor_utils::writeTensorVal<int8_t>(inTensor, 0, c, h, w, c);
      }
    }
  }
  
  Tensor<int8_t> outTensor;
  outTensor.precision_type = PrecisionType::INT8;
  outTensor.dims = {1, 10, 5, 10};
  outTensor.offset = 0;
  outTensor.data = new int8_t[10 * 5 * 10]; // c * h * w
 
  // Initialize Data
  for (uint32_t c = 0; c < 10; c ++){
    for (uint32_t h = 0; h < 5; h++){
      for (uint32_t w = 0; w < 10; w++){
        tensor_utils::writeTensorVal<int8_t>(outTensor, 0, c, h, w, 0);
      }
    }
  }


  std::cout << std::to_string(tensor_utils::readTensorVal(inTensor, 0, 0, 0, 1))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(inTensor, 0, 0, 0, 2))  << std::endl;

  permute<int8_t>(inTensor, outTensor, {2}, {2}); 
  
  std::cout << std::to_string(tensor_utils::readTensorVal(outTensor, 0, 0, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(outTensor, 0, 0, 0, 1))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(outTensor, 0, 0, 0, 2))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(outTensor, 0, 0, 0, 3))  << std::endl;

}

