#include <stdio.h> // for printing to console and user input
#include <stdlib.h> // rand for random numbers
#include <string.h> // string manipulation
#include <time.h>  // seeds rng

#define NUM_HORSES 6 // defines constant NUM_HORSES with a value of 6

typedef struct {    // New data type called horse
    char name[15];  // A char array/string to store a horses name
    int speed;      // an integer to store the horses speed
} Horse;


Horse horses[NUM_HORSES] = {    // creates an array that can hold 4 horses
    {"Thunderbolt", 8},
    {"Whirlwind", 8},
    {"Eclipse", 8},
    {"Comet", 8},
    {"Volcano", 8},
    {"Monsoon", 8}
};


// Updated function prototypes
void simulateRace(Horse horses[NUM_HORSES], int positions[]);
void displayResults(Horse horses[NUM_HORSES], int positions[]);
void startBetting(const Horse horses[], const int odds[], int positions[]);
void winBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount);
void showBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount);
void placeBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount);
void displayOdds(const Horse horses[], int odds[]); // Updated prototype


int main() {
    printf("Welcome to the Horse Racing Simulation!\n");
    int isBetting;
    printf("Would you like to bet today? (1 for yes, 0 for no)\n");
    scanf("%d", &isBetting);
    

    int positions[NUM_HORSES] = {0};
    int odds[NUM_HORSES];
    
    simulateRace(horses, positions);
    
    if (isBetting) {
        srand(time(NULL)); 
        printf("\n");
        startBetting(horses, odds, positions);
    }

    
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
                raceFinished = 1;
                break; 
            }
        }

        // // Print positions for debugging
        // for (int j = 0; j < NUM_HORSES; j++) {
        //     printf("%s: %d\t", horses[j].name, positions[j]);
        // }
        // printf("\n");
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

void startBetting(const Horse horses[], const int odds[], int positions[]) {
    int betType, chosenHorse, betAmount;
    printf("What type of bet would you like to make? (1: Win, 2: Place, 3: Show): ");
    scanf("%d", &betType);

    if (betType == 1) {
        winBet(horses, odds, positions, &chosenHorse, &betAmount);
    } else if (betType == 2) {
        showBet(horses, odds, positions, &chosenHorse, &betAmount);
    } else if (betType == 3) {
        placeBet(horses, odds, positions, &chosenHorse, &betAmount);
    } else {
        printf("Error: Invalid bet type.\n");
    }
}

void winBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount) {
    printf("Well aren't you bold, here are the odds for today\n");
    displayOdds(horses, odds);

    printf("Which horse would you like to bet on? (Enter a number 1-%d): ", NUM_HORSES);
    scanf("%d", chosenHorse);

    // Validate chosenHorse (same as before)
    while (*chosenHorse < 1 || *chosenHorse > NUM_HORSES) {
        // ... (error message and input prompt)
    }

    printf("And how much would you like to bet (limit $10,000): ");
    scanf("%d", betAmount);
    printf("Good luck!\n");


    // Use dereferenced values in the calculation
    if (positions[*chosenHorse - 1] >= 100) {
        int winnings = (*betAmount) * odds[*chosenHorse - 1];
        printf("Congratulations! You won $%d\n", winnings);
    } else {
        printf("Sorry, your horse didn't win.\n");
    }
}

void showBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount){}

void placeBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount){}

void displayOdds(const Horse horses[], int odds[]) {
    srand(time(NULL)); // Initialize random number generator again for odds
    for (int i = 0; i < NUM_HORSES; i++) {
        odds[i] = rand() % 10 + 1; // Random odds between 1 and 10
    }

    printf("\nOdds for Today's Race:\n");
    for (int i = 0; i < NUM_HORSES; i++) {
        printf("%s: %d:1\n", horses[i].name, odds[i]);
    }

    printf("\n");
}
