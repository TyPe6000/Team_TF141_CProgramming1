#include <stdio.h>
#include <windows.h> // SetConsoleTextAttribute, HANDLE, GetStdHandle
#include "combat.h"

// 색상 정의
#define COLOR_DEFAULT 7
#define COLOR_PLAYER 10
#define COLOR_COVER 14
#define COLOR_HOSTL 12

void set_color(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void print_grid(int grid[3][5], int x, int y) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == x && j == y) {
                set_color(COLOR_PLAYER);
                printf("[P] "); // 플레이어 위치
            }
            else {
                switch (grid[i][j]) {
                case EMPTY:
                    set_color(COLOR_DEFAULT);
                    printf("[ ] ");
                    break;
                case COVER:
                    set_color(COLOR_COVER);
                    printf("[C] ");
                    break;
                case HOSTL:
                    set_color(COLOR_HOSTL);
                    printf("[E] ");
                    break;
                default:
                    set_color(COLOR_DEFAULT);
                    printf("[ ] ");
                    break;
                }
            }
        }
        printf("\n");
    }
    set_color(COLOR_DEFAULT); // 기본 색상으로 복원
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
        if (*x < 2) (*x)++;
        break;
    case 'd':
        if (*y < 4) (*y)++;
        break;
    }
}

void shoot(Player* player, int grid[3][5], int* x, int* y) {
    if (player->ammo <= 0) {
        printf("탄약이 부족합니다!\n");
        return;
    }

    player->ammo--;

    for (int i = *x; i < 3 && i < *x + 5; i++) {
        if (grid[i][*y] == HOSTL) {
            grid[i][*y] = EMPTY;
            printf("적을 처치했습니다!\n");
            return;
        }
    }

    printf("적이 사정거리 내에 없습니다.\n");
}

void interact_tile(int grid[3][5], int x, int y, int action) {
    grid[x][y] = action;
}
