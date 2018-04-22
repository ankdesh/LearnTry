#include "tensor.hpp"
#include "utilities.hpp"

template <typename DataType> 
Status crop(const Tensor<DataType>& input,  
                  Tensor<DataType>& output,
                  const uint32_t& start_axis,
                  const uint32_t& end_axis){

  // Copy input to output if not in place computation
  if (std::addressof(input) != std::addressof(output)){
    tensor_utils::tensorDeepCopy<DataType>(input, output);
  }

  uint32_t totalFlattenedDims = 1;
  
  if (start_axis <= 0 && end_axis >= 0){
    totalFlattenedDims *= input.dims.n;
    output.dims.n = 1;
  } 
  if (start_axis <= 1 && end_axis >= 1){
    totalFlattenedDims *= input.dims.c;
    output.dims.c = 1;
  } 
  if (start_axis <= 2 && end_axis >= 2){
    totalFlattenedDims *= input.dims.h;
    output.dims.h = 1;
  } 
  if (start_axis <= 3 && end_axis >= 3){
    totalFlattenedDims *= input.dims.w;
    output.dims.w = 1;
  } 

  switch (end_axis){
    case 0: output.dims.n = totalFlattenedDims; break;
    case 1: output.dims.c = totalFlattenedDims; break;
    case 2: output.dims.h = totalFlattenedDims; break;
    case 3: output.dims.w = totalFlattenedDims; break;
  };
}


int main(){

}

