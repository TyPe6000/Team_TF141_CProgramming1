#include <stdio.h>
#include <conio.h> // _kbhit(), _getch()
                        // Ű���� ���� �Է����� ��ȣ�ۿ��ϱ� ���� ��� ����
#include <windows.h> // SetConsoleTextAttribute, HANDLE, GetStdHandle
                        // ���� ǥ�� ���� ���� ��� ����
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

// �ʱ� �޴� �Լ�
void show_menu() {
    printf("1. ���� ����\n");
    printf("2. ����\n");
    printf("����: ");
}

void print_map(int map[5][10], int x, int y) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            if (i == x && j == y) {
				set_color_move(COLOR_EMPTY);
                printf("[P] "); // �÷��̾� ��ġ
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

// ���� ������ �����ߴ��� Ȯ���ϴ� �Լ�
bool is_at_destination(int* x, int* y) {
    // ���� ������ ��ǥ�� (4, 9)�� ����
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
            // ���� ������ �����ߴ��� Ȯ��
            if (is_at_destination(x, y)) {
                printf("���� ������ �����߽��ϴ�! ���� Ŭ����!\n");
                // �ٽ� ���� ȭ������ ���ư���
                return;
            }

            if (map[new_x][new_y] == BLKED) {
                printf("�̵��� �� ���� ��ġ�Դϴ�.\n");
            }
            else {
                *x = new_x;
                *y = new_y;
                if (map[*x][*y] == BATTLE) {
                    printf("������ �����մϴ�!\n");
                    int saved_x = *x;
                    int saved_y = *y;
                    combat(player);
                    *x = saved_x;
                    *y = saved_y;
                    printf("������ �������ϴ�. �̵��� ����մϴ�.\n");
                }
            }

            printf("\n");
            print_map(map, *x, *y);
            printf("����� �Է��ϼ��� (w/a/s/d: �̵�, q: ����): ");
        }
    }
}

int main() {
    int choice;
    int x = 0, y = 0;
    Player player = { 100, 10, 3, 2 }; // �ʱ� �÷��̾� ����

    while (1) {
        show_menu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            move_map(&x, &y, &player);
            break;
        case 2:
            printf("������ �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }

    return 0;
}
/*int main() {
    int choice;
    int x = 0, y = 0;
    Player player = { 100, 10, 3, 2 }; // �ʱ� �÷��̾� ����

    while (1) {
        show_menu();
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            move_map(&x, &y);
            if (x == 0 && y == 4) { // ���� ��ġ�� �������� ��
                combat(&player);
			}
            break;
        case 2:
            printf("������ �����մϴ�.\n");
            return 0;
        default:
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
            break;
        }
    }

    return 0;
}*/
