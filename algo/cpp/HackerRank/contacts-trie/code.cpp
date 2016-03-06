#include <iostream>
using namespace std;

struct TrieNode{
TrieNode(){
  count =0;
  for (int i =0; i < 26; i++)
    children[i] = NULL;
}
int count;
TrieNode* children[26];
};


int getLen(char* str){
  int len = 0;
  while(str[len] != '\0')
    len++;

  return len;
}

struct Trie{
Trie(){
  root = new TrieNode;
}
  void add(char* str){
    int i = 0;
    TrieNode* currNode = root;
    while(i < getLen(str)){
     if(currNode->children[str[i] - 'a'] == NULL){
        currNode->children[str[i] - 'a'] = new TrieNode;
      }
      currNode->children[str[i] - 'a']->count++;
      currNode = currNode->children[str[i] - 'a'];
      i++;
    }
  }

  int returnCount(char* str){
    int i = 0;
    TrieNode* currNode = root;
    while(i < getLen(str)){
      currNode = currNode->children[str[i] - 'a'];
      if(currNode == NULL) {
        return 0;
      }
      i++;
      //std::cout << std::endl << " >> " << currNode->count;
    }
    return currNode->count;
  }

  TrieNode* root;

};




int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int N;
    std::cin >> N;
    Trie trie;

    char command[4],str[21];
    for(int i = 0; i < N; i++){
      std::cin >> command;
      std::cin >> str;
      //std::cout << command << " " << getLen(str) << std::endl;
      if(getLen(command) == 3){
        trie.add(str);
      }
      else if (getLen(command) == 4){
        std::cout << trie.returnCount(str) << std::endl;
      }
    }

    return 0;
}

