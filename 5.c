#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20
#define clear() printf("\033[H\033[J")
#define MAX_STRING_SIZE 256


typedef struct Phonebook{
    char    *name;
    char    *number;
    char    *addres;
} Phonebook;

int lastIndex = 0;

void addNewUser(Phonebook *pb);
void findInIndexArr(int n1, int n2, Phonebook *pointArr, Phonebook *pb);
void showPhonebook(Phonebook *pb);
void findBetweenNumbers(Phonebook *pointArr, Phonebook *pb);
void addUserManualy(Phonebook *pb);
void importUsers(Phonebook *pb);
void createIndexArray(Phonebook *pointArr, Phonebook *pb);

int main (){
    char c;
    // Phonebook myPB;
    // Phonebook *pb = &myPB;
    // pb = malloc(N * sizeof myPB); 

    Phonebook *pb = malloc(N * sizeof *pb);
    // Phonebook **pointArr[20];
    Phonebook *pointArr;
    pointArr = (Phonebook*) malloc(sizeof(Phonebook));

    while(1){
        clear();
        puts(" 1 - Add new Users to the Phonebook ");
        puts(" 2 - Show the Phonebook ");
        puts(" 3 - Search by 2 numbers ");
        puts(" 4 - Create index array" );
        puts(" 0 - Exit");

        fseek(stdin, 0, SEEK_END);
        c = getchar();

        switch(c){
            case '1': addNewUser(pb); break;
            case '2': showPhonebook(pb); break;
            case '3': findBetweenNumbers(pointArr, pb); break;
            case '4': createIndexArray(pointArr, pb); break;
            case '0': return 0;

            default : {
                clear();
                puts("Incorrect input...try again");
            };
        }
    }
}

void addNewUser(Phonebook *pb){
    char c;
    clear();
    
    puts(" 1 - Add new user manualy ");
    puts(" 2 - Add new users from file (5.txt) "); //hardcoded
    
    fseek(stdin, 0, SEEK_END);
    c = getchar();

    switch(c){
        case '1': addUserManualy(pb); break;
        case '2': importUsers(pb); break;
        // case '0'
    }
};

void showPhonebook(Phonebook *pb){
    clear();

    for (int i = 0; i < lastIndex; i++){
        printf("-----------------------------------|\n");
        printf("| Name: <%s>\n", pb[i].name);
        printf("| Number: <%s>\n", pb[i].number);
        printf("| Addres: <%s>\n", pb[i].addres);
        printf("-----------------------------------|\n\n");
    }

    fseek(stdin, 0, SEEK_END);
    getchar();
};

void addUserManualy(Phonebook *pb){
    // struct phonebook *u;
    // u = malloc(sizeof(struct phonebook));
    pb[lastIndex].name = malloc(MAX_STRING_SIZE);
    pb[lastIndex].addres = malloc(MAX_STRING_SIZE);
    pb[lastIndex].number = malloc(MAX_STRING_SIZE);

    clear();

    puts(" Give user a name... ");
    fseek(stdin, 0, SEEK_END);
    fgets(pb[lastIndex].name, MAX_STRING_SIZE, stdin);

    puts(" Give user a phone number...");
    fseek(stdin, 0, SEEK_END);
    fgets(pb[lastIndex].number, MAX_STRING_SIZE, stdin);

    puts(" Give user an addres...");
    fseek(stdin, 0, SEEK_END);
    fgets(pb[lastIndex].addres, MAX_STRING_SIZE, stdin);

    lastIndex+=1;
}  

void importUsers(Phonebook *pb){
    char buf[512];
    FILE *textbook;


    
    textbook = fopen("./5.txt", "r");
    
    if (textbook == NULL){
        printf("Error.\n");
    }

    while (fgets(buf, sizeof(buf), textbook) && lastIndex < 20){
        pb[lastIndex].name = malloc(MAX_STRING_SIZE);
        pb[lastIndex].number = malloc(MAX_STRING_SIZE);
        pb[lastIndex].addres = malloc(MAX_STRING_SIZE);
        
        printf("Original string = %s\n", buf);
        char *partStr;

        partStr = strtok(buf, ",");
        strcpy(pb[lastIndex].name, partStr);

        partStr = strtok(NULL, ",");
        strcpy(pb[lastIndex].number, partStr);

        partStr = strtok(NULL, ",");
        strcpy(pb[lastIndex].addres, partStr);

        lastIndex+=1;

        fseek(stdin, 0, SEEK_END);
        // getchar();
    }

    // fseek(stdin, 0, SEEK_END);
    // getchar();

    fclose(textbook);

}

void createIndexArray(Phonebook *pointArr, Phonebook *pb){
    int min;
    Phonebook temp;

    for (int i = 0; i < N; i++){
        pointArr[i] = pb[i];
    }

    for (int i = 0; i < N; i++){
        min = i;
        for(int j=i+1; j < N; j++){
            if (atoi((pointArr[j].number)) < atoi((pointArr[min].number))){
                // printf("%d < %d\n", atoi((pointArr[j].number)), atoi((pointArr[i].number)));
                min = j;
            }
        }
         // printf("Buggy-min: %d\n", atoi((pointArr[min].number)));
        temp = pointArr[i];
        pointArr[i] = pointArr[min];
        pointArr[min] = temp; 
    }

    for (int i = 0; i<N; i++){
        printf("Number = %d\n", atoi((pointArr[i].number)));
    }

    fseek(stdin, 0, SEEK_END);
    getchar();
}


void findInIndexArr(int n1, int n2, Phonebook *pointArr, Phonebook *pb){
    int left, right;

    for (int i = 0; i < N; i++){
        if ( atoi((pointArr[i].number)) < n1 ){
            // printf("WTF: %d < %d\n", atoi((pointArr[i].number)), n1);
            left = i;
            continue;
        }
        else
            left = i;
            break;
    }

    for (int i = N-1; i >= 0; i--){
        if ( atoi((pointArr[i].number)) > n2 ){
            // printf("WTF: %d > %d\n", atoi((pointArr[i].number)), n1);
            right = i;
            continue;
        }
        else
            right = i;
            break;
    }

    // printf("Left = %d, Right = %d\n", left, right);

    // for (int i = left; i<= right; i++){
    //     printf("Number = %d\n", atoi((pointArr[i].number)));
    // }

    for (int i = left; i<= right; i++){
        printf("-----------------------------------|\n");
        printf("| Name: %s\n", pointArr[i].name);
        printf("| Number: %s\n", pointArr[i].number);
        printf("| Addres: %s\n", pointArr[i].addres);
        printf("-----------------------------------|\n\n");
    }
}

void findBetweenNumbers(Phonebook *pointArr, Phonebook *pb){
    int n1, n2;

    clear();

    printf("Type two 5-digit numbers to search in between...\n");
    scanf("%d %d", &n1, &n2);

    // printf("Searching between %d and %d...\n", n1, n2);

    findInIndexArr(n1, n2, pointArr, pb);

    fseek(stdin, 0, SEEK_END);
    getchar();
}

