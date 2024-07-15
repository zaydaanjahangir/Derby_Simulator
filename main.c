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
    {"Thunderbolt", 10},
    {"Whirlwind", 8},
    {"Eclipse", 9},
    {"Comet", 7}
};

// function prototype for simulateRace
// takes in the horses and positions arrays as arguments and will simulate a race and updates postions
void simulateRace(Horse horses[NUM_HORSES], int positions[]); 

// function prototype for displayResults
// takes in the horses and positions arrays as arguments and prints the final results of the race
void displayResults(Horse horses[NUM_HORSES], int positions[]);

int main() {
    printf("Welcome to the Horse Racing Simulation!\n"); // prints a welcome message

    int positions[NUM_HORSES];  // declares an int array to store horse positions pre & post race
    simulateRace(horses, positions);    // calls the simulateRace function
    displayResults(horses, positions);  // calls the displayResults function
    
    printf("The race is over!\n");      // prints a messsage for the end of the race

    return 0;
}


void simulateRace(Horse horses[], int positions[]) {
    int raceFinished = 0;  // initializes a variable flag to indicate if the race is finished

    while (!raceFinished) { // while flag == 0
        for (int j = 0; j < NUM_HORSES; j++) {  // iterates through each horse in the horses array
            // updates the current position of the horse
            // adds a random value between -1 and 1 to the horse's speed for each step
            positions[j] += horses[j].speed + (rand() % 3) - 1;     

            if (positions[j] >= 100) {  // checks if the current horse has crosse the finish
                printf("%s wins!\n", horses[j].name);   // prints a winning message if the horse has won
                raceFinished = 1;   // sets the flag to 1, indicating that the race is over
                break;  // breaks out of inner loop
            }
        }

        for (int j = 0; j < NUM_HORSES; j++) {  // iterates through the horses
            printf("%s: %d\t", horses[j].name, positions[j]);   // prints the horse's current position
        }
        printf("\n");   
    }
}

void displayResults(Horse horses[], int positions[]) { 
    printf("\nRace Results:\n");    
    for (int i = 0; i < NUM_HORSES; i++) {  // iterates through horses
        printf("%s: %d\n", horses[i].name, positions[i]);  // prints the horse's final position 
    }
}
