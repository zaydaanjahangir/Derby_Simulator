#include <stdlib.h> 
#include <stdio.h> 
#include <time.h>
#include "betting.h"
#include "race.h"

#define NUM_HORSES 6

void startBetting(const Horse horses[], int odds[], int positions[]) {    
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

void winBet(const Horse horses[], int odds[], const int positions[], int* chosenHorse, int* betAmount) {
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

void showBet(const Horse horses[], int odds[], const int positions[], int* chosenHorse, int* betAmount) {
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

void placeBet(const Horse horses[], int odds[], const int positions[], int* chosenHorse, int* betAmount) {
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
    printf("\nOdds for Today's Race:\n");
    for (int i = 0; i < NUM_HORSES; i++) {
        printf("%d. %s: %d:1\n", i + 1, horses[i].name, odds[i]); 
    }

    printf("\n");
}

void calculateOdds(const Horse horses[], int odds[], int positions[], TrackCondition trackCondition) {
    for (int i = 0; i < NUM_HORSES; i++) {
        int baseOdds = 10; 
        //    Track Condition Bias
        baseOdds -= (horses[i].trackBias[trackCondition]) * 5; 
        // // Ensure odds are at least 1:1
        if (baseOdds < 1) {
            baseOdds = 1;
        }
        odds[i] = baseOdds; // Store calculated odds
    }
}