#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")
// #define N 20

typedef struct Node{
   int data;
   struct Node *next;
} Node;

int N = 20;
struct Node *front = NULL;
struct Node *rear = NULL;

void insert(int);
void delete();
void dropQueue();
void ascQueue();
void descQueue();
void randomQueue();
void checkSum(Node *list);
void seriesCalc();
void display(Node *front);
void frontBackSplit(Node *source, Node **frontRef, Node **backRef);
void changeN(int *N, int newN);
Node* mergeSort(Node **front, int *asign, int *comp);
Node* copy(Node *start1);
Node* sortedMerge(Node *a, Node *b, int *asign, int *comp);
Node* radixSort (Node *list, int base, int rounds, int *asign);

int main() {
 int newN;
 int choice, value;

 clear();
 printf("\n:: Queue Sorting using Merge and Radix Sort ::\n");

 while(1){
    printf("\n:: N = %d ::\n", N);
    printf("\n****** MENU ******\n");
    printf("1. Insert\n2. Delete\n3. Display\n4. Fill with ascending\n5. Fill with descending\n6. Fill with random\n7. Print Checksum\n8. Drop Queue\n9. Calculate Series\n10. Merge-Sort\n11. Radix-Sort\n12. Change N\n0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d",&choice);

    switch(choice){

      case 1: printf("Enter the value to be insert: ");
       scanf("%d", &value);
       insert(value);
       break;
      case 2: delete(); break;
      case 3: display(front); break;
      case 4: ascQueue(); break;
      case 5: descQueue(); break;
      case 6: randomQueue(); break;
      case 7: checkSum(front); break;
      case 8: dropQueue(); break;
      case 9: seriesCalc(); break;
      case 10: {
        int asign = 0, comp = 0;
        Node *newFront = copy(front);
        newFront = mergeSort(&newFront, &asign, &comp);
        printf("Assigns = %d\n", asign);
        printf("Comparisons = %d\n", comp);
        display(newFront);

        break;
      }
      case 11: {
        int asign = 0;
        Node *newFront = copy(front);
        Node *radixSorted = radixSort(newFront, 10, 2, &asign);
        printf("Assigns = %d\n", asign);
        display(radixSorted);

        break;
     }

     case 12: {
       printf("\nEnter new N...\n");
       scanf("%d", &newN);
       changeN(&N, newN);

       break;
     }

      case 0: exit(0);

      default: printf("\nWrong selection!!! Please try again!!!\n");
    }
  }
}

void insert (int value){
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   newNode->data = value;
   newNode->next = NULL;
   if(front == NULL)
      front = rear = newNode;
   else{
      rear -> next = newNode;
      rear = newNode;
   }
   printf("\nInsertion is Success!!!\n");
}

void delete(){
   if(front == NULL)
      printf("\nQueue is Empty!!!\n");
   else{
      struct Node *temp = front;
      front = front -> next;
      printf("\nDeleted element: %d\n", temp->data);
      free(temp);
   }
}

void dropQueue (){
  if (front == NULL)
    printf("\nStack is already Empty!\n");
  else {
    while(front != NULL){
      delete();
    }
  }
}

void ascQueue (){
  for (int i = 0; i < N; i++)
    insert(i);
}

void descQueue (){
  for (int i = N-1; i >= 0; i--)
    insert(i);
}

void randomQueue (){
  srand(time(NULL));
  for (int i = 0; i < N; i++){
    insert(rand() % 100);
  }
}

void seriesCalc (){
  if (front == NULL)
    printf("\nStack is Empty!\n");

  struct Node *temp = front;
  int series = 0;
  int prev = -1;
  int curr = temp->data;

  while (temp->next != NULL){
    if (prev != -1 && prev <= temp->data)
      series+=0;
    else
      series+=1;
    prev = temp->data;
    temp = temp->next;
  }

  printf("\nSeries = %d\n", series);
}

void checkSum (){
  if(front == NULL)
    printf("\nQueue is Empty!!!\n");

  struct Node *temp = front;
  int sum = 0;

  while (temp->next != NULL){
    sum += temp->data;
    temp = temp->next;
  }

  printf("\nChecksum = %d\n", sum);
}

void display(Node *front){
   if(front == NULL)
      printf("\nQueue is Empty!!!\n");
   else{
      struct Node *temp = front;
      while(temp->next != NULL){
	 printf("%d--->",temp->data);
	 temp = temp -> next;
      }
      printf("%d--->NULL\n",temp->data);
   }
}

void frontBackSplit (Node *source, Node **frontRef, Node **backRef){
	Node *fast;
	Node *slow;

	if (source == NULL || source->next == NULL){
		*frontRef = source;
		*backRef = NULL;
	}
	else {
		slow = source;
		fast = source->next;

		while (fast != NULL){
			fast = fast->next;
			if (fast != NULL){
				slow = slow->next;
				fast = fast->next;
			}
		}
		*frontRef = source;
		*backRef = slow->next;
		slow->next = NULL;
	}
}

Node* mergeSort (Node **front, int *asign, int *comp){
	Node *head = *front;
	Node *a;
	Node *b;

	if ((head == NULL) || (head->next == NULL)){
		return head;
	}

	frontBackSplit(head, &a, &b);

  *asign += 1;

	mergeSort(&a, asign, comp);
	mergeSort(&b, asign, comp);

	*front = sortedMerge(a, b, asign, comp);

  return *front;
}

Node* sortedMerge (Node *a, Node *b, int *asign, int *comp){
 Node *result = NULL;

 if (a == NULL){
   return(b);
 }
 else if (b == NULL){
   return(a);
 }

 *comp += 1;
 if (a->data <= b->data){
   *asign += 1;
   result = a;
   result->next = sortedMerge(a->next, b, asign, comp);
 }
 else {
   *asign += 1;
   result = b;
   result->next = sortedMerge(a, b->next, asign, comp);
 }
 return result;
}

Node* radixSort (Node *list, int base, int rounds, int *asign){
	int n = 1;
	Node **bucket, *next, *temp;
	// Dyamic bucket array
	bucket = malloc(sizeof(*bucket) * base);

	for (int j = 0; j < rounds; j++){
		//Place numbers into buckets.
		while(list != NULL){
				*asign+=1;
				next				 = list->next;
				list->next	 = bucket[(list->data/n) % base];
				bucket[(list->data / n) % base] = list;
				list				 = list->next;
				list				 = next;
		}

		//Rebuild list
		for (int i = base; i >= 0; i--){
			while (bucket[i] != NULL){
				*asign+=1;
				temp		 = bucket[i]->next;
				bucket[i]->next = list;
			  list		 = bucket[i];
				bucket[i]	 = bucket[i]->next;
				bucket[i]	 = temp;
			}
		}
		n *=10;
	}
  checkSum(list);

	return list;
}

Node* copy (Node *start1){
  while (start1 != NULL){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if(start1==NULL) return temp;
    temp->data = start1->data;
    temp->next = copy(start1->next);

    return temp;
  }

}

void changeN(int *N, int newN){
  *N = newN;
}
