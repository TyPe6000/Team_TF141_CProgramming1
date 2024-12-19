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
    int x = 2, y = 0; // 플레이어 초기 위치

    place_enemies_randomly(grid, 5); // 적 5명을 랜덤으로 배치
	place_covers_randomly(grid, 3); // 엄폐물 3개를 랜덤으로 배치

    srand(static_cast<unsigned int>(time(0))); // 랜덤 시드 설정

    printf("전투 시작!\n");
    print_grid(grid, x, y);
	check_player_status(player);
	printf("행동을 선택하세요 (w/a/s/d: 이동, 1: 사격, 2: 엄폐, 3: 수류탄, 4: 연막탄): ");

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
                    printf("엄폐 성공! 체력이 회복되었습니다. 현재 체력: %d\n", player->health);
                }
                else {
                    printf("엄폐할 수 없습니다. 우측 2칸 이내에 엄폐할 수 있는 타일이 없습니다.\n");
                }
                break;
            case '3':
                throw_grenade(player, grid, &x, &y);
				break;
			case '4':
				throw_smoke(player, grid, &x, &y);
				break;
			default:
				printf("잘못된 명령입니다. 다시 시도하세요.\n");
				break;
			}
            // 적이 모두 처치되었는지 확인
            if (are_all_enemies_defeated(grid)) {
                printf("모든 적을 처치했습니다!\n");
                break;
            }
            // 피격 확률 계산
            if (is_hit_by_enemy(grid, x, y, 40)) { // 40% 확률로 피격
                player->health -= 10; // 피격 시 체력 감소
                printf("적의 공격을 받았습니다! 현재 체력: %d\n", player->health);
                if (player->health <= 0) {
                    printf("플레이어가 사망했습니다. 게임 오버.\n");
                    return;
                }
            }
            printf("\n");
            print_grid(grid, x, y);
			check_player_status(player);
            printf("행동을 선택하세요 (w/a/s/d: 이동, 1: 사격, 2: 엄폐, 3: 수류탄, 4: 연막탄): \n");
		}
    }
}

