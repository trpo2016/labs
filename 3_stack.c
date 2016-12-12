#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define clear() printf("\033[H\033[J")
#define N 20

struct Node{
   int data;
   struct Node *next;
};

struct Node *top = NULL;

void push(int);
void pop();
void ascStack();
void descStack();
void randomStack();
void checkSum();
void dropStack();
void seriesCalc();
void display();


int main() {
   int choice, value;

   clear();
   printf("\n:: Stack using Linked List ::\n");

   while(1){
      printf("\n****** MENU ******\n");
      printf("1. Push\n2. Pop\n3. Display\n4. Fill with ascending\n5. Fill with descending\n6. Fill with random\n7. Print Checksum\n8. Drop Stack\n9. Calculate Series\n0. Exit\n");
      printf("Enter your choice: ");
      scanf("%d",&choice);

      switch(choice){
        case 1:  
         printf("Enter the value to be insert: ");
         scanf("%d", &value);
         push(value);
         break;

        case 2: pop(); break;
        case 3: display(); break;
        case 4: ascStack(); break;
        case 5: descStack(); break;
        case 6: randomStack(); break;
        case 7: checkSum(); break;
        case 8: dropStack(); break;
        case 9: seriesCalc(); break;

        case 0: exit(0);

        default: printf("\nWrong selection!!! Please try again!!!\n");
      }
   }
}

void push (int value){
  struct Node *newNode;
  newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = value;

  if(top == NULL)
    newNode->next = NULL;
  else
    newNode->next = top;

  top = newNode;
  printf("\nAdded element to stack\n");
}

void pop (){
  if (top == NULL)
    printf("\nNo elements in stack\n");
  else {
    struct Node *temp = top;
    printf("\nDeleted element: %d", temp->data);
    top = temp->next;
    free(temp);
  }
}

void dropStack (){
  if (top == NULL)
    printf("\nStack is already Empty!\n");
  else {
    while(top != NULL){
      pop();
    }
  }
}

void ascStack (){
  for (int i = 0; i < N; i++)
    // AddQueueNext(qStart, qEnd, i);
    push(i);
}

void descStack (){
  for (int i = N-1; i >= 0; i--)
    push(i);
}

void randomStack (){
  srand(time(NULL));
  for (int i = 0; i < N; i++){
    push(rand() % 100 + 1);
  }
}

void seriesCalc (){
  if (top == NULL)
    printf("\nStack is Empty!\n");

  struct Node *temp = top;
  int series = 0;
  int prev = -1;

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
  if (top == NULL)
    printf("\nStack is Empty!\n");
  struct Node *temp = top;
  int sum = 0;

  while (temp->next != NULL){
    sum += temp->data;
    temp = temp->next;
  }

  printf("\nChecksum = %d\n", sum);
}

void display (){
  if (top == NULL)
    printf("\nStack is Empty!\n");
  else {
  struct Node *temp = top;

  while(temp->next != NULL){
    printf("%d--->",temp->data);
    temp = temp->next;
  }

  printf("%d--->NULL",temp->data);

  }
}
