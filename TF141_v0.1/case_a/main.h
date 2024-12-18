//플레이어 구조체
struct Character {
	char name[10];
	int level = 1;
	int lvlUp = 100; //레벨업 하기위한 경험치
	int maxHp = 100;
	int hp = maxHp;
	int money = 0;
	int exp = 0;
	int atk = 8;
	int def = 2;
};
extern struct Character chara; //extern 으로 플레이어 구조체 선언

//적 구조체
struct Enemy {
	char name[3] = { 1, 2, 3 };
	int level = 1;
	int maxHp = 10;
	int hp = maxHp;
	int atk = 1;
	int def = 1;
};

extern struct Enemy enemy;

//windows.h ui용 함수
void SetColor(int color);
void gotoxy(int x, int y);
void CursorView(char show);

//게임 ui용 함수
int drawTitle();
void storyLoad(int i);
void printUI();
int keyControl();
void expBar();
void healthBar(int h, int mh);

//게임진행용 함수
void getName();
void mainGame();
void battle();
int random();