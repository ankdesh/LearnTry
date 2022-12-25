/// 
/// @file   counterAbstract.h
/// @Author a.deshwal@samsung.com
/// @brief  Includes declararions of Abstract class for counters 
/// This file contains decalration of Abstract class for counters 
/// of different types which are used in different level of stream 
/// Comparision

#ifndef COUNTERABSTRACT_H_
#define COUNTERABSTRACT_H_

#include <string>

/// Abstract Counter class
class CounterAbstract{
  public:
    void update();
    virtual std::string resultAsString() const = 0;
 };

#endif
