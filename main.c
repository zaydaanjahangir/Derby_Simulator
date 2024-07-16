#include <stdio.h> // for printing to console and user input
#include <stdlib.h> // rand for random numbers
#include <string.h> // string manipulation
#include <time.h>  // seeds rng

#define NUM_HORSES 6 // defines constant NUM_HORSES with a value of 6
#define NUM_SIMULATIONS 1000


typedef struct {
    char name[15];
    int skill; // Skill level (1-10, for example)
} Jockey;


typedef struct {
    char name[15];  
    int speed;
    int stamina;
    Jockey jockey; // Add the Jockey structure member
} Horse;

Horse horses[NUM_HORSES] = {   
    {"Thunderbolt", 8, 10, {"Johnny J.", 7}}, // 26
    {"Whirlwind", 8, 10, {"Mickey P.", 7}},   // 28
    {"Eclipse", 8, 10, {"Laura H.", 7}},       // 24
    {"Comet", 8, 10, {"John S.", 7}},         // 23
    {"Volcano", 8, 10, {"Hiton H.", 7}},       // 22
    {"Monsoon", 8, 10, {"Mike M.", 7}}        // 26
};


// Updated function prototypes
void simulateRace(Horse horses[NUM_HORSES], int positions[], int horseIndices[]);
void displayResults(Horse horses[NUM_HORSES], int positions[]);
void startBetting(const Horse horses[], const int odds[], int positions[]);
void winBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount);
void showBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount);
void placeBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount);
void displayOdds(const Horse horses[], int odds[]); // Updated prototype
void resetPositions(int positions[]);

void resetPositions(int positions[]) {
    for (int i = 0; i < NUM_HORSES; i++) {
        positions[i] = 0;
    }
}

int main() {
    printf("Welcome to the Horse Racing Simulation!\n");
    int isBetting;      // stores user's decision to bet
    printf("Would you like to bet today? (1 for yes, 0 for no)\n");
    scanf("%d", &isBetting);    // get user input for if they want to bet
    
    int positions[NUM_HORSES] = {0};    // declares and initializes an array of horse positions to 0
    int odds[NUM_HORSES];           // declares an array odds to store the odds for each horse
    int winCounts[NUM_HORSES] = {0};      // Array to count wins for each horse
    int placeCounts[NUM_HORSES] = {0};   // Array to count place finishes
    int showCounts[NUM_HORSES] = {0};    // Array to count show finishes

    int horseIndices[NUM_HORSES];
    for (int i = 0; i < NUM_HORSES; i++) {
        horseIndices[i] = i; 
    }

    if(isBetting == 3){
        srand(time(NULL)); // Initialize random number generator
        for (int sim = 0; sim < NUM_SIMULATIONS; sim++) {
            resetPositions(positions);   
            for (int i = 0; i < NUM_HORSES; i++) {
                horses[i].stamina = 10; 
            }
            simulateRace(horses, positions, horseIndices);

            // Correctly update the win, place, and show count for each horse based on sorted positions
            winCounts[horseIndices[0]]++;
            placeCounts[horseIndices[1]]++;
            showCounts[horseIndices[2]]++;
        }

        // Calculate probabilities for each horse
        printf("\nProbabilities (over %d simulations):\n", NUM_SIMULATIONS);
        for (int i = 0; i < NUM_HORSES; i++) {
            printf("%s:\n", horses[i].name);
            printf("  Win: %.2f%%\n", (winCounts[i] * 100.0) / NUM_SIMULATIONS);
            printf("  Place: %.2f%%\n", (placeCounts[i] * 100.0) / NUM_SIMULATIONS);
            printf("  Show: %.2f%%\n", (showCounts[i] * 100.0) / NUM_SIMULATIONS);
        }
        return 0;
    }

    simulateRace(horses, positions, horseIndices);    // simulates the race and updates the positions array
    
    if (isBetting) {        // if the user is betting
        srand(time(NULL));  // gets a random time as a seed for rng
        printf("\n");
        startBetting(horses, odds, positions);  // starts the betting process
    } else {
        displayResults(horses, positions);  // displays the results
    }
    return 0;
}

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

