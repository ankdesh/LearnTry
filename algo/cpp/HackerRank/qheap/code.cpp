#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Heap{
    Heap(int len){
        max_len = len;
        this->len = 0;
        heap = new int[max_len];
    }
    
    int max_len;
    int len;
    int* heap;

    void insert(int x){
        heap[len] = x;
        len++;
        int i = len - 1;
        while (i > 0 && heap[i/2] > heap[i]){
            int temp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = temp;
            i /= 2;
        }
    }
    void deleteVal(int x){
        int pos = findPos(x);
        heap[pos] = heap[len-1];
        len --;
        heapify(pos);
    }
    
    void heapify(int i){
        int l = 2*i+1;
        int r = 2*i+2;
        int smallest = i;
        if(l < len && heap[l] < heap[smallest]){
            smallest = l;
        }
        if ( r < len && heap[r] < heap[smallest]){
            smallest = r;
        }
        if( smallest != i){
            int temp = heap[i];
            heap[i] = heap[smallest];
            heap[smallest] = temp;
            heapify (smallest);
        }
    }
    int findPos(int val){
        for (int i = 0; i < len; i++){
            if(heap[i] == val){
                return (i);
            }
        }
        return -1;
    }
    
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    std::cin >> N;
    Heap heap(N);
    for (int i=0; i < N; i++){
        int op,val; 
        cin >> op;
        if (op == 1){
            cin >> val;
            heap.insert(val);
        }
        else if (op == 2){
            cin >> val;
            heap.deleteVal(val);
        }
        else{
                std::cout << heap.heap[0] << std::endl;
            }
    }
    
    return 0;
}

