#ifndef COMBAT_H
#define COMBAT_H

#define EMPTY 0
#define COVER 2
#define HOSTL 3
#define SMOKE 4

struct Player {
    int health;
    int ammo;
    int grenades;
    int smokes;
};


void print_grid(int grid[5][10], int x, int y);
void move_tile(int* x, int* y, char direction);
void shoot(Player* player, int grid[5][10], int* x, int* y);
void place_enemies_randomly(int grid[5][10], int num_enemies);
void place_covers_randomly(int grid[5][10], int num_covers);
void throw_grenade(Player* player, int grid[5][10], int* x, int* y);
void throw_smoke(Player* player, int grid[5][10], int* x, int* y);
bool is_hit_by_enemy(int grid[5][10], int x, int y, int hit_chance);
bool take_cover(Player* player, int grid[5][10], int* x, int* y);
void check_player_status(Player* player);
bool are_all_enemies_defeated(int grid[5][10]);

#endif // COMBAT_H
