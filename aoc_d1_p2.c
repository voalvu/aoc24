#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 1000
#define MAX_INTEGERS 2

#define TABLE_SIZE 1000 // Size of the hash table

typedef struct {
    int number;
    int count;
} HashEntry;

HashEntry hashTable[TABLE_SIZE];
HashEntry hashTable2[TABLE_SIZE];

int hashFunction(int number) {
    return abs(number) % TABLE_SIZE; // Simple hash function
}

void insert(int number, HashEntry *hashTable) {
    int index = hashFunction(number);
    while (hashTable[index].count != 0) { // Collision resolution
        if (hashTable[index].number == number) {
            hashTable[index].count++;
            return;
        }
        index = (index + 1) % TABLE_SIZE; // Linear probing
    }
    hashTable[index].number = number;
    hashTable[index].count = 1;
}
printAndHandleOccurrences(HashEntry *hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].count > 1) {
            if(i%100==0){
                printf("Number: %d, Count: %d\n", hashTable[i].number, hashTable[i].count);
            }
            //totalAnswer+=hashTable[i].number*hashTable[i].count;
        }
    }
}

int main() {
    FILE *file;
    char buffer[256];
    const char *delimiter = "    ";
    int numbers1[MAX_LINES];
    int numbers2[MAX_LINES];
    setvbuf(stdout, NULL, _IONBF, 0); // Disable buffering


    file = fopen("../adv_01input.txt", "r");
    if(file == NULL){
        perror("error opening file");
        return -1;
    }
    int lineCount = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL && lineCount < MAX_LINES) {
/*         char *buffercopy = buffer;
        char *token = strtok(buffer,delimiter);
        char *token2 = strtok(NULL, delimiter);
        int tokint = atoi(token);
        int tokint2 = atoi(token2); 
*/
        sscanf(buffer, "%d    %d", &numbers1[lineCount], &numbers2[lineCount]);
        lineCount++;

        //printf("buffer: %s\ntokens:%s %sints:%d %d\n", buffercopy,token,token2,tokint,tokint2);
    }
    int *combined = (int *)malloc((lineCount * 2) * sizeof(int));
    memcpy(combined, numbers1, lineCount * sizeof(int)); // Copy numbers1
    memcpy(combined + lineCount, numbers2, lineCount * sizeof(int)); // Copy numbers2
    
    // Handle the case where no line was read (EOF or error)
    if (feof(file)) {
        printf("End of file reached.\n");
    } else {
        perror("Error reading line");
    }

    for (int i = 0; i < lineCount*2; i++) {
        //printf("Line %d: %d\n", i + 1, combined[i]);
        if(i < 1000)    insert(combined[i], hashTable);
        else insert(combined[i], hashTable2);
        //printf("Inserted %d: %d\n", i + 1, combined[i]);

    }
    int total = 0;
    for (int i = 0; i < MAX_LINES; i++) {
        printf("%d, %d\n",i, numbers1[i]);
        int j = 0;
        while(j < TABLE_SIZE*5){
            if(hashTable2[j].number == numbers1[i]){
                total += numbers1[i]*hashTable2[j].count;
                printf("%s %d found %d times!\n","Eureka!",numbers1[i],hashTable2[j].count);
                break;
            }
            j++;
        }
    }
    printf("The answer for aoc day1 part2 is: %d",total);
    //printf("%d\n",printAndHandleOccurrences(hashTable));
    //printf("%d\n",printAndHandleOccurrences(hashTable2));
    fclose(file);
    free(combined);
    return 0;
}