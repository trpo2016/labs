#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define clear() printf("\033[H\033[J")

int  *generateRandomArr(int *arr, int N);
int  *dropArr(int *arr, int N);
int  cmpfunc(const void *a, const void *b);
void printArr(int *arr, int N);
void heapMethod(int* arr, int N);
// void quickSort(int* arr, int N);
void shellsSort(int* arr, int N);
void checkSum();
void changeN(int *N, int newN);
void siftDown(int *array, int root, int bottom, int *comp, int *asign);

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
    printf("1. Generate Random array\n2. Drop Array\n3. Show Original Array\n4. Sort: Heap Method\n5. Sort: QuickSort(OUT OF SERVICE :())\n6. Sort: Shell's Sort\n7. Show Checksum\n8. Change N\n9. Sort Original Array\n0. Exit\n");
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
      case 4: heapMethod(arr, N); break;
      // case 5: 
      //   int comp = 0, asign = 0;

      //   quickSort(arr, N, &comp, &asign); 
      //   printf("Assignments = %d\n", asign);
      //   printf("Comparisons = %d\n", comp);
        printf("\nfixing...\n");
        break;
      case 6: shellsSort(arr, N); break;
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

// Algorithms

void shellsSort(int *arr, int N){
  int *array = copyIntArr(arr, N);
  int comp = 0, asign = 0; 
  int t;
  for(int k = N/2; k > 0; k /= 2)
    for(int i = k; i < N; i += 1){
      t = array[i];
      int j;
      for(j = i; j >= k; j -= k){
        comp++;
        if(t < array[j-k]){
          asign+=2;
          array[j] = array[j-k];
        }
        else {
          break;
        }
      }
      array[j] = t;
    }

  printf("\nShell-sorted Array: ");
  
  printArr(array, N);
  checkSum(array, N);
  printf("Assignments = %d\n", asign);
  printf("Comparisons = %d\n", comp);
}

void heapMethod(int arr[], int N) {
  int *array = copyIntArr(arr, N);
  int i, temp;
  int comp = 0, asign = 0; 

  for (i = (N / 2)-1; i >= 0; i--)
    siftDown(array, i, N, &comp, &asign);
  for (i = N-1; i >= 1; i--) {
    asign+=2;
    temp = array[0];
    array[0] = array[i];
    array[i] = temp;
    siftDown(array, 0, i-1, &comp, &asign);
  }

  printf("Heap-sorted Array: ");
  
  printArr(array, N);
  checkSum(array, N);
  printf("Assignments = %d\n", asign);
  printf("Comparisons = %d\n", comp);
}

// void quickSort(int *arr , int first, int last, int *comp, int *asign){
//   int *array = copyIntArr(arr, N);
//   int pivot,j,temp,i;

//   if(first<last){
//     pivot=first;
//     i=first;
//     j=last;

//     while(i<j){

//       while(array[i] <= array[pivot] && i < last){
//         *comp+=1;
//         i++;
//        }

//        while(array[j] > array[pivot]){
//         *comp+=1;
//         j--;
//        }

//        *comp+=1;
//        if(i<j){
//          *asign+=2;
//          temp=array[i];
//          array[i]=array[j];
//          array[j]=temp;
//        }
//      }

//      temp=array[pivot];
//      array[pivot]=array[j];
//      array[j]=temp;
//      *asign+=2;

//      quickSort(array,first,j-1, comp, asign);
//      quickSort(array,j+1,last, comp, asign);
//    }
// }

void siftDown(int *array, int root, int bottom, int *comp, int *asign) {
  int done, maxChild, temp;
  done = 0;

  while ((root*2 <= bottom) && (!done)) {
    if (root*2 == bottom){
      *comp+=1;
      maxChild = root * 2;
    }
    else if (array[root * 2] > array[root * 2 + 1]){
      *comp+=1;
      maxChild = root * 2;
    }
    else {
      *comp+=1;
      maxChild = root * 2 + 1;
    }
    *comp+=1;
    if (array[root] < array[maxChild]) {
      *asign+=2;
      temp = array[root];
      array[root] = array[maxChild];
      array[maxChild] = temp;
      root = maxChild;
    }  else
      done = 1;
  }
}

int cmpfunc (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}