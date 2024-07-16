#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include "sequences.h"
#include "horse.h"
#include "race.h"

#define NUM_HORSES 6
#define NUM_SIMULATIONS 1000


void startSequence(int* isBetting){
    printf("Welcome to the Horse Racing Simulation!\n");
    printf("Would you like to bet today? (1 for yes, 0 for no)\n");
    scanf("%d", isBetting);    
}

void simulationSequence(int positions[], int horseIndices[], Horse horses[]){
    int winCounts[NUM_HORSES] = {0};      
    int placeCounts[NUM_HORSES] = {0};  
    int showCounts[NUM_HORSES] = {0};   
    srand(time(NULL));
        for (int sim = 0; sim < NUM_SIMULATIONS; sim++) {
            resetPositions(positions);   
            for (int i = 0; i < NUM_HORSES; i++) {
                horses[i].stamina = 10; 
            }
            simulateRace(horses, positions, horseIndices);

            winCounts[horseIndices[0]]++;
            placeCounts[horseIndices[1]]++;
            showCounts[horseIndices[2]]++;
        }


        printf("\nProbabilities (over %d simulations):\n", NUM_SIMULATIONS);
        for (int i = 0; i < NUM_HORSES; i++) {
            printf("%s:\n", horses[i].name);
            printf("  Win: %.2f%%\n", (winCounts[i] * 100.0) / NUM_SIMULATIONS);
            printf("  Place: %.2f%%\n", (placeCounts[i] * 100.0) / NUM_SIMULATIONS);
            printf("  Show: %.2f%%\n", (showCounts[i] * 100.0) / NUM_SIMULATIONS);
        }
}

