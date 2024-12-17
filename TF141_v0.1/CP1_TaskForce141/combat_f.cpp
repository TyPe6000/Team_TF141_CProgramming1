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

    printf("전투를 시작합니다.\n");
    print_grid(grid, x, y);
    printf("명령을 입력하세요 (w/a/s/d: 이동, 1:사격, q: 종료): ");

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
                printf("잘못된 명령입니다.\n");
            }

            // 화면을 갱신합니다.
            printf("\n");
            print_grid(grid, x, y);
            printf("명령을 입력하세요 (w/a/s/d: 이동, 1:사격, q: 종료): ");
        }
    }

    printf("전투를 종료합니다.\n");
}