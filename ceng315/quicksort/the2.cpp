#include "the2.h"
//You may write your own helper functions here

int distance(int x, int y){
    if(x>y) return x - y;
    else return y - x;
}

void swapf(unsigned short *a, unsigned short *b, long &swap){
    unsigned short temp = *a;
    *a = *b;
    *b = temp;
    swap++;
}

int partition(unsigned short* arr, long &swap, double &avg_dist, double &max_dist, int start, int end){
    int p = arr[end];
    int i = start - 1;
    for(int j = start; j < end; j++){
        if(arr[j] >= p){
            i++;
            swapf(&arr[i], &arr[j], swap);
            avg_dist += distance(i,j);
            if(max_dist < distance(i,j)) max_dist = distance(i,j);
            
        }
    }
    swapf(&arr[i+1], &arr[end], swap);
    avg_dist += distance(i+1,end);
    if(max_dist < distance(i+1,end)) max_dist = distance(i+1,end);
    return i+1;
}

void quickSortFunc(unsigned short* arr, long &swap, double &avg_dist, double &max_dist, int size, int start, int end){
    if(size > 1){
        int p = partition(arr, swap, avg_dist, max_dist, start, end);
        quickSortFunc(arr, swap, avg_dist, max_dist, p-start, start, p-1);
        quickSortFunc(arr, swap, avg_dist, max_dist, end - p, p+1, end);
    }
}

int partitionHoare(unsigned short* arr, long &swap, double &avg_dist, double &max_dist, int start, int end){
    int p = arr[(end - start)/2 + start];
    int i = start - 1;
    int j = end + 1;
    
    while(true){
        do {
            j--;
        } while (arr[j] < p);
        
        
        do {
            i++;
        } while (arr[i] > p);
 
        
        if(i < j){
            swapf(&arr[i], &arr[j], swap);
            avg_dist += distance(i,j);
            if(max_dist < distance(i,j)) max_dist = distance(i,j);
        }
        else return j;
    }
    
}

void quickHoare(unsigned short* arr, long &swap, double &avg_dist, double &max_dist, int size, int start, int end){
    if(size > 1){
        int p = partitionHoare(arr, swap, avg_dist, max_dist, start, end);
        quickHoare(arr, swap, avg_dist, max_dist, p-start+1, start, p);
        quickHoare(arr, swap, avg_dist, max_dist, end-p, p+1, end);
    }
}

void quickSort(unsigned short* arr, long &swap, double & avg_dist, double & max_dist, bool hoare, int size)
{
    if(hoare == false){
        quickSortFunc(arr, swap, avg_dist, max_dist, size, 0, size-1);
        avg_dist /= swap;
    }
    else{
        quickHoare(arr, swap, avg_dist, max_dist, size, 0, size-1);
        if(swap != 0 )avg_dist /= swap;
    }
	
}

void partitionThree(unsigned short *arr, long &swap, long &comparison, int start, int end, int &l, int &r){
    int i = start;
    int j = start;
    int p = end;
    int m;
    
    while(i < p){
        if(arr[i] > arr[end]){
            swapf(&arr[i], &arr[j], swap);
            i++;
            j++;
            comparison++;
        }
        else if(arr[i] == arr[end]){
            p--;
            swapf(&arr[i], &arr[p], swap);
            comparison += 2;
        }
        else{
            i++;
            comparison += 2;
        }
    }
    
    if((p-j) < (end - p + 1)) m = p - j;
    else m = end - p + 1;
    for(int k = 0; k < m; k++){
        swapf(&arr[j+k],&arr[end-m+1 + k], swap);
    }
    l = j;
    r = p - j;
    
    
}

void threeHelper(unsigned short *arr, long &swap, long &comparison, int size, int start, int end){
    if(size > 1){
        int l,r;
        partitionThree(arr, swap, comparison, start, end, l, r);
        threeHelper(arr, swap, comparison, (l - start), start, l-1);
        threeHelper(arr, swap, comparison, r, end - r + 1, end);
    }
}

void quickSort3(unsigned short *arr, long &swap, long &comparison, int size) {
	threeHelper(arr, swap, comparison, size, 0, size-1);
	
}