#include <stdio.h>
#include <conio.h> // _kbhit(), _getch()
                        // 키보드 단일 입력으로 상호작용하기 위한 헤더 파일
#include <windows.h> // SetConsoleTextAttribute, HANDLE, GetStdHandle
                        // 색상 표현 등을 위한 헤더 파일
#include "combat_f.h"
#include "combat.h"

#define EMPTY 0
#define BLKED 1
#define BATTLE 2
#define GOAL 3

#define COLOR_EMPTY 7
#define COLOR_BLKED 8
#define COLOR_BATTLE 12
#define COLOR_GOAL 10

void set_color_move(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 초기 메뉴 함수
void show_menu() {
    printf("1. 게임 시작\n");
    printf("2. 종료\n");
    printf("선택: ");
}

void print_map(int map[5][10], int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == x && j == y) {
				set_color_move(COLOR_EMPTY);
                printf("[P] "); // 플레이어 위치
            }
            else {
                switch (map[i][j]) {
                case EMPTY:
					set_color_move(COLOR_EMPTY);
                    printf("[ ] ");
                    break;
                case BLKED:
					set_color_move(COLOR_BLKED);
                    printf("[#] ");
                    break;
                case BATTLE:
					set_color_move(COLOR_BATTLE); 
                    printf("[B] ");
                    break;
				case GOAL:
					set_color_move(COLOR_GOAL);
					printf("[G] ");
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

// 도착 지점에 도착했는지 확인하는 함수
bool is_at_destination(int* x, int* y) {
    // 도착 지점의 좌표를 (4, 9)로 가정
    return (*x == 0 && *y == 9);
}

void move_map(int* x, int* y, Player* player) {
    char command;
    int map[5][10] = {
        {EMPTY, EMPTY, EMPTY, EMPTY, BATTLE, EMPTY, EMPTY, EMPTY, EMPTY, GOAL},
        {EMPTY, BLKED, BLKED, EMPTY, EMPTY, EMPTY, BLKED, BLKED, BLKED, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, BLKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, BLKED, BLKED, EMPTY, EMPTY, EMPTY, BLKED, BLKED, BLKED, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };

    printf("맵 이동을 시작합니다.\n");
    print_map(map, *x, *y);
    printf("명령을 입력하세요 (w/a/s/d: 이동, q: 종료): ");

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
                printf("잘못된 명령입니다.\n");
                continue;
            }
            // 도착 지점에 도착했는지 확인
            if (is_at_destination(x, y)) {
                printf("도착 지점에 도착했습니다! 게임 클리어!\n");
                // 다시 시작 화면으로 돌아가기
                return;
            }

            if (map[new_x][new_y] == BLKED) {
                printf("이동할 수 없는 위치입니다.\n");
            }
            else {
                *x = new_x;
                *y = new_y;
                if (map[*x][*y] == BATTLE) {
                    printf("전투에 진입합니다!\n");
                    int saved_x = *x;
                    int saved_y = *y;
                    combat(player);
                    *x = saved_x;
                    *y = saved_y;
                    printf("전투가 끝났습니다. 이동을 계속합니다.\n");
                }
            }

            printf("\n");
            print_map(map, *x, *y);
            printf("명령을 입력하세요 (w/a/s/d: 이동, q: 종료): ");
        }
    }
}

int main() {
    int choice;
    int x = 0, y = 0;
    Player player = { 100, 10, 3, 2 }; // 초기 플레이어 상태

    while (1) {
        show_menu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            move_map(&x, &y, &player);
            break;
        case 2:
            printf("게임을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }

    return 0;
}
/*int main() {
    int choice;
    int x = 0, y = 0;
    Player player = { 100, 10, 3, 2 }; // 초기 플레이어 상태

    while (1) {
        show_menu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            move_map(&x, &y);
            if (x == 0 && y == 4) { // 전투 위치에 도달했을 때
                combat(&player);
			}
            break;
        case 2:
            printf("게임을 종료합니다.\n");
            return 0;
        default:
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
            break;
        }
    }

    return 0;
}*/
