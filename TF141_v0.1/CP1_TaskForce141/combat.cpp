#include <stdio.h>
#include <windows.h> // SetConsoleTextAttribute, HANDLE, GetStdHandle
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()
#include "combat.h"
#include "combat_f.h"

// 색상 정의
#define COLOR_DEFAULT 7
#define COLOR_PLAYER 10
#define COLOR_COVER 14
#define COLOR_HOSTL 12
#define COLOR_SMOKE 8

void set_color_combat(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void print_grid(int grid[5][10], int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == x && j == y) {
                set_color_combat(COLOR_PLAYER);
                printf("[P] "); // 플레이어 위치
            }
            else {
                switch (grid[i][j]) {
                case EMPTY:
                    set_color_combat(COLOR_DEFAULT);
                    printf("[ ] ");
                    break;
                case COVER:
                    set_color_combat(COLOR_COVER);
                    printf("[C] ");
                    break;
                case HOSTL:
                    set_color_combat(COLOR_HOSTL);
                    printf("[E] ");
                    break;
                case SMOKE:
                    set_color_combat(COLOR_SMOKE);
                    printf("[S] ");
                default:
                    set_color_combat(COLOR_DEFAULT);
                    printf("[ ] ");
                    break;
                }
            }
        }
        printf("\n");
    }
    set_color_combat(COLOR_DEFAULT); // 기본 색상으로 복원

}

void check_player_status(Player* player) {
    printf("플레이어 스테이터스: 체력: %d, 탄약: %d, 수류탄: %d, 연막탄: %d\n",
        player->health, player->ammo, player->grenades, player->smokes);
}
void move_tile(int* x, int* y, char direction) {
    switch (direction) {
    case 'w':
        if (*x > 0) (*x)--;
        break;
    case 'a':
        if (*y > 0) (*y)--;
        break;
    case 's':
        if (*x < 4) (*x)++;
        break;
    case 'd':
        if (*y < 9) (*y)++;
        break;
    }
}

void shoot(Player* player, int grid[5][10], int* x, int* y) {
    if (player->ammo <= 0) {
        printf("탄약이 부족합니다!\n");
        return;
    }

    player->ammo--;

    for (int j = *y + 1; j < 10 && j < *y + 6; j++) {
        if (grid[*x][j] == HOSTL) {
            grid[*x][j] = EMPTY;
            printf("적을 처치했습니다!\n");
            return;
        }
    }

    printf("적이 사정거리 내에 없습니다.\n");
}

bool take_cover(Player* player, int grid[5][10], int* x, int* y) {
    for (int j = *y + 1; j <= *y + 2 && j < 10; j++) {
        if (grid[*x][j] == COVER || grid[*x][j] == SMOKE) {
            player->health += 10; // 엄폐 시 체력 회복
            return true;
        }
    }
    return false;
}

void throw_grenade(Player* player, int grid[5][10], int* x, int* y) {
    if (player->grenades <= 0) {
        printf("수류탄이 부족합니다!\n");
        return;
    }

    player->grenades--;

    int target_x = *x;
    int target_y = *y + 3;

    if (target_y >= 10) {
        printf("수류탄을 투척할 수 없는 위치입니다.\n");
        return;
    }

    for (int i = target_x - 1; i <= target_x + 1; i++) {
        for (int j = target_y - 1; j <= target_y + 1; j++) {
            if (i >= 0 && i < 5 && j >= 0 && j < 10 && grid[i][j] == HOSTL) {
                grid[i][j] = EMPTY;
                printf("적을 처치했습니다!\n");
            }
        }
    }
}

void throw_smoke(Player* player, int grid[5][10], int* x, int* y) {
    if (player->smokes <= 0) {
        printf("연막탄이 부족합니다!\n");
        return;
    }

    player->smokes--;

    int target_x = *x;
    int target_y = *y + 1;

    if (target_y >= 10 || grid[target_x][target_y] != EMPTY) {
        printf("연막탄을 투척할 수 없는 위치입니다.\n");
        return;
    }

    grid[target_x][target_y] = SMOKE;
    printf("연막탄을 투척했습니다!\n");
}

bool is_hit_by_enemy(int grid[5][10], int x, int y, int hit_chance) {
    for (int j = 0; j < 10; j++) {
        if (grid[x][j] == HOSTL) {
            int random_value = rand() % 100;
            if (random_value < hit_chance) {
                return true;
            }
        }
    }
    return false;
}

void place_enemies_randomly(int grid[5][10], int num_enemies) {
    int placed = 0;
    while (placed < num_enemies) {
        int x = rand() % 5;
        int y = rand() % 8 + 2; // y=0, y=1을 제외한 위치에 배치
        if (grid[x][y] == EMPTY) {
            grid[x][y] = HOSTL;
            placed++;
        }
    }
}

void place_covers_randomly(int grid[5][10], int num_covers) {
    int placed = 0;
    while (placed < num_covers) {
        int x = rand() % 5;
        int y = rand() % 8 + 2; // y=0, y=1을 제외한 위치에 배치
        if (grid[x][y] == EMPTY) {
            grid[x][y] = COVER;
            placed++;
        }
    }
}

// 모든 적이 처치되었는지 확인하는 함수
bool are_all_enemies_defeated(int grid[5][10]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (grid[i][j] == HOSTL) {
                return false;
            }
        }
    }
    return true;
}