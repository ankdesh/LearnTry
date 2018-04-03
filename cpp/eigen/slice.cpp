#include <iostream>
#include <Eigen/Core>
#include <unsupported/Eigen/CXX11/Tensor>

using namespace std;

template <typename Dtype>
Eigen::Tensor <Dtype, 4> Crop( Eigen::Tensor <Dtype, 4> inTensor, Dtype cropAxesOffset, int axis){

  Eigen::array<Dtype,4> offsetsVec;
  offsetsVec.set(cropAxesOffset);

  return Crop(inTensor, offsetsVec, axis);
}

template <typename Dtype>
Eigen::Tensor <Dtype, 4> Crop( Eigen::Tensor <Dtype, 4> inTensor, Eigen::array<Dtype,4> cropAxesOffset, int axis){

  Eigen::array<int, 4> offsets({0,0,0,0});
  Eigen::array<int, 4> extents({0,0,0,0});

  for (int i = axis; i < 4; i ++){
    offsets[i] = cropAxesOffset[i];
    std::cout << offsets[i] <<" << ";
  }
  cout << "\n";

  for (int i = 0; i < 4; i++){
    extents[i] = inTensor.dimension(i) - offsets[i] ;
    std::cout << extents[i] <<" <<< ";
  }

  Eigen::Tensor <Dtype, 4> outTensor = inTensor.slice(offsets, extents);

  return outTensor;
}
  
main(){

  Eigen::Tensor<int, 4> a(1, 1, 4, 3);
  a.setValues({{{{0, 100, 200}, {300, 400, 500},
               {600, 700, 800}, {900, 1000, 1100}}}});
  std::cout << a;
  Eigen::array<int, 4> offsets = {2, 2, 2, 1};
  //Eigen::array<int, 2> extents = {2, 2};
  //Eigen::Tensor<int, 2> slice = a.slice(offsets, extents);
  //cout << "slice" << endl << slice << endl;
  //for (int i= 0; i < 4; i++)
  //std::cout << a.dimension(i) << " ";
  std::cout << Crop<int>(a, offsets, 2);
}

