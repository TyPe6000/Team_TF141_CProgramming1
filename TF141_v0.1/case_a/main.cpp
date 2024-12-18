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
		printf("게임을 종료합니다.\n");
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
		printf("원하시는 메뉴를 선택해 주세요.\n");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			battle();
			break;
		case 2:
			printf("게임을 종료합니다.\n");
			return; //무한루프 탈출로 종료
		case 3:
			break;
		default:
			printf("오입력\n");
			break;
		}
	}
}