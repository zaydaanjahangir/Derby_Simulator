#ifndef HORSE_H
#define HORSE_H

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

#endif