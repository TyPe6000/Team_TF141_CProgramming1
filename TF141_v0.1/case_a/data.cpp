#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stralign.h>  
#include <time.h>
#include <conio.h>
#include "main.h"

//키보드 입력값
#define UP 0
#define DOWN 1
#define SUBMIT 2

Character chara;
Enemy enemy;

void gotoxy(int x, int y) { // 커서 조종 함수
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // 콘솔 핸들 가져오기
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void SetColor(int color) //색 지정 함수
{
	/*
		검정 0
		어두운 파랑 1
		어두운 초록 2
		어두운 하늘 3
		어두운 빨강 4
		어두운 보라 5
		어두운 노랑 6
		회색 7
		어두운 회색 8
		파랑 9
		초록 10
		하늘 11
		빨강 12
		보라 13
		노랑 14
		하양 15
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show) //콘솔 커서 표시 함수
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int drawTitle() { //로고 출력 함수
	int x = 25, y = 12;
	printf("\n\t #######    #######      #      #            #   \n");
	printf("\t    #       #           ##      #    #      ##     \n");
	printf("\t    #       #          # #      #    #     # #     \n");
	printf("\t    #       #####        #      #    #       #     \n");
	printf("\t    #       #            #      #######      #     \n");
	printf("\t    #       #            #           #       #     \n");
	printf("\t    #       #          #####         #     #####   \n");
	printf("				      ~ Into The Dungeon			 \n");
	gotoxy(x, y);
	printf("1. 시작하기");
	gotoxy(x, ++y);
	printf("2. 게임종료");
	gotoxy(x - 1, y + 4);
	printf("방향키로 선택");
	gotoxy(x - 3, y + 5);
	printf("스페이스바로 확정");

	while (1) //커서이동 반복문
	{
		int n = keyControl();
		switch (n)
		{
		case UP:
			if (y > 12) //if문으로 커서 범위 제한
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, --y);
				printf(">");
			}
			break;
		case DOWN:
			if (y < 14)
			{
				gotoxy(x - 2, y);
				printf(" ");
				gotoxy(x - 2, ++y);
				printf(">");
			}
			break;
		case SUBMIT:
			return y - 11;
		}
	}
}

int keyControl() {
	char temp = _getch(); //키보드 입력값을 받기위해 getch()사용

	if (temp == -32 || temp == 72)
	{
		return UP;
	}
	else if (temp == -32 || temp == 80)
	{
		return DOWN;
	}
	else if (temp == ' ' || temp == 13)
		return SUBMIT;
}


void getName() { //닉네임 설정
	printf("이곳에 떨어진 당신의 이름은 .. ?\n");
	printf("=>");
	scanf_s("%s", &chara.name, sizeof(chara.name));
	system("cls");
	printf("반갑습니다 %s 님. \n\n", chara.name);
}

void storyLoad(int i) { //스토리를 출력해주는 함수
	if (i == 1)
	{
		printf("스토리 1");
		printf("\n\n");
	}
	if (i == 2)
	{
		printf("스토리 2");
	}
	if (i == 3)
	{
		printf("스토리 3");
	}
}

int random() //난수 생성 함수 
{
	srand(time(NULL));
	int random = (rand() % 10) + 1;
	return random;
}

void printUI() //인게임 화면 구현 함수
{
	printf("\n==================================\n");
	printf("\t    게임 메뉴 \n");
	printf("==================================\n");
	printf("이름 : %s | 레벨 : %d | 돈 : %d \n", chara.name, chara.level, chara.money);
	expBar();
	printf("\n");
	printf("\n1 : 탐험하기\t       \n");
	printf("2 : 종료하기\t       \n");
}

void expBar() {
	// 1부터 10까지 퍼센트를 구하는 변수
	int bar = (int)((float)chara.exp / (float)chara.lvlUp * 10);
	printf("EXP ");
	SetColor(10);
	for (int i = 0; i < bar; i++)
	{
		printf("■");
	}
	for (int i = 0; i < 10 - bar; i++)
	{
		printf("□");
	}
	SetColor(15);
	printf(" (%d/%d)", chara.exp, chara.lvlUp);
}
void healthBar(int h, int mh) { // 각 체력과 최대체력을 매개변수로
	// 퍼센트를 구하는 변수 1부터 10까지
	int bar = (int)((float)h / (float)mh * 10);
	printf("HP ");
	SetColor(4);
	for (int i = 0; i < bar; i++)
	{
		printf("■");
	}
	for (int i = 0; i < 10 - bar; i++)
	{
		printf("□");
	}
	SetColor(15);
	printf(" (%d/%d)", h, mh);
}


void battle() //탐험하기 눌렀을때 전투 구현 함수 
{
	printf("배틀 시작!\n"); 
	printf("%s vs %s\n", chara.name, enemy.name); 
	while (chara.hp > 0 && enemy.hp > 0) 
	{
		//체력바 구현
		printf("\n");
		healthBar(chara.hp, chara.maxHp);
		printf("\n\n");
		printf("Enemy  ~ %s ", enemy.name);
		printf("\n");
		healthBar(enemy.hp, enemy.maxHp);
		printf("\n\n");

		//플레이어의 공격 
		int playerDamage = chara.atk - enemy.def; 
		if (playerDamage < 0) 
			playerDamage = 0; 
		enemy.hp -= playerDamage; 
		printf("%s가 %s에게 %d의 데미지를 입혔습니다. (적의 남은 HP: %d)\n", chara.name, enemy.name, playerDamage, enemy.hp);
		Sleep(1000);
		if (enemy.hp <= 0) 
		{ 
			printf("%s가 승리했습니다!\n", chara.name);
			chara.exp += enemy.level * 10; // 경험치 획득 
			return; 
		} 

		// 적의 공격 
		int enemyDamage = enemy.atk - chara.def;
		if (enemyDamage < 0) 
			enemyDamage = 0; 
		chara.hp -= enemyDamage;
		printf("%s가 %s에게 %d의 데미지를 입혔습니다. (내 HP: %d)\n", enemy.name, chara.name, enemyDamage, chara.hp);
		Sleep(1000);
		if (chara.hp <= 0)
		{ 
			printf("%s가 패배했습니다...\n", chara.name);
			return; 
		} 
	} 
}

