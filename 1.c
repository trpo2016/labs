#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

int  *generateRandomArr(int *arr, int N);
int  *dropArr(int *arr, int N);
void printArr(int *arr, int N);
void directMethod(int* arr, int N);
void bubbleMethod(int* arr, int N);
void shakerMethod(int* arr, int N);
void checkSum();
void changeN(int *N, int newN);
int  cmpfunc(const void *a, const void *b);

int main() {
  int N = 10;
  int choice, value;
  int newN;
  int *arr;

  clear();
  printf("\n:: Sotring arrays part I ::\n");

  while (1){
    printf("\n:: N = %d ::\n", N);
    printf("\n****** MENU ******\n");
    printf("1. Generate Random array\n2. Drop Array\n3. Show Original Array\n4. Sort: Direct Method\n5. Sort: Bubble Method\n6. Sort: Shaker Method\n7. Show Checksum\n8. Change N\n9. Sort Original Array\n0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){
      case 1: 
        arr = generateRandomArr(arr, N);
        break;
      case 2: 
        arr = dropArr(arr, N); 
        break;
      case 3: printArr(arr, N); break;
      case 4: directMethod(arr, N); break;
      case 5: bubbleMethod(arr, N); break;
      case 6: shakerMethod(arr, N); break;
      case 7: checkSum(arr, N); break;
      case 8: 
        printf("\nEnter new N...\n");
        scanf("%d", &newN);
        changeN(&N, newN);
        break;
      case 9:
        qsort(arr, N, sizeof(int), cmpfunc); break;

      case 0: exit(0);
    }
  }
}

int *generateRandomArr(int *arr, int N){
  srand(time(NULL));
  arr = (int *) malloc(N * sizeof(int));

  for (int i = 0; i < N; i++)
    arr[i] = rand() % 100;

  printf("\nRandom-based array generated.\n");

  return arr;
}

int *dropArr(int *arr, int N){
  // free(arr);
  memset(arr, 0, sizeof(int) * N);
  // printf("A[0] == %d\n", *arr[0]);
  printf("\nArray was dropped\n");

  return arr;
}

int *copyIntArr(int *arr, int N){
   int *p = malloc(N * sizeof(int));
   memcpy(p, arr, N * sizeof(int));
   return p;
}

void printArr(int *arr, int N){
  printf("[");
  for (int i = 0; i < N; i++){
    if (i == N-1) 
      printf("%d]", arr[i]);
    else
      printf("%d, ", arr[i]);
  }
}

void checkSum(int *arr, int N){
  int sum = 0;

  for (int i = 0; i < N; i++)
    sum+=arr[i];

  printf("\nChecksum = %d\n", sum);
}

void changeN(int *N, int newN){
  *N = newN;
}

// Sorting Algorithms

void directMethod(int *arr, int N){
  int *array = copyIntArr(arr, N);
  int comp = 0, asign = 0; 
  int min, temp;

  for (int i = 0; i < N; i++){
    min = i;
    for (int j = i+1; j < N; j++){
      comp+=1;
      if (array[j] < array[min]){
        asign+=2;
        min = j;
      }
    }

    temp = array[i];
    array[i] = array[min];
    array[min] = temp; 
  }

  printf("\nDirect Sorted Array: ");

  printArr(array, N);
  checkSum(array, N);
  printf("Assignments = %d\n", asign);
  printf("Comparisons = %d\n", comp);
}

void bubbleMethod(int *arr, int N){
  int *array = copyIntArr(arr, N);
  int comp = 0, asign = 0; 

  for (int i = 0; i < N - 1; i++){
    for (int j = 0; j < N - i - 1; j++){
      comp++;
      if (array[j] > array[j+1]){
        asign+=2;
        int tmp = array[j];
        array[j] = array[j+1];
        array[j+1] = tmp;
      }
    }
  }

  printf("\nBubble Sorted Array: ");

  printArr(array, N);
  checkSum(array, N);
  printf("Assignments = %d\n", asign);
  printf("Comparisons = %d\n", comp);
}

void shakerMethod(int *arr, int N){
  int *array = copyIntArr(arr, N);
  int comp = 0, asign = 0; 
  int left, right, temp;
  left = 0;
  right = N - 1;
  int flag = 1;

  while((left < right) && flag > 0){
    flag = 0;

    for (int i=left; i<right; i++){
      comp++;
      if (array[i] > array[i+1]){
        temp = array[i];
        array[i] = array[i+1];
        array[i+1] = temp;
        flag = 1;
        asign+=2;
      }
    }
    right--;

    for (int i=right; i>left; i--){
      comp++;
      if (array[i-1] > array[i]){
        temp = array[i];
        array[i] = array[i-1];
        array[i-1] = temp;
        flag = 1;
        asign+=2;
      }    
    }
    left++;
  }
  printf("\nShaker Sorted Array: ");

  printArr(array, N);
  checkSum(array, N);
  printf("Assignments = %d\n", asign);
  printf("Comparisons = %d\n", comp);
}

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}