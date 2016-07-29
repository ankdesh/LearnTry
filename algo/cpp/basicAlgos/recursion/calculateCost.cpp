#include <iostream>


char* str = "(()()())()";
int strLen = 10;

int curr = 0;
bool matches = true;

bool isMatching(char first, char second){
  if ( (first == '(' && second == ')') 
        || (first == '{' && second == '}') 
        || (first == '[' && second == ']')){
        return true;
      }
   return false;
} 

bool isBegin(char ch){
  if ( ch == '(' || ch == '{' || ch == '[' ){
    return true;
  }
  return false;
}

struct RetVal {
  int val;
  char ch;
};

RetVal match(int level){
  if (level != 0 && curr == strLen){
    matches = false;  
  }
  int val = 0;
  while (curr < strLen){
    if (isBegin(str[curr])){
      char currChar = str[curr];
      curr++;
      RetVal ret = match(level+1);
      val += ret.val * 2;
      std::cout << "CurrChar: " << currChar 
                << " RetChar =" << ret.ch << std::endl;
      matches = matches && isMatching(currChar, ret.ch);
    }
    else {
      char currChar = str[curr];
      int retval;
      if (isMatching(str[curr-1], currChar)){
         retval = 1;
      }
      else {
        retval = val;
      }
      curr ++;
      RetVal r; 
      r.ch = currChar;
      r.val = retval;
      return r;
    }
  }
  RetVal r; 
  r.ch = '*';
  r.val = val;
  return r;
}

int main(){
  RetVal r = match(0);
  std::cout << r.val;
  //if (matches) {
  //  std::cout << "Matches";
  //}
  //else {
  //  std::cout << "Does not match";
  //}
}
