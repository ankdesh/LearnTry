#include "tensor.hpp"
#include "utilities.hpp"
#include <string>
#include <algorithm>
#include <cassert>
#include <memory>

template <typename DataType> 
Status crop(const Tensor<DataType>& input,  
                  Tensor<DataType>& output,
                  const uint32_t& offset,
                  const uint32_t& axis){

  // TODO Check loop extents 

  // Calculate extents for each loop
  std::pair <uint32_t, uint32_t> extentN = 
                        (axis <= 0 ? std::make_pair (offset, output.dims.n):
                                    std::make_pair (uint32_t (0), output.dims.n));

  std::pair <uint32_t, uint32_t> extentC = 
                        (axis <= 1 ? std::make_pair (offset, output.dims.c):
                                    std::make_pair (uint32_t (0), output.dims.c));


  std::pair <uint32_t, uint32_t> extentH = 
                        (axis <= 2 ? std::make_pair (offset, output.dims.h):
                                    std::make_pair (uint32_t (0), output.dims.h));

  std::pair <uint32_t, uint32_t> extentW = 
                        (axis <= 3 ? std::make_pair (offset, output.dims.w):
                                    std::make_pair (uint32_t (0), output.dims.w));

  for (uint32_t n = extentN.first , no = 0; n < extentN.second; n++, no++){
    for (uint32_t c = extentC.first , co = 0; c < extentC.second; c++, co++){
      for (uint32_t h = extentH.first , ho = 0; h < extentH.second; h++, ho++){
        for (uint32_t w = extentW.first , wo = 0; w < extentW.second; w++, wo++){
          DataType val = tensor_utils::readTensorVal<DataType>(input, n, c, h, w);
          tensor_utils::writeTensorVal<DataType>(output, no, co, ho, wo, val);
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
        tensor_utils::writeTensorVal<int8_t>(inTensor, 0, c, h, w, (c % 2 == 0? c:-1*c ));
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


  std::cout << std::to_string(tensor_utils::readTensorVal(inTensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(inTensor, 0, 2, 0, 0))  << std::endl;

  // Crop with offset =2, only for H,W axis
  crop<int8_t>(inTensor, outTensor, 2, 2); 
  
  std::cout << std::to_string(tensor_utils::readTensorVal(outTensor, 0, 1, 0, 0))  << std::endl;
  std::cout << std::to_string(tensor_utils::readTensorVal(outTensor, 0, 2, 0, 0))  << std::endl;

}

