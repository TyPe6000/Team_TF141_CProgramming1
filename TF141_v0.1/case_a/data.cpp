#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stralign.h>  
#include <time.h>
#include <conio.h>
#include "main.h"

//Ű���� �Է°�
#define UP 0
#define DOWN 1
#define SUBMIT 2

Character chara;
Enemy enemy;

void gotoxy(int x, int y) { // Ŀ�� ���� �Լ�
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE); // �ܼ� �ڵ� ��������
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consoleHandle, pos);
}

void SetColor(int color) //�� ���� �Լ�
{
	/*
		���� 0
		��ο� �Ķ� 1
		��ο� �ʷ� 2
		��ο� �ϴ� 3
		��ο� ���� 4
		��ο� ���� 5
		��ο� ��� 6
		ȸ�� 7
		��ο� ȸ�� 8
		�Ķ� 9
		�ʷ� 10
		�ϴ� 11
		���� 12
		���� 13
		��� 14
		�Ͼ� 15
	*/
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void CursorView(char show) //�ܼ� Ŀ�� ǥ�� �Լ�
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

int drawTitle() { //�ΰ� ��� �Լ�
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
	printf("1. �����ϱ�");
	gotoxy(x, ++y);
	printf("2. ��������");
	gotoxy(x - 1, y + 4);
	printf("����Ű�� ����");
	gotoxy(x - 3, y + 5);
	printf("�����̽��ٷ� Ȯ��");

	while (1) //Ŀ���̵� �ݺ���
	{
		int n = keyControl();
		switch (n)
		{
		case UP:
			if (y > 12) //if������ Ŀ�� ���� ����
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
	char temp = _getch(); //Ű���� �Է°��� �ޱ����� getch()���

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


void getName() { //�г��� ����
	printf("�̰��� ������ ����� �̸��� .. ?\n");
	printf("=>");
	scanf_s("%s", &chara.name, sizeof(chara.name));
	system("cls");
	printf("�ݰ����ϴ� %s ��. \n\n", chara.name);
}

void storyLoad(int i) { //���丮�� ������ִ� �Լ�
	if (i == 1)
	{
		printf("���丮 1");
		printf("\n\n");
	}
	if (i == 2)
	{
		printf("���丮 2");
	}
	if (i == 3)
	{
		printf("���丮 3");
	}
}

int random() //���� ���� �Լ� 
{
	srand(time(NULL));
	int random = (rand() % 10) + 1;
	return random;
}

void printUI() //�ΰ��� ȭ�� ���� �Լ�
{
	printf("\n==================================\n");
	printf("\t    ���� �޴� \n");
	printf("==================================\n");
	printf("�̸� : %s | ���� : %d | �� : %d \n", chara.name, chara.level, chara.money);
	expBar();
	printf("\n");
	printf("\n1 : Ž���ϱ�\t       \n");
	printf("2 : �����ϱ�\t       \n");
}

void expBar() {
	// 1���� 10���� �ۼ�Ʈ�� ���ϴ� ����
	int bar = (int)((float)chara.exp / (float)chara.lvlUp * 10);
	printf("EXP ");
	SetColor(10);
	for (int i = 0; i < bar; i++)
	{
		printf("��");
	}
	for (int i = 0; i < 10 - bar; i++)
	{
		printf("��");
	}
	SetColor(15);
	printf(" (%d/%d)", chara.exp, chara.lvlUp);
}
void healthBar(int h, int mh) { // �� ü�°� �ִ�ü���� �Ű�������
	// �ۼ�Ʈ�� ���ϴ� ���� 1���� 10����
	int bar = (int)((float)h / (float)mh * 10);
	printf("HP ");
	SetColor(4);
	for (int i = 0; i < bar; i++)
	{
		printf("��");
	}
	for (int i = 0; i < 10 - bar; i++)
	{
		printf("��");
	}
	SetColor(15);
	printf(" (%d/%d)", h, mh);
}


void battle() //Ž���ϱ� �������� ���� ���� �Լ� 
{
	printf("��Ʋ ����!\n"); 
	printf("%s vs %s\n", chara.name, enemy.name); 
	while (chara.hp > 0 && enemy.hp > 0) 
	{
		//ü�¹� ����
		printf("\n");
		healthBar(chara.hp, chara.maxHp);
		printf("\n\n");
		printf("Enemy  ~ %s ", enemy.name);
		printf("\n");
		healthBar(enemy.hp, enemy.maxHp);
		printf("\n\n");

		//�÷��̾��� ���� 
		int playerDamage = chara.atk - enemy.def; 
		if (playerDamage < 0) 
			playerDamage = 0; 
		enemy.hp -= playerDamage; 
		printf("%s�� %s���� %d�� �������� �������ϴ�. (���� ���� HP: %d)\n", chara.name, enemy.name, playerDamage, enemy.hp);
		Sleep(1000);
		if (enemy.hp <= 0) 
		{ 
			printf("%s�� �¸��߽��ϴ�!\n", chara.name);
			chara.exp += enemy.level * 10; // ����ġ ȹ�� 
			return; 
		} 

		// ���� ���� 
		int enemyDamage = enemy.atk - chara.def;
		if (enemyDamage < 0) 
			enemyDamage = 0; 
		chara.hp -= enemyDamage;
		printf("%s�� %s���� %d�� �������� �������ϴ�. (�� HP: %d)\n", enemy.name, chara.name, enemyDamage, chara.hp);
		Sleep(1000);
		if (chara.hp <= 0)
		{ 
			printf("%s�� �й��߽��ϴ�...\n", chara.name);
			return; 
		} 
	} 
}