void displayResults(Horse horses[], int positions[]) {
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

void startBetting(const Horse horses[], const int odds[], int positions[]) {    
    int betType, chosenHorse, betAmount;    // stores the type of bet, horse user chose, and bet amount
    printf("What type of bet would you like to make? (1: Win, 2: Place, 3: Show): ");
    scanf("%d", &betType); // gets the type of bet

    if (betType == 1) {
        winBet(horses, odds, positions, &chosenHorse, &betAmount);
    } else if (betType == 2) {
        placeBet(horses, odds, positions, &chosenHorse, &betAmount);
    } else if (betType == 3) {
        showBet(horses, odds, positions, &chosenHorse, &betAmount);
    } else {
        printf("Error: Invalid bet type.\n");
    }
}

void winBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount) {
    printf("Well aren't you bold, here are the odds for today\n");
    displayOdds(horses, odds); // shows the odds for the user to choose from

    printf("Which horse would you like to bet on? (Enter a number 1-%d): ", NUM_HORSES);
    scanf("%d", chosenHorse); // stores the chosen horse

    // Validates chosenHorse
    while (*chosenHorse < 1 || *chosenHorse > NUM_HORSES) {
        printf("Invalid horse number. Please enter a number between 1 and %d: ", NUM_HORSES);
        scanf("%d", chosenHorse);
    }

    printf("And how much would you like to bet (limit $10,000): ");
    scanf("%d", betAmount); // gets the amount the user wants to be
    printf("Good luck!\n");

    // Check if the chosen horse won (index 0 in the sorted positions array)
    if (*chosenHorse - 1 == 0) {
        int winnings = (*betAmount) * odds[*chosenHorse - 1];
        displayResults(horses, positions);
        printf("\nCongratulations! You won $%d\n", winnings);
    } else {
        displayResults(horses, positions);
        printf("\nSorry, your horse didn't win.\n");
    }
}

void showBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount) {
    printf("Playing it safe, here are the odds for today\n");
    displayOdds(horses, odds);

    printf("Which horse would you like to bet on? (Enter a number 1-%d): ", NUM_HORSES);
    scanf("%d", chosenHorse);

    // Validate chosenHorse
    while (*chosenHorse < 1 || *chosenHorse > NUM_HORSES) {
        printf("Invalid horse number. Please enter a number between 1 and %d: ", NUM_HORSES);
        scanf("%d", chosenHorse);
    }

    printf("And how much would you like to bet (limit $10,000): ");
    scanf("%d", betAmount);

    // Check if the chosen horse won (index 0 in the sorted positions array)
    if (*chosenHorse - 1 == 0 || *chosenHorse - 1 == 1 || *chosenHorse - 1 == 2) {
        int winnings = (*betAmount) * odds[*chosenHorse - 1];
        displayResults(horses, positions);
        printf("\nCongratulations! You won $%d\n", winnings);
    } else {
        displayResults(horses, positions);
        printf("\nSorry, your horse didn't win.\n");
    }
}

void placeBet(const Horse horses[], const int odds[], const int positions[], int* chosenHorse, int* betAmount) {
    printf("A place bet, eh? Here are the odds for today\n");
    displayOdds(horses, odds);
    
    printf("Which horse would you like to bet on? (Enter a number 1-%d): ", NUM_HORSES);
    scanf("%d", chosenHorse);

    // Validate chosenHorse
    while (*chosenHorse < 1 || *chosenHorse > NUM_HORSES) {
        printf("Invalid horse number. Please enter a number between 1 and %d: ", NUM_HORSES);
        scanf("%d", chosenHorse);
    }

    printf("And how much would you like to bet (limit $10,000): ");
    scanf("%d", betAmount);

    if (*chosenHorse - 1 == 0 || *chosenHorse - 1 == 1) {
        int winnings = (*betAmount) * odds[*chosenHorse - 1];
        displayResults(horses, positions);
        printf("\nCongratulations! You won $%d\n", winnings);
    } else {
        displayResults(horses, positions);
        printf("\nSorry, your horse didn't win.\n");
    }
}

void displayOdds(const Horse horses[], int odds[]) {
    srand(time(NULL)); // Initialize random number generator again for odds
    for (int i = 0; i < NUM_HORSES; i++) {
        odds[i] = rand() % 10 + 1; // Random odds between 1 and 10
    }

    printf("\nOdds for Today's Race:\n");
    for (int i = 0; i < NUM_HORSES; i++) {
        printf("%d. %s: %d:1\n", i + 1, horses[i].name, odds[i]); 
    }

    printf("\n");
}
