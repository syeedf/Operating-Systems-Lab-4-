#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE 5
#define THREAD_NUM 2
int array[SIZE];
int part= 0; 
void fillArrayWithRandomNumbers(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) array[i] = rand()%100;
}

void printArray(int arr[SIZE]) {
    for(int i = 0; i<SIZE; i++) printf("%5d", arr[i]);
    printf("\n");
}

typedef struct StartEndIndexes {
    int start;
    int end;
} StartEndIndexes;

void merge(int low, int mid, int high) {
    int n1= mid - low + 1;
    int n2= high-mid,i,j;
    int* left =(int*) malloc( n1 * sizeof(int)); 
    int* right = (int*)malloc(n2 * sizeof(int)); 

    for (i = 0; i < n1; i++) 
        left[i] = array[i + low]; 
   
    for (i = 0; i < n2; i++) 
        right[i] = array[i + mid + 1]; 
  
    int k = low; 
    i = j = 0; 
  
    while (i < n1 && j < n2) { 
        if (left[i] <= right[j]) 
            array[k++] = left[i++]; 
        else
            array[k++] = right[j++]; 
    } 
  
   
    while (i < n1) { 
        array[k++] = left[i++]; 
    } 
  
    
    while (j < n2) { 
        array[k++] = right[j++]; 
    } 

} 
  
// merge sort function
void merge_sort(int low, int high) 
{ 

    int mid = low + (high - low) / 2; 
    if (low < high) { 
   
        merge_sort(low, mid); 

        merge_sort(mid + 1, high); 
 
        merge(low, mid, high); 
    } 
} 

// Runs mergesort on the array segment described in the
// argument. Spawns two threads to mergesort each half
// of the array segment, and then merges the results.
void* mergeSort(void* args) {
    int thread_part = part++; 
  

    int low = thread_part * SIZE; 
    int high = (thread_part + 1) * SIZE-1; 
    int mid = low+(high-low)/2;
    if (low< high){
        merge_sort(low,mid);
        merge_sort(mid+1,high);
        merge(low,mid,high);
    }
}

int main() {
    srand(time(0));
    StartEndIndexes sei;
    sei.start = 0;
    sei.end = SIZE - 1;
    int len = SIZE/ THREAD_NUM;
    // 1. Fill array with random numbers.
    fillArrayWithRandomNumbers(array);
    
    // 2. Print the array.
    printf("Unsorted array: ");
    printArray(array);
    
    // 3. Create a thread for merge sort.
    int i;
    pthread_t threads[THREAD_NUM];
    for(i =0; i< THREAD_NUM; i++ )
    {
        pthread_create(&threads[i], NULL, mergeSort,(void*)NULL);
    }
    for(i=0; i< THREAD_NUM;i++)
        pthread_join(threads[i],NULL);
    // 4. Wait for mergesort to finish.
    merge(sei.start,(SIZE/ 2-1)/2, SIZE/2 -1);
    merge(SIZE / 2, SIZE/2 + (SIZE-1-SIZE/2)/2, sei.end); 
    merge(0, (sei.end)/2, sei.end); 
    
    // 5. Print the sorted array.
    printf("Sorted array:   ");
    printArray(array);
    
    return 0; 
}