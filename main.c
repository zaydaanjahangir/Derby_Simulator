#include <stdio.h> // for printing to console and user input
#include <stdlib.h> // rand for random numbers
#include <string.h> // string manipulation
#include <time.h>  // seeds rng

#define NUM_HORSES 4 // defines constant NUM_HORSES with a value of 4

typedef struct {    // New data type called horse
    char name[15];  // A char array/string to store a horses name
    int speed;      // an integer to store the horses speed
} Horse;


Horse horses[NUM_HORSES] = {    // creates an array that can hold 4 horses
    {"Thunderbolt", 8},
    {"Whirlwind", 8},
    {"Eclipse", 8},
    {"Comet", 8}
};

// function prototype for simulateRace
// takes in the horses and positions arrays as arguments and will simulate a race and updates postions
void simulateRace(Horse horses[NUM_HORSES], int positions[]); 

// function prototype for displayResults
// takes in the horses and positions arrays as arguments and prints the final results of the race
void displayResults(Horse horses[NUM_HORSES], int positions[]);


int main() {
    printf("Welcome to the Horse Racing Simulation!\n");

    int positions[NUM_HORSES] = {0}; // Initialize positions ONCE in main
    simulateRace(horses, positions);  // Pass it to simulateRace
    displayResults(horses, positions);

    printf("The race is over!\n\n");
    return 0;
}


void simulateRace(Horse horses[], int positions[]) {
    int raceFinished = 0;
    srand(time(NULL)); // Initialize random number generator

    while (!raceFinished) {
        for (int j = 0; j < NUM_HORSES; j++) {
            positions[j] += horses[j].speed + (rand() % 3) - 1;

            if (positions[j] >= 100) {
                printf("%s wins!\n", horses[j].name);
                raceFinished = 1;
                break; 
            }
        }

        // Print positions for debugging
        for (int j = 0; j < NUM_HORSES; j++) {
            printf("%s: %d\t", horses[j].name, positions[j]);
        }
        printf("\n");
    }
}

void displayResults(Horse horses[], int positions[]) {
    // Sort positions array in descending order
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
            }
        }
    }

    // Print the sorted results
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


