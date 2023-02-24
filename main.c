#include <stdio.h>
#include <stdlib.h>


int search(int numbers[], int low, int high, int value){
    // base if condition that if the lowest number is greater than the highest number, this isnt even possible so just return -1
    if(low>high) {
        return -1;
    }
    // creating a mid point that the program will compare to the target value
    int midPoint = (low+high)/2;

    if(numbers[midPoint]==value) { // if our target is the mid point

        return midPoint;

    }  else if( numbers[midPoint] < value ){ // if target is greater than our mid point

        return search(numbers, value, midPoint+1, high);

    } else if( numbers[midPoint] > value ) { // if target is less than our midpoint

        return search(numbers, value, low, midPoint - 1);
    }
}


void printArray(int numbers[], int sz){

    int i;
    printf("Number array : ");
    for (i = 0;i<sz;++i)
    {
        printf("%d ",numbers[i]);
    }
    printf("\n");
}


int main(void){

    int i, numInputs;
    char* str;
    float average;
    int value;
    int index;
    int* numArray = NULL;
    int countOfNums;
    FILE* inFile = fopen("input.txt","r");

    fscanf(inFile, " %d\n", &numInputs);

    while (numInputs-- > 0)
    {
        fscanf(inFile, " %d\n", &countOfNums);
        numArray = (int *) malloc(countOfNums * sizeof(int));
        average = 0;
        for (i = 0; i < countOfNums; i++)
        {
            fscanf(inFile," %d", &value);
            numArray[i] = value;
            average += numArray[i];
        }

        printArray(numArray, countOfNums);
        value = average / countOfNums;
        index = search(numArray, 0, countOfNums - 1, value);
        if (index >= 0)
        {
            printf("Item %d exists in the number array at index %d!\n",value, index);
        }
        else
        {
            printf("Item %d does not exist in the number array!\n", value);
        }

        free(numArray);
    }

    fclose(inFile);
}