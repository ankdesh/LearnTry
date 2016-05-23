#include<iostream>

int** board;
int N,M;
long long int numBoards = 0;


bool isValid(){

 for (int i = 0; i < N; i++){
    for (int j = 0 ;j < M; j++){
      if (board[i][j] == 1){
        for (int k = i-1; k >= 0; k --){
          if(board[k][j] == 1){
            return false;
          }
          else if (board[k][j] == 2){
            break;
          }
        }
        for (int k = i+1; k < N ; k++){
          if(board[k][j] == 1){
            return false;
          }
          else if (board[k][j] == 2){
            break;
          }
        }
        for (int l = j-1; l >= 0 ; l--){
          if(board[i][l] == 1){
            return false;
          }
          else if (board[i][l] == 2){
            break;
          }
        }
        for (int l = j+1; l < M ; l++){
          if(board[i][l] == 1){
            return false;
          }
          else if (board[i][l] == 2){
            break;
          }
        }
        
        for (int l = j-1, k = i-1 ; l >= 0 && k >=0 ; l--, k--){
          if(board[k][l] == 1){
            return false;
          }
          else if (board[k][l] == 2){
            break;
          }
        }
        for (int l = j+1, k = i-1 ; l < M && k >=0 ; l++, k--){
          if(board[k][l] == 1){
            return false;
          }
          else if (board[k][l] == 2){
            break;
          }
        }
        for (int l = j-1, k = i+1 ; l >= 0 && k < N ; l--, k++){
          if(board[k][l] == 1){
            return false;
          }
          else if (board[k][l] == 2){
            break;
          }
        }
        for (int l = j+1, k = i+1 ; l < M && k < N ; l++, k++){
          if(board[k][l] == 1){
            return false;
          }
          else if (board[k][l] == 2){
            break;
          }
        }

      }
    }
  }
  return true;
}

void printBoard(){
  for (int i = 0; i < N; i++){
    for (int j = 0 ;j < M; j++){
      std::cout << board[i][j] << " ";
    }
    //std::cout << std::endl;
  }
}

void tryAll(int x){
  if (x == M*N ){
    bool isV = isValid();
    if (isV){
      //printBoard();
      //std::cout << std::endl;
      numBoards++;
    }
    return;
  }
    int c = x%M;
    int r = x/M;
    //std::cout << "(" << r << "," << c << ")" <<std::endl;
    if (board[r][c] != 2){
        board[r][c] = 1;
      if (isValid()){
        tryAll(x+1);
      }
      board[r][c] = 0;
      tryAll(x+1);
    }
    else {
      tryAll(x+1);
    }
}




int main(){
  int T;
  std::cin >> T;

  for (int t = 0; t < T; t++){
    board = NULL;
    numBoards = 0;
    std::cin >> N >> M;
    board = new int*[N];
    for (int i = 0; i < N; i++){
      board[i] = new int[M];
    }

    for (int i = 0; i < N; i++){
      for (int j = 0 ;j < M; j++){
        char ch;
        std::cin >> ch;
        if (ch == '.'){
          board[i][j] = 0;
        }
        else if (ch == '#'){
          board[i][j] = 2;
        }
      }
    }
    tryAll(0);
    std::cout << numBoards -1 << std::endl;
  }
}

