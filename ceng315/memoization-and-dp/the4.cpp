#include "the4.h"



int recursive_sln(int i, int*& arr, int &number_of_calls){ //direct recursive
    int x,y;
    number_of_calls+=1;
    if(i == 0) return arr[0];
    if(i == 1) return std::max(arr[0],arr[1]);
    if(i == 2) return std::max(std::max(arr[0],arr[1]),arr[2]);
    
    x = recursive_sln(i-3,arr,number_of_calls) + arr[i];
    y = recursive_sln(i-1,arr,number_of_calls);
    return std::max(x,y);
}



int memoization_sln(int i, int*& arr, int*& mem){ //memoization
    int x,y;
    mem[0] = arr[0];
    mem[1] = std::max(arr[1],arr[0]);
    mem[2] = std::max(arr[2],mem[1]);
    if((i - 3) >= 3 && mem[i-3] == -1) x = memoization_sln(i-3, arr, mem) + arr[i];
    else x = mem[i-3] + arr[i];
    if((i - 1) >= 3 && mem[i-1] == -1) y = memoization_sln(i-1, arr, mem);
    else y = mem[i-1];
    
    mem[i] = std::max(x,y);
    return mem[i];
}



int dp_sln(int size, int*& arr, int*& mem){ //dynamic programming
    mem[0] = arr[0];
    mem[1] = std::max(arr[1],arr[0]);
    mem[2] = std::max(arr[2],mem[1]);

    for(int i = 3; i < size; i++){
        mem[i] = std::max(mem[i-3]+arr[i],mem[i-1]);
    }

    return mem[size-1];
}

