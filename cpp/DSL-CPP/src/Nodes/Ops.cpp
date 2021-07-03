#include "Ops.hpp"

bool isOpType(enums::NODE_TYPE nodeTy){
        if ( nodeTy==enums::NODE_TYPE::AddOp || 
             nodeTy==enums::NODE_TYPE::MultOp ){
            return true;                    
    }
    return false;
}
