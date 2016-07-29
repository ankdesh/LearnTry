#include <iostream>

char *str = "(()()(";
int lenStr = 6;

int curr = 0;

int match(int level){
  if (level != 0 && curr == lenStr){
    std::cout << "Error" ;
  }
  while(curr < lenStr){
    if(str[curr] == '('){
      int openPos = curr;
      curr++;
      int closePos = match(level + 1);
      std::cout << "Pos: " << openPos << " matches with pos " << closePos 
                << "at level " << level << std::endl;
    }
    else if (str[curr] == ')'){
      curr ++;
      return curr-1;
    }
  }
}


int main(){
  match(0);
}
