#include "combat_f.h"

#include <windows.h> // SetConsoleTextAttribute, HANDLE, GetStdHandle
#include <stdio.h>
#include <conio.h> // _kbhit(), _getch()
#include <cstdlib>   // rand(), srand()
#include <ctime>     // time()



void combat(Player* player) {
    int action;
    int grid[5][10] = {
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
        {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
    };
    int x = 2, y = 0; // �÷��̾� �ʱ� ��ġ

    place_enemies_randomly(grid, 5); // �� 5���� �������� ��ġ
	place_covers_randomly(grid, 3); // ���� 3���� �������� ��ġ

    srand(static_cast<unsigned int>(time(0))); // ���� �õ� ����

    printf("���� ����!\n");
    print_grid(grid, x, y);
	check_player_status(player);
	printf("�ൿ�� �����ϼ��� (w/a/s/d: �̵�, 1: ���, 2: ����, 3: ����ź, 4: ����ź): ");

    while (1)
    {
		if (_kbhit())
		{
			action = _getch();
			switch (action)
			{
			case 'w':
				move_tile(&x, &y, 'w');
				break;
			case 'a':
				move_tile(&x, &y, 'a');
				break;
			case 's':
				move_tile(&x, &y, 's');
				break;
			case 'd':
				move_tile(&x, &y, 'd');
				break;
			case '1':
				shoot(player, grid, &x, &y);
				break;
            case '2':
                if (take_cover(player, grid, &x, &y)) {
                    printf("���� ����! ü���� ȸ���Ǿ����ϴ�. ���� ü��: %d\n", player->health);
                }
                else {
                    printf("������ �� �����ϴ�. ���� 2ĭ �̳��� ������ �� �ִ� Ÿ���� �����ϴ�.\n");
                }
                break;
            case '3':
                throw_grenade(player, grid, &x, &y);
				break;
			case '4':
				throw_smoke(player, grid, &x, &y);
				break;
			default:
				printf("�߸��� ����Դϴ�. �ٽ� �õ��ϼ���.\n");
				break;
			}
            // ���� ��� óġ�Ǿ����� Ȯ��
            if (are_all_enemies_defeated(grid)) {
                printf("��� ���� óġ�߽��ϴ�!\n");
                break;
            }
            // �ǰ� Ȯ�� ���
            if (is_hit_by_enemy(grid, x, y, 40)) { // 40% Ȯ���� �ǰ�
                player->health -= 10; // �ǰ� �� ü�� ����
                printf("���� ������ �޾ҽ��ϴ�! ���� ü��: %d\n", player->health);
                if (player->health <= 0) {
                    printf("�÷��̾ ����߽��ϴ�. ���� ����.\n");
                    return;
                }
            }
            printf("\n");
            print_grid(grid, x, y);
			check_player_status(player);
            printf("�ൿ�� �����ϼ��� (w/a/s/d: �̵�, 1: ���, 2: ����, 3: ����ź, 4: ����ź): \n");
		}
    }
}

