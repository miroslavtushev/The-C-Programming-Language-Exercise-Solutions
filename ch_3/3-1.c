// Exercise 3-1. Write a version [of binary search] with only one test inside the loop
// and measure the difference in run-time.

// a more clever approach would invalidate cache before each run

#include <stdio.h>
#include <time.h>
#define SIZE 1000000

int binsearch(int x, int v[], int n);
int binsearchNew(int x, int v[], int n);

int main()
{
    // init seah array
    int array[SIZE];
    for(int i = 0; i < SIZE; i++) {
        array[i] = i + 1;
    }
    
    // to measure performance when the elem. is not present
    array[5969]++;
    int i1, i2;
    double time_taken;
    clock_t t;
    
    // element is in the array
    t = clock();
    i1 = binsearch(37, array, SIZE);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%d Original bin search: %f\n", i1, time_taken);
    
    t = clock();
    i1 = binsearchNew(37, array, SIZE);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%d New bin search: %f\n", i1, time_taken);
    
    printf("\n");
    
    // element is not in the array
    t = clock();
    i2 = binsearch(5970, array, SIZE);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%d Original bin search: %f\n", i2, time_taken);
    
    t = clock();
    i2 = binsearchNew(5970, array, SIZE);
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%d New bin search: %f\n", i2, time_taken);
    
    return 0;
}

int binsearchNew(int x, int v[], int n)
{
    int low, high, mid;
    
    mid = low = 0;
    high = n - 1;
    
    while (low <= high && x != v[mid])
    {
        mid = (low + high) / 2;
        if (x <= v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }
    if (v[mid] == x)
        return mid;
    return -1;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid;
    
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1;
}
