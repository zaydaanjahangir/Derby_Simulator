#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include "race.h"
#include "horse.h"

#define NUM_HORSES 6

void simulateRace(Horse horses[], int positions[], int horseIndices[]) {
    int raceFinished = 0;   // flag to indicate if race is over
    srand(time(NULL)); // Initialize random number generator

    while (!raceFinished) { // while the race isn't over (flag == 0)
        for (int j = 0; j < NUM_HORSES; j++) {

            if (horses[j].stamina > 0) {
                positions[j] += horses[j].speed + (rand() % 3) - 1;

                // Stamina Depletion based on Jockey Skill
                int staminaReduction = 1 - (horses[j].jockey.skill / 20.0); // Skill 10 reduces depletion by 0.5

                // Ensure at least 1 stamina is lost
                if (staminaReduction < 1) {
                    staminaReduction = 1;
                }

                horses[j].stamina -= staminaReduction; 
            } else {
                positions[j] += horses[j].speed / 2; // Slower if out of stamina
            }
            
            if (positions[j] >= 100) {  // Check if a horse has finished
                raceFinished = 1;
                break;
            }
        }
    }

    for (int i = 0; i < NUM_HORSES - 1; i++) {
        for (int j = 0; j < NUM_HORSES - i - 1; j++) {
            if (positions[j] < positions[j + 1]) {
                // Swap positions[j] and positions[j+1]
                int temp = positions[j];
                positions[j] = positions[j + 1];
                positions[j + 1] = temp;

                // Swap horses[j] and horses[j+1] to maintain the correct order
                Horse tempHorse = horses[j];
                horses[j] = horses[j + 1];
                horses[j + 1] = tempHorse;

                // Swap horseIndices[j] and horseIndices[j + 1]
                int tempIndex = horseIndices[j];
                horseIndices[j] = horseIndices[j + 1];
                horseIndices[j + 1] = tempIndex;
            }
        }
    }
}

void displayResults(const Horse horses[], const int positions[]) {
    // Print the sorted results (arrays are already sorted in simulateRace)
    printf("\nRace Results:\n");
    for (int i = 0; i < NUM_HORSES; i++) {
        if (i == 0) {
            printf("Winner: %s: %d\n", horses[i].name, positions[i]); 
        } else if (i == 1) {
            printf("Place: %s: %d\n", horses[i].name, positions[i]);
        } else if (i == 2) {
            printf("Show: %s: %d\n", horses[i].name, positions[i]);
        } else {
            printf("%d. %s: %d\n", i + 1, horses[i].name, positions[i]);
        }
    }
}

void resetPositions(int positions[]) {
    for (int i = 0; i < NUM_HORSES; i++) {
        positions[i] = 0;
    }
}
