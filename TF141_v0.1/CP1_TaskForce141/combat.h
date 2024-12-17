// combat.h ÆÄÀÏ
#ifndef COMBAT_H
#define COMBAT_H

#define EMPTY 0
#define COVER 2
#define HOSTL 3

struct Player {
    int health;
    int ammo;
    int grenades;
    int smokes;
};

void print_grid(int grid[3][5], int x, int y);
void move_tile(int* x, int* y, char direction);
void interact_tile(int grid[3][5], int x, int y, int action);

#endif // COMBAT_H
