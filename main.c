#include <stdio.h>



// swaps two indexes
void swap(int *x, int *y) {
    int temp = *x;
    *x=*y;
    *y=temp;
}



void bubbleSort(int arr[], int n) {
    int count=0;

    for(int i=0; i<n-1; i++) {

        for(int j=0; j<n-i-1; j++) {

            if(arr[j]>arr[j+1]) { // if the value is less than the next value
                swap(&arr[j], &arr[j+1]);
                count++;
            }

        }
        printf("Pass #%d: %d\n", i+1, count);
        count=0;

    }

}


int main() {

    int arr[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    bubbleSort(arr, 9);
    return 0;
}