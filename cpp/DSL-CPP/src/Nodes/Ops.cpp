#include "Ops.hpp"

bool isOpType(enums::NODE_TYPE nodeTy){
        if ( nodeTy==enums::NODE_TYPE::AddOp || 
             nodeTy==enums::NODE_TYPE::MultOp ||
             nodeTy==enums::NODE_TYPE::IndexOp ){
            return true;                    
    }
    return false;
}
