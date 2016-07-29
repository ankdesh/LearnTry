#include <iostream>


char* str = "[{(()(){})}]";
int strLen = 12;

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


char match(int level){
  if (level != 0 && curr == strLen){
    matches = false;  
  }
  while (curr < strLen){
    if (isBegin(str[curr])){
      char currChar = str[curr];
      curr++;
      char retChar = match(level+1);
      std::cout << "CurrChar: " << currChar 
                << " RetChar =" << retChar << std::endl;
      matches = matches && isMatching(currChar, retChar);
    }
    else {
      char currChar = str[curr];
      curr++;
      return currChar;
    }
  }
}

int main(){
  match(0);
  if (matches) {
    std::cout << "Matches";
  }
  else {
    std::cout << "Does not match";
  }

}
