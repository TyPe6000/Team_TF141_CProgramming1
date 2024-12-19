#include <stdio.h>
#include <conio.h> // _kbhit(), _getch()
#include "combat_f.h"

#define EMPTY 0
#define BLKED 1
#define BATTLE 2

void print_map(int map[5][10], int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == x && j == y) {
                printf("[P] "); // �÷��̾� ��ġ
            }
            else {
                switch (map[i][j]) {
                case EMPTY:
                    printf("[ ] ");
                    break;
                case BLKED:
                    printf("[#] ");
                    break;
                case BATTLE:
                    printf("[B] ");
                    break;
                default:
                    printf("[ ] ");
                    break;
                }
            }
        }
        printf("\n");
    }
}

void move_map(int* x, int* y, Player* player) {
    char command;
    int map[5][10] = {
        {EMPTY, EMPTY, EMPTY, EMPTY, BATTLE, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLKED, BLKED, EMPTY, EMPTY, EMPTY, BLKED, BLKED, BLKED, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, BLKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLKED, BLKED, EMPTY, EMPTY, EMPTY, BLKED, BLKED, BLKED, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    printf("�� �̵��� �����մϴ�.\n");
    print_map(map, *x, *y);
    printf("����� �Է��ϼ��� (w/a/s/d: �̵�, q: ����): ");

    while (1) {
        if (_kbhit()) {
            command = _getch();

            int new_x = *x;
            int new_y = *y;

            switch (command) {
            case 'w':
                if (new_x > 0) new_x--;
                break;
            case 'a':
                if (new_y > 0) new_y--;
                break;
            case 's':
                if (new_x < 4) new_x++;
                break;
            case 'd':
                if (new_y < 9) new_y++;
                break;
            case 'q':
                return;
            default:
                printf("�߸��� ����Դϴ�.\n");
                continue;
            }

            if (map[new_x][new_y] == BLKED) {
                printf("�̵��� �� ���� ��ġ�Դϴ�.\n");
            }
            else {
                *x = new_x;
                *y = new_y;
                if (map[*x][*y] == BATTLE) {
                    printf("������ �����մϴ�!\n");
                    return;
                }
            }

            printf("\n");
            print_map(map, *x, *y);
            printf("����� �Է��ϼ��� (w/a/s/d: �̵�, q: ����): ");
        }
    }
}
