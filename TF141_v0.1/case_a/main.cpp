#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stralign.h>  
#include "main.h"

int main(void)
{
	int select;
	select = drawTitle();
	
	switch (select) {
	case 1:
		system("cls");
		getName();
		mainGame();
		break;
	case 2:
		system("cls");
		printf("������ �����մϴ�.\n");
		break;
	default:
		break;
	}

	return 0;
}

void mainGame() {
	while (1)
	{
		int choice;
		printUI();
		printf("���Ͻô� �޴��� ������ �ּ���.\n");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			battle();
			break;
		case 2:
			printf("������ �����մϴ�.\n");
			return; //���ѷ��� Ż��� ����
		case 3:
			break;
		default:
			printf("���Է�\n");
			break;
		}
	}
}