# C Horse Racing Simulation

Welcome to the thrilling world of virtual horse racing! This C-based simulation brings the excitement of the track to your terminal, offering a fun and interactive betting experience.

## Features

- **Realistic Race Simulation:** Watch as horses with different speeds and stamina compete in a thrilling race to the finish line.
- **Jockey Influence:** Skilled jockeys can make a difference, managing their horses' stamina and potentially influencing the outcome.
- **Dynamic Odds:** The odds for each horse are calculated based on various factors like speed, stamina, jockey skill, and track conditions.
- **Betting Options:** Place win, place, or show bets and test your luck against the odds.
- **Simulation Mode:** Analyze the horses' performance over 1000 simulated races to get insights into their winning probabilities.

## How to Use

1. **Compilation:** Make sure you have a C compiler (e.g., GCC) installed. Compile the project using the following command:
    ```bash
    gcc -o horse_race *.c
    ```

2. **Run the Simulation:**
    ```bash
    ./horse_race
    ```

### Betting (Optional)
- You'll be asked if you want to bet. Enter `1` for yes or `0` for no.
- Choose your bet type (win, place, or show).
- Select the horse you want to bet on (1-6).
- Enter your bet amount (up to $10,000).
- Watch the race unfold and see if you've won!

### Simulation Mode
- Enter `3` when prompted if you want to bet.
- The program will simulate 1000 races and display the probability of each horse winning, placing, or showing.

## Future Plans
- **More Complex Odds:** Implement more sophisticated odds calculations that factor in historical performance, recent form, and potentially even betting patterns.
- **Track Variety:** Add different types of tracks with varying lengths and conditions.
- **Graphical User Interface (GUI):** Enhance the user experience with a graphical interface that visually simulates the race.
- **Horse Upgrades:** Allow players to train and improve their horses over time.
- **Multiplayer Mode:** Enable players to compete against each other online.
- **Customizable Horses and Jockeys:** Let players create and customize their own horses and jockeys.


