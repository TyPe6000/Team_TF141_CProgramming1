#include <stdio.h>
#include <conio.h> // _kbhit(), _getch()
#include "combat.h"
#include "combat_f.h"

void combat(Player* player) {
    char command;
    int x = 0, y = 0;
    int grid[3][5] = { {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
                       {EMPTY, COVER, EMPTY, HOSTL, EMPTY},
                       {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY} };

    printf("������ �����մϴ�.\n");
    print_grid(grid, x, y);
    printf("����� �Է��ϼ��� (w/a/s/d: �̵�, 1:���, q: ����): ");

    while (1) {
        if (_kbhit()) {
            command = _getch();

            if (command == 'q') {
                break;
            }

            if (command == 'w' || command == 'a' || command == 's' || command == 'd') {
                move_tile(&x, &y, command);
            }
			if (command == '1') {
				shoot(player, grid, &x, &y);
			}
            else if (command >= '2' && command <= '5') {
                interact_tile(grid, x, y, command - '0');
            }
            else {
                printf("�߸��� ����Դϴ�.\n");
            }

            // ȭ���� �����մϴ�.
            printf("\n");
            print_grid(grid, x, y);
            printf("����� �Է��ϼ��� (w/a/s/d: �̵�, 1:���, q: ����): ");
        }
    }

    printf("������ �����մϴ�.\n");
}