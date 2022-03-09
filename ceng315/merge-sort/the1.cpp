#include "the1.h"

//You can add your own helper functions

int sillyHelper(int *arr, long &comparison, long &swap, int size, int first)
{
    int num_of_calls=1;
	
	if(size == 0 || size == 1){
	    return num_of_calls;
	}
	else if(size == 2){
	    if(arr[first] > arr[first + 1]){
	        int tmp = arr[first];
	        arr[first] = arr[first + 1];
	        arr[first + 1] = tmp;
	        swap++;
	    }
	    comparison++;
	}
	else{
	    num_of_calls += sillyHelper(arr, comparison, swap, size/2, first);
	    num_of_calls += sillyHelper(arr, comparison, swap, size/2, first + size/4);
	    num_of_calls += sillyHelper(arr, comparison, swap, size/2, first + size/2);
	    num_of_calls += sillyHelper(arr, comparison, swap, size/2, first);
	    num_of_calls += sillyHelper(arr, comparison, swap, size/2, first + size/4);
	    num_of_calls += sillyHelper(arr, comparison, swap, size/2, first);
	}
	
	return num_of_calls;
}

int sillySort(int* arr, long &comparison, long & swap, int size) 
{

    int num_of_calls = 1;
	
	num_of_calls = sillyHelper(arr, comparison, swap, size, 0);
	
	return num_of_calls;
}

void merge(int *arr, int first, int size, long &comparison)
{
    int n = size/4;
    int nh = size/2;
    int q1[n], q2[n], q3[n], q4[n], h1[nh], h2[nh];
    int i, j, k;
    
    for(i = 0; i < n; i++){
        q1[i] = arr[first + i];
    }
    
    for(i = 0; i < n; i++){
        q2[i] = arr[first + n + i];
    }
    
    for(i = 0; i < n; i++){
        q3[i] = arr[first + 2*n + i];
    }
    
    for(i = 0; i < n; i++){
        q4[i] = arr[first + 3*n + i];
    }
    
    i = 0;
    j = 0;
    
    for(k = 0; k < nh; k++){
        if(i < n && j < n){
            if(q1[i] <= q3[j]){
                comparison++;
                h1[k] = q1[i];
                i++;
            }
            else{
                comparison++;
                h1[k] = q3[j];
                j++;
            }
        }
        else if(i < n){
            h1[k] = q1[i];
            i++;
        }
        else{
            h1[k] = q3[j];
            j++;
        }
    }
    
    i = 0;
    j = 0;
    
    for(k = 0; k < nh; k++){
        if(i < n && j < n){
            if(q2[i] <= q4[j]){
                comparison++;
                h2[k] = q2[i];
                i++;
            }
            else{
                comparison++;
                h2[k] = q4[j];
                j++;
            }
        }
        else if(i < n){
            h2[k] = q2[i];
            i++;
        }
        else{
            h2[k] = q4[j];
            j++;
        }
    }
    
    i = 0;
    j = 0;
    k = first;
    
    while(i < nh && j < nh){
        if(h1[i] <= h2[j]){
            comparison++;
            arr[k] = h1[i];
            i++;
            k++;
        }
        else{
            comparison++;
            arr[k] = h2[j];
            j++;
            k++;
        }
    }
    
    
    
    while(i < nh){
        arr[k] = h1[i];
        i++;
        k++;
    }
    
    while(j < nh){
        arr[k] = h2[j];
        j++;
        k++;
    }
    
}

int crossMergeHelper(int *arr, long &comparison, int size, int first)
{
    
    int num_of_calls = 1;
    
    if(size == 2){
	    if(arr[first] <= arr[first + 1]){
	        comparison++;
	    }
	    else{
	        int tmp = arr[first];
	        comparison++;
	        arr[first] = arr[first + 1];
	        arr[first + 1] = tmp;
	    }
	}
    
    else if(size >= 4){
        num_of_calls += crossMergeHelper(arr, comparison, size/4, first);
	    num_of_calls += crossMergeHelper(arr, comparison, size/4, first + size/4);
	    num_of_calls += crossMergeHelper(arr, comparison, size/4, first + size/2);
	    num_of_calls += crossMergeHelper(arr, comparison, size/4, first + 3*size/4);
	    
	    merge(arr, first, size, comparison);
    }
    
	return num_of_calls;
}

int crossMergeSort(int *arr, long &comparison, int size)
{
	
	int num_of_calls=1;

	num_of_calls = crossMergeHelper(arr,comparison,size,0);
	
	return num_of_calls;
	
}



