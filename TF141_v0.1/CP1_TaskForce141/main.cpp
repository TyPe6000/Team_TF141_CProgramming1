#include <stdio.h>
#include "combat_f.h"
#include "combat.h"

// �ʱ� �޴� �Լ�
void show_menu() {
    printf("1. ���� ����\n");
    printf("2. ����\n");
    printf("����: ");
}

// �� �̵� �Լ�
void move_map(int* x, int* y);

// ���� ��ȣ�ۿ� �Լ�
//void interact_trap() {
   // printf("���� ��ȣ�ۿ� ��...\n");
    // ���� ��ȣ�ۿ� ���� �߰�
//}

int main() {
    int choice;
    int x = 0, y = 0;
    Player player = { 100, 30, 3, 2 }; // �ʱ� �÷��̾� ����

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
}
