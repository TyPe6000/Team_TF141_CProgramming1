//�÷��̾� ����ü
struct Character {
	char name[10];
	int level = 1;
	int lvlUp = 100; //������ �ϱ����� ����ġ
	int maxHp = 100;
	int hp = maxHp;
	int money = 0;
	int exp = 0;
	int atk = 8;
	int def = 2;
};
extern struct Character chara; //extern ���� �÷��̾� ����ü ����

//�� ����ü
struct Enemy {
	char name[3] = { 1, 2, 3 };
	int level = 1;
	int maxHp = 10;
	int hp = maxHp;
	int atk = 1;
	int def = 1;
};

extern struct Enemy enemy;

//windows.h ui�� �Լ�
void SetColor(int color);
void gotoxy(int x, int y);
void CursorView(char show);

//���� ui�� �Լ�
int drawTitle();
void storyLoad(int i);
void printUI();
int keyControl();
void expBar();
void healthBar(int h, int mh);

//��������� �Լ�
void getName();
void mainGame();
void battle();
int random();