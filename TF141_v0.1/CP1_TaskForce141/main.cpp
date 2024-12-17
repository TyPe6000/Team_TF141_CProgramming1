#include <stdio.h>
#include "combat_f.h"
#include "combat.h"

// 초기 메뉴 함수
void show_menu() {
    printf("1. 게임 시작\n");
    printf("2. 종료\n");
    printf("선택: ");
}

// 맵 이동 함수
void move_map(int* x, int* y);

// 함정 상호작용 함수
//void interact_trap() {
   // printf("함정 상호작용 중...\n");
    // 함정 상호작용 로직 추가
//}

int main() {
    int choice;
    int x = 0, y = 0;
    Player player = { 100, 30, 3, 2 }; // 초기 플레이어 상태

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
}
