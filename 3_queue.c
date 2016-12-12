#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")
#define N 20

struct Node{
   int data;
   struct Node *next;
};

struct Node *front = NULL;
struct Node *rear = NULL;

void insert(int);
void delete();
void dropQueue();
void ascQueue();
void descQueue();
void randomQueue();
void checkSum();
void seriesCalc();
void display();

int main() {
   int choice, value;

   clear();
   printf("\n:: Queue Implementation using Linked List ::\n");

   while(1){
      printf("\n****** MENU ******\n");
      printf("1. Insert\n2. Delete\n3. Display\n4. Fill with ascending\n5. Fill with descending\n6. Fill with random\n7. Print Checksum\n8. Drop Queue\n9. Calculate Series\n0. Exit\n");
      printf("Enter your choice: ");
      scanf("%d",&choice);

      switch(choice){

        case 1: printf("Enter the value to be insert: ");
         scanf("%d", &value);
         insert(value);
         break;
        case 2: delete(); break;
        case 3: display(); break;
        case 4: ascQueue(); break;
        case 5: descQueue(); break;
        case 6: randomQueue(); break;
        case 7: checkSum(); break;
        case 8: dropQueue(); break;
        case 9: seriesCalc(); break;

        case 0: exit(0);

        default: printf("\nWrong selection!!! Please try again!!!\n");
      }
   }
}

void insert (int value){
   struct Node *newNode;
   newNode = (struct Node*)malloc(sizeof(struct Node));
   newNode->data = value;
   newNode -> next = NULL;
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
    // AddQueueNext(qStart, qEnd, i);
    insert(i);
}

void descQueue (){
  for (int i = N-1; i >= 0; i--)
    insert(i);
}

void randomQueue (){
  srand(time(NULL));
  for (int i = 0; i < N; i++){
    insert(rand() % 100 + 1);
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

void display(){
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
    