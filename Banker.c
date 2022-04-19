#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>



#define numOfProcesses 5
#define numOfResources 3

// Index 0 is resource A, 1 is B, and 2 is C
int resources[3] = {10, 5, 6};
// Stores what is already allocated. Rows are the processes, columns are the resources
int allocationMatrix[numOfProcesses][numOfResources] = {{0, 1, 0},
                                                        {2, 0, 0},
                                                        {3, 0, 2},
                                                        {2, 1, 1},
                                                        {0, 0, 2}};
// Stores the max allowed to be allocated. Rows are processes, columns are the resources
int maxMatrix[numOfProcesses][numOfResources] = {{7, 5, 3},
                                                {3, 2, 2},
                                                {9, 0, 2},
                                                {2, 2, 2},
                                                {4, 3, 3}};
int need[numOfProcesses][numOfResources];
// Stores the available resources
int available[3] = {3, 3, 2};
bool finished[numOfProcesses];
int sequence[numOfProcesses];



// Return is system is safe
void isSafe() {
    int work[3];
    // Initializes work = available
    for(int i = 0; i < numOfResources; i++) {
        work[i] = available[i];
    }

    // Initilizes all processes to not finished
    for(int i = 0; i < numOfProcesses; i++) {
        finished[i] = false;
    }

    int c = 0;
    while(c < numOfProcesses) {
        bool canAllocate = false;

        for(int i = 0; i < numOfProcesses; i++) {

            if(finished[i] == false) {
                int j = 0;
                while (j < numOfResources) {
                    if(work[j] < need[i][j]) {
                        break;
                    }
                    j++;
                }

                if(j == numOfResources) {
                    for(int j = 0; j < numOfResources; j++) {
                        work[j] += allocationMatrix[i][j];
                    }

                    sequence[c++] = i;
                    finished[i] = true;
                    canAllocate = true;
                }
            }
        }
        if(canAllocate == false) {
            printf("System is not safe.\n");
            return;
        }
    }
    printf("System is safe.\n");
    printf("Safe sequence: ");
    for(int i = 0; i < numOfProcesses; i++) {
        printf("%d ",sequence[i]);
    }
    printf("\n");
}



int main() {
    
    // Calculate the number of needed instances
    for(int i = 0; i < numOfProcesses; i++) {
        for(int j = 0; j < numOfResources; j++) {
            need[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
        }
    }

    isSafe();
}