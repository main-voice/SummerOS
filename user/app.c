/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            app.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							 					hkx & ph & sbw, 2022
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"
#include "rand.h"
#include "string.h"

/*************************************************************
 * @title calendar
 * @author ph
 * @data 2022
 * ***********************************************************/

 int isLeap(int year);
 int monthDays(int year, int month);
 int weekday(int year, int month, int day);
 void printWeekday(int year, int month, int day);
 void printCalendar(int year, int month, int day);
 int calendar_main(int *fd_stdin);
 void calendar_intro();

int isLeap(int year)
{
    if ((year % 400) == 0 || ((year % 4 == 0)) && (year % 100 != 0)) {
        return 1;
    } else {
        return 0;
    }
}

// return the days of 'year-month'
int monthDays (int year, int month) {
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        return 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    } else {
        return 28 + isLeap(year);
    }
}

// return the weekday of year-month-day
int zeller(int year, int month, int day)
{
    int w, c;
    c = year / 100;
    if (month == 1)
    {
        month = 13;
        year = year - 1;
        if (year + 1 == 1900 || year + 1 == 2000 || year + 1 == 2100) { c = c - 1; }
    }

    if (month == 2)
    {
        month = 14;
        year = year - 1;
        if (year + 1 == 1900 || year + 1 == 2000 || year + 1 == 2100) { c = c - 1; }
    }

    w = (year - c * 100) + (int)((year - c * 100) / 4) + (int)(c / 4) - 2 * c + (int)(13 * (month + 1) / 5) + day - 1;

    while (w < 0)
        w = w + 7;
    w = w % 7;

    return w;
}

// print the weekday of 'year-month-day'
void printWeekday (int year, int month, int day)
{
    int count = zeller (year, month, day);
    switch (count) {
        case 0: {
            printf("\n%d-%d-%d is Sunday\n", year, month, day);
            break;
        }
        case 1: {
            printf("\n%d-%d-%d is Monday\n", year, month, day);
            break;
        }
        case 2: {
            printf("\n%d-%d-%d is Tuesday\n", year, month, day);
            break;
        }
        case 3: {
            printf("\n%d-%d-%d is Wednesday\n", year, month, day);
            break;
        }
        case 4: {
            printf("\n%d-%d-%d is Thursday\n", year, month, day);
            break;
        }
        case 5: {
            printf("\n%d-%d-%d is Friday\n", year, month, day);
            break;
        }
        case 6: {
            printf("\n%d-%d-%d is Saturday\n", year, month, day);
            break;
        }
    }
}


// print calendar of 'year-month'
void printCalendar (int year, int month, int day)
{
    int weekday = zeller (year, month, 1);
    int maxDay = monthDays (year, month);

    printf("\n                   %d/%d\n", year, month);
    printf("Sun    Mon    Tue    Wed    Thu    Fri    Sat\n");
    int i = 0;
    for (i = 0; i < weekday; i++)
        printf("       ");
    for (int j = 1; j <= maxDay; j++)
    {
        printf("%d     ", j);
        if (j < 10)
            printf(" ");
        if (i % 7 == 6)
            printf("\n");
        i++;
    }
    printf("\n");
}

int calendar_main(int *fd_stdin)
{
    int year, month, day;
    char y[5], m[3], d[3]; // represent year, month, day respectively

    calendar_intro();

    printf("Please enter year of calendar:");
    int p = read(*fd_stdin, y, 512);

    y[p] = 0;
    year = 0;
    int i = 0;
    while (i < p)
    {
        year *= 10;
        year += (y[i++] - '0');
    }

    printf("Please enter month of calendar:");
    p = read(*fd_stdin, m, 512);
    m[p] = 0;
    month = 0;
    i = 0;
    while (i < p)
    {
        month *= 10;
        month += (m[i++] - '0');
    }

    printf("Please enter day of calendar:");
    p = read(*fd_stdin, d, 512);
    d[p] = 0;
    day = 0;
    i = 0;
    while (i < p)
    {
        day *= 10;
        day += (d[i++] - '0');
    }

    if (month < 1 || month > 12 || day < 1 || day > 31)
    {
        printf("There is no such data!");
        return -1;
    }

    printWeekday(year, month, day);
    printCalendar(year, month, day);

    printf("\nPress ENTER to continue...\n");
    read(*fd_stdin, d, 512);

    return 0;
}

void calendar_intro()
{
    clear();
    printf("      ====================================================================\n");
    printf("      #                                         Welcome to               #\n");
    printf("      #                                     SummerOS's Calendar          #\n");
    printf("      #              &              |                                    #\n");
    printf("      #             & &             |            [ COMMAND ]             #\n");
    printf("      #            &   &            |                                    #\n");
    printf("      #           &     &           |     You can look up any date       #\n");
    printf("      #          &   *   &          |         in this calendar.          #\n");
    printf("      #         &         &         |                                    #\n");
    printf("      #        &           &        |      Input the year, month and     #\n");
    printf("      #       &   *     *   &       |      day that you want to look     #\n");
    printf("      #      &&             &&      |          up respectively.          #\n");
    printf("      #     &&               &&     |                                    #\n");
    printf("      #    && &&&&       &&&& &&    |                                    #\n");
    printf("      #   &&& ---  &&&&&  --- &&&   |                                    #\n");
    printf("      #     &&&&&  -----  &&&&&     |                                    #\n");
    printf("      #           &&&&&&&           |                                    #\n");
    printf("      #                                                                  #\n");
	printf("      #                 $ Designed by  HKX PH SBW $                      #\n");
	printf("      #                 $ TONGJI UNIVERSITY  2022 $                      #\n");
	printf("      ====================================================================\n");	    

    printf("\n");
}



/*************************************************************
 * @Gluttonous Snake 
 * @author sbw2053512
 * ***********************************************************/
#define ROW 10
#define COL 24
#define Up  0
#define Down 1 
#define Left 2
#define Right 3
#define LENGTH 2
#define bool int
#define true 1
#define false 0
int score = 0;
bool eated = false;
int M[ROW][COL];
int direction=0;
int length=LENGTH;//4是因为move函数消去尾巴。这样蛇的长度打印出来为3
int Coordinate[ROW * COL][2]={0,0};
void welcome() {
	printf("\n\n\n\n\n\n");
	printf("   * * * * * * * * * * * * * *\n");
	printf("                               \n");
	printf("   *        WELCOME!         *\n");
	printf("                               \n");
	printf("   * * * * * * * * * * * * * *\n");
}
void rule() {
	printf("Rule:\n");
    printf("    Control the direction of the snake, look for something to eat,\n and be careful not to hit the wall and bite yourself!\n");
	printf("\n\n\nEating food will get corresponding points.\n");
	printf("     Your only goal is to become a long snake!\n");
}
 
void Initmap() {
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (i == 0 || i == ROW - 1 || j == 0 || j == COL - 1)
			{
				M[i][j] = 1;//1为墙
			}
			else  M[i][j] = 0;//0不为0
		}

	}
}
void Drawmap() {
    clear();
    printf("\n\n\n");
	for (int i = 0; i < ROW; i++)
	{
        printf("                     ");
		for (int j = 0; j < COL; j++)
		{
			if (M[i][j] == 1)//wall
                printf("*"); 
			else if(M[i][j] == -1)//food
                printf("&");
            else if(M[i][j] == 2)//snake body
                printf("#");
            else if(M[i][j] == 3)//snake head
                printf("@");
            else printf(" ");
		}
        printf("\n");
	}
    printf("                                         score:%d\n",score);
}
void fuclength(){
	length++;
}
void Initsnake() {
	Coordinate[0][0] = ROW / 2;//0为横坐标
	Coordinate[0][1] = COL / 2;//1为纵坐标
	for (int i = 1; i < length; i++)
	{
		Coordinate[i][0] = Coordinate[0][0] + i;
		Coordinate[i][1] = Coordinate[0][1];
	}
}
void Drawsnake() {
	for (int i = 0; i < length; i++)
	{	
        if(i==0)
            M[Coordinate[i][0]][Coordinate[i][1]]=3;
        else
            M[Coordinate[i][0]][Coordinate[i][1]]=2;
    }
}
void Move() {//从尾部开始后面的等于前面的坐标
    M[Coordinate[length-1][0]][Coordinate[length-1][1]]=0;
    for (int i = length - 1; i > 0; i--)
	{
		Coordinate[i][0] = Coordinate[i - 1][0];//行坐标
		Coordinate[i][1] = Coordinate[i - 1][1];//列坐标
	}
    switch (direction)
	{
		case Up:
			Coordinate[0][0]--;
			break;
		case Down:
			Coordinate[0][0]++;
			break;
		case Left:
			Coordinate[0][1]--;
			break;
		case Right:
			Coordinate[0][1]++;
			break;

	}
}
void directioncontrol(int fd_stdin,char choice) {
    switch (choice)
    {
        case 'W':
        case 'w':
            if (direction != Down)
                direction = Up;
            break;
        case 'S':
        case 's':
            if (direction != Up)
                direction = Down;
            break;
        case 'A':
        case 'a':
            if (direction != Right)
                direction = Left;
            break;
        case 'D':
        case 'd':
            if (direction != Left)
                direction = Right;
            break;
    }
}
bool death(){
	bool isGameOver = false;
	int sX = Coordinate[0][0], sY = Coordinate[0][1];      //蛇头的x坐标和y坐标
	if (sX == 0 || sX == ROW - 1 || sY == 0 || sY == COL - 1)
		isGameOver = true;
	for (int i = 1; i < length; i++)    //判断有没有吃到自己
	{
		if (Coordinate[i][0] == sX && Coordinate[i][1] == sY)
			isGameOver = true;
	}
	return isGameOver;
}
void Drawfood(){
    int error=0;
    while(!error)
    {
        int i = rand() % (ROW-2)+1;               //生成0~ROW-1之间的一个数
        int j = rand() % (COL-2)+1;
        error=1;
        for (int k = 0; k < length; k++)
        {
            if (i == Coordinate[k][0] && j == Coordinate[k][1])
                { 
                    error=0;
                    break;
                }
        }
        M[i][j]=-1;
    }
}

void snake_game(int fd_stdin){
    clear();
    welcome();
    rule();
    printf("\n                  push any key and continue\n");
    char in[1];
    read(fd_stdin, in, 1);
    clear();
    //init
    Initmap();
    Initsnake();
    Drawsnake();
    Drawfood();
    Drawmap();
    int lived=1;
    while(lived)
    {
	    char in[32];
	    printf("  W: Up\n  S: Down\n  A: Left\n  D: Rigth           \nWrite the direction what you want to walk: \n");
	    printf("command example: w 3(you can up three times(please be less than 10))\nif you want to follow last,please enter\n");
	    printf("command:");
	    int p=read(fd_stdin, in, 32);
	    in[p]=0;
	    char comm;
	    comm=in[0];
	    int i=1;
	    char times='1';
	    while((in[i]<'0'||in[i]>'9')&&in[i]!=0)
	    {
		i++;
	    }
	    if(in[i]!=0)
		times=in[i];
	    int time=0;
	    time=time+(times+1-'1');
	    int t=0;
	    while(t<time)
	    {
		directioncontrol(fd_stdin,comm);
		Move();
		if(death())
		{
		    clear();
		    printf("\n                        Game Over             \n                  push any key and continue\n");
		    char in[1];
		    read(fd_stdin, in, 1);
		    lived=0;
		    break;
		}
		if (M[Coordinate[0][0]][Coordinate[0][1]] == -1)
		{
		    eated = true;
		    if (eated == true)               //如果吃到了食物
		    {
			fuclength();
			eated = false;        //设置为false，不然无限变长
		    }
		    score += 10;
		    Drawfood();
		//	M[Coordinate[0][0]][Coordinate[0][1]] = 0;
		    Drawsnake();
		}
		t++;
		Drawsnake();
		Drawmap();
	    }
    }
}


/*************************************************************
 * @title sweep mine
 * @author ph
 * ***********************************************************/
#define MINE_ROW 9//界面的长宽
#define MINE_COL 9
#define ROWS ((MINE_ROW) + 2)
#define COLS ((MINE_COL) + 2)
#define COUNT 10//雷的个数

void initBoard(char board[ROWS][COLS], int rows, int cols, char set);
void displayBoard(char board[ROWS][COLS], int row, int col);
void setMine(char mine[ROWS][COLS], int row, int col);
void sweepMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int fd_stdin);

int sweepMineWelcome()
{
    clear();
    printf("      ====================================================================\n");
    printf("      #                                 Welcome to                       #\n");
    printf("      #                           Mine Sweeping--- an easy and fun game  #\n");
    printf("      #              &              |                                    #\n");
    printf("      #             & &             |                                    #\n");
    printf("      #            &   &            |     Welcome to play Mine Sweeping! #\n");
    printf("      #           &     &           |                                    #\n");
    printf("      #          &   *   &          |           Enjoy Yourself!          #\n");
    printf("      #         &         &         |                                    #\n");
    printf("      #        &           &        |                                    #\n");
    printf("      #       &   *     *   &       |       ********************         #\n");
    printf("      #      &&             &&      |       ****** 1.play ******         #\n");
    printf("      #     &&               &&     |       ********************         #\n");
    printf("      #    && &&&&       &&&& &&    |       ****** 0.quit ******         #\n");
    printf("      #   &&& ---  &&&&&  --- &&&   |       ********************         #\n");
    printf("      #     &&&&&  -----  &&&&&     |                                    #\n");
    printf("      #           &&&&&&&           |                                    #\n");
    printf("      #                                                                  #\n");
    printf("      #                 $ Designed by  HKX PH SBW $                      #\n");
	printf("      #                 $ TONGJI UNIVERSITY  2022 $                      #\n");
	printf("      ====================================================================\n");	    

    printf("\n\n");
}

// config the board according to the character of 'set'
void initBoard(char board[ROWS][COLS], int rows, int cols, char set)
{
	int i = 0;
	int j = 0;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			board[i][j] = set;
		}
	}
}

// user interface
void displayBoard(char board[ROWS][COLS], int row, int col)
{
	int i = 0;
	int j = 0;
	for (i = 0; i <= row; i++)
	{
		printf("%d ", i);
        if(i == 0) {
            printf(" ");
        }
	}
    printf("\n");
    for (i = 0; i <= row; i++)
	{
		printf("--");
	}
	printf("\n");
	for (i = 1; i <= row; i++)
	{
		printf("%d|", i);
		for (j = 1; j <= col; j++)
		{
			printf("%2c", board[i][j]);
		}
		printf("\n");
	}
}

// set mines randomly
void setMine(char mine[ROWS][COLS], int row, int col) 
{
	int count = COUNT;
    srand(get_ticks());
	while (count)
	{
		int x = rand() % row + 1;
		int y = rand() % col + 1;
		if (mine[x][y] == '0')
		{
			mine[x][y] = '1';
			count--;
		}
	}
}

//sweep mines recursively
void sweepMineRecursively(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int x, int y, int* score)
{
    if (x < 1 || y < 1 || x > row || y > col) 
        return;
    if (show[x][y] != '*') 
        return;

	int mine_count = 
        (mine[x - 1][y] +
		mine[x - 1][y - 1] +
		mine[x][y - 1] +
		mine[x + 1][y - 1] +
		mine[x + 1][y] +
		mine[x][y + 1] +
		mine[x + 1][y + 1] +
		mine[x - 1][y + 1] - 8 * '0');

    show[x][y] = mine_count + '0';

    (*score)++;
    if (mine_count == 0)
    {
        int dirX[8] = {1,1,0,-1,-1,-1,0,1};
        int dirY[8] = {0,1,1,1,0,-1,-1,-1};
        for (int i = 0; i < 8; i++)
        {
            sweepMineRecursively(mine, show, row, col, x + dirX[i], y + dirY[i], score);
        }
    }
}

void sweepMine(char mine[ROWS][COLS], char show[ROWS][COLS], int row, int col, int fd_stdin)
{
	int x = 0;
	int y = 0;
	int score = 0;
	int p; // receive the return value of read()
	char inputX[2];
	char inputY[2];
    printf("\nCurrent score is %d.\n", score);
    printf("You'll win when score reaches 71 (9 * 9 = 81 place and 10 mines)!\n\n");

	while (score < (row * col - COUNT))
	{
        printf("(Enter 0 to quit)\n");
		printf("Please input x: ");
		p = read(fd_stdin, inputX, 512);
        x = inputX[0]-'0';
        if(x == 0)
        {
            printf("X can not be 0!\n");
            return;
        }

		printf("Please input y:");
		p = read(fd_stdin, inputY, 512);
		y = inputY[0]-'0';
        if(y == 0)
        {
            return;
        }

		if (x >= 1 && x <= row && y >= 1 && y <= col)
		{
			if (mine[x][y] == '1')
			{
				clear();
				printf("Boom!!!  You step on a mine, Game Over!\n");
                printf("the mine are as followings, '1' is a mine\n");
				displayBoard(mine, row, col);
                printf("Press any to exit\n");
                read(fd_stdin, inputY, 512);
				break;
			}
			else
			{
                sweepMineRecursively(mine, show, row, col, x, y, &score);
				clear();
				displayBoard(show, row, col);
                printf("\nCurrent score is %d.\n", score);
                printf("You'll win when score reaches 71!\n\n");
			}

			if (score == row * col - COUNT)
			{
                clear();
                displayBoard(mine, row, col);
				printf("\nYou win! That's amazing!!\n\n");
			}
		}
		else
		{
			printf("wrong coordinate, I'm sorry:\n");
		}
	}
}


void game(int fd_stdin)
{
	//store the info of map
	//1. inner info of map
	char mine[ROWS][COLS] = { 0 };
	//2. user interface
	char show[ROWS][COLS] = { 0 };

    // init and set mine
	initBoard(mine, ROWS, COLS, '0');
	setMine(mine, MINE_ROW, MINE_COL);

	initBoard(show, ROWS, COLS, '*');

	//display
	clear();
	displayBoard(show, MINE_ROW, MINE_COL);

	// sweep mine
	sweepMine(mine, show, MINE_ROW, MINE_COL, fd_stdin);
}

int mine_main(int fd_stdin)
{
	clear();
	char o[2];
	int input = -1;
	sweepMineWelcome();

	do
	{
		printf("please input your choice: ");
		int p = read(fd_stdin, o, 512);
		input=o[0]-'0';

		switch (input)
		{
		case 1: {
            printf("you choose 1");
			game(fd_stdin);
			break;
        }
		case 0: {
			printf("quit game：\n");
			break;
        }
		default: {
			printf("You can only choose 1 or 2, please input again:\n");
			break;
        }
		}
		sweepMineWelcome();
	} while (input);

	return 0;
}


/*************************************************************
 * @title calculator ������
 * @author hkx
 * ***********************************************************/

#define False 0
#define True 1
#define END_ZERO '\0'
#define EMPTY_NUM -999999
#define SIZE 50
#define bool int
PUBLIC int get_choice();
PUBLIC void print_result(int num1, int num2, int result, int choice);
PUBLIC void calculator_menu();
PUBLIC void calculator_main();
int curPtr = 0;//global pointer

// single item structure
struct Item {
	int data;	//data item
	int tag;	//0:operator;1:number
};


//number stack 
int numStack[100] = { 0 };
int numTop = -1;


bool isEmpty_num() {
	return numTop == -1;
}

void pushNum(int num) {
	numTop++;
	numStack[numTop] = num;
}

int popNum(void) {
	if (isEmpty_num()) {
		printf("ERROR ! Num stack is already empty !\n");
		return EMPTY_NUM;
	}
	int num = numStack[numTop];
	numStack[numTop] = 0;
	numTop--;
	return num;
}

void clearNum(void) {
	memset(numStack, 0, sizeof(numStack));
	numTop = -1;
	return;
}


//operator stack
char oprStack[100] = { '\0'};
int oprTop = -1;

bool isEmpty_opr() {
	return oprTop == -1;
}

void pushOpr(char ch) {
	oprTop++;
	oprStack[oprTop] = ch;
}

char popOpr(void) {
	if (isEmpty_opr()) {
		printf("ERROR ! Operator stack is already empty !\n");
		return END_ZERO;
	}
	char ch = oprStack[oprTop];
	oprStack[oprTop] = '\0';
	oprTop--;
	return ch;
}

char getOprTop(void) {
	if (isEmpty_opr()) {
		return END_ZERO;
	}
	return oprStack[oprTop];
}

void clearOpr(void) {
	memset(oprStack, '\0', sizeof(oprStack));
	oprTop = -1;
}


//bracket stack
char bracketStack[100] = "\0";
int bracketTop = -1;

bool isEmpty_bracket() {
	return bracketTop == -1;
}

void pushBracket(char ch) {
	bracketTop++;
	bracketStack[bracketTop] = ch;
}

char popBracket(void) {
	if (isEmpty_bracket()) {
		return END_ZERO;
	}
	char ch = bracketStack[bracketTop];
	bracketTop--;
	return ch;
}

void clearBracket(void) {
	memset(bracketStack, '\0', sizeof(bracketStack));
	bracketTop = -1;
}

int priorityInStack(char c)
{
	switch (c)
	{
	case '@':return 0;
	case '(':return 1;
	case '+':case '-':return 3;
	case '*':case '/':return 5;
	case ')':return 6;
	}
}

int priorityOutStack(char c)
{
	switch (c)
	{
	case '@':return 0;
	case ')':return 1;
	case '+':case '-':return 2;
	case '*':case '/':return 4;
	case '(':return 6;
	}
}

// add end symbol 
void addEndTag(char* exp) {
	int i = strlen(exp);
	exp[i] = ' ';
	exp[i + 1] = '@';
}
// judge operator
bool isOpr(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '@') {
		return True;
	}
	return False;
}
// judge single number
bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}
//judge whole number
bool isNum(char* exp)
{
	char c = exp[0];
	if (c == '+' && strlen(exp) > 1)
		
	{
		exp = exp + 1;	//delete+
		c = exp[0];		//updatec
	}

	if (isDigit(c) || (c == '-' && strlen(exp) > 1))//store different kinds of numbers
	{
		return True;
	}
	return False;
}

struct Item WeNext(char* exp)
{
	char temp[50] = "\0";
	char c;
	int index = 0;

	for (int i = curPtr; i < strlen(exp); ++i)
	{
		c = exp[i];
		if (c != ' ')
		{
			temp[index] = c;
			index++;	//space for divide items
		}
		else
		{
			while (exp[i] == ' ') {
				i++;
			}
			curPtr = i;	//ָto find next item
			break;
		}
	}

	if (isOpr(temp[0])) {
		struct Item e;
		e.data = temp[0];
		e.tag = 0;
		return e;
	}
	else {
		struct Item e;
		e.data = (*temp) - '0';
		e.tag = 1;
		return e;
	}
}

int basCal(int num1, int num2, char opr)
{
	if (opr == '+')
	{
		return num1 + num2;
	}
	if (opr == '-')
	{
		return num1 - num2;
	}
	if (opr == '*')
	{
		return num1 * num2;
	}
	if (opr == '/')
	{
		return num1 / num2;
	}
}

int calculate(struct Item e[], int size)
{
	clearNum();
	for (int i = 0; i < size; ++i) {
		if (e[i].tag == 1) {//is number
			pushNum(e[i].data);
		}
		else {//is operator
			int n2 = popNum();
			int n1 = popNum();
			pushNum(basCal(n1, n2,e[i].data));// push in stack
		}
	}
	return popNum();
}

int advanceCalculate(char* input) {
	char exp[30] = "\0";
	int pos = 0;
	for (int i = 0; i < strlen(input); ++i) {
		if (isOpr(input[i])) {
			exp[pos] = ' ';
			++pos;
			exp[pos] = input[i];
			++pos;
			exp[pos] = ' ';
			++pos;
		}
		else if (isDigit(input[i])) {
			exp[pos] = input[i];
			++pos;
		}
	}
	// initialize
	clearNum();
	clearOpr();
	curPtr = 0;

	struct Item result[100];
	int index = 0;

	addEndTag(exp);

	pushOpr('@');//enter loop
	struct Item elem = WeNext(exp);
	while (!isEmpty_opr()) {
		char ch = elem.data;

		if (elem.tag == 1) {		
			result[index] = elem;
			index++;
			elem = WeNext(exp);
		}
		else if (elem.tag == 0) {	//compare priority
			char topEle = getOprTop();
			if (priorityInStack(topEle) < priorityOutStack(ch)) {		
				pushOpr(ch);
				elem = WeNext(exp);
			}
			else if (priorityInStack(topEle) > priorityOutStack(ch)) {	
				struct Item buf;
				buf.data = popOpr();
				buf.tag = 0;
				result[index] = buf;
				index++;
			}
			else {
				if (getOprTop() == '(') {	//"(" exit for next item
					elem = WeNext(exp);
				}
				popOpr();
			}
		}
	}

	return calculate(result, index);
}

bool checkBracket(char* exp) {

	char ch = '\0';

	for (int i = 0; i < strlen(exp); ++i) {
		if (exp[i] == '(') {
			pushBracket('(');
		}
		else if (exp[i] == ')') {
			ch = popBracket();
			if (ch == END_ZERO || ch != '(') {
				printf("Brackets  do not match.\n");
				return False;
			}
		}
	}
	return isEmpty_bracket();
}

bool checkOpr(char* exp) {
	for (int i = 0; i < strlen(exp); ++i) {
		if (isDigit(exp[i]) || isOpr(exp[i]) || exp[i] == ' ') {
			continue;
		}
		else {
			printf("%c invalid !\n", exp[i]);
			return False;
		}
	}
	return True;
}
void advCal(char* expression)
{
	if (!strcmp(expression, "NULL")) {
		printf("Uh-oh, please input a math expressioin.\n");
	}
	else {
		// �������Ƿ�Ϸ�
		if (!checkOpr(expression)) {
			printf("Uh-oh, please check and try again.\n\n");
			return;
		}
		// ��������Ƿ�ƥ��
		clearBracket();
		if (!checkBracket(expression)) {
			printf("Uh-oh, please check and try again.\n\n");
			return;
		}
		int result = advanceCalculate(expression);
		printf("The result is %d\n", result);
		printf("\n");
	}
}

int get_choice(int* fd_stdin)
{
	int choice;
	char option[2];

	do
	{
		printf("\n #========================#");
		printf("\n #=====   1.add      =====#");
		printf("\n #=====   2.minus    =====#");
		printf("\n #=====   3.mutiply  =====#");
		printf("\n #=====   4.division =====#");
		printf("\n #=====   5.advance  =====#");
		printf("\n #=====   0.exit     =====#");
		printf("\n #========================#\n");
		printf("Please select a function :");


		int t = read(*fd_stdin, option, 512);//return number of characters
		option[t] = '\0';
		choice = option[0] - '0';

		if (choice < 0 || choice > 5)
		{
			clear();
			printf("No match ! Please reput ! \n");
		}
	} while (choice < 0 || choice > 5);

	return choice;
}


PUBLIC void calculator_main(int* fd_stdin)
{
	int choice, num1, num2, result;
	char a[20], b[20];

	calculator_menu();
	read(*fd_stdin, a, 512);
	clear();

	do
	{
		choice = get_choice(fd_stdin);
		if (choice == 0)
			break;
		if (choice == 5) {
			char exp[30] = "\0";
			printf("Please input an math expression :");
			int t = read(*fd_stdin, exp, 512);
			advCal(exp);
		}
		else {
			do                                                                                         
			{
				printf("\nPlease input a number :");
				int t = read(*fd_stdin, a, 512);
				a[t] = 0;
				num1 = 0;
				int i = 0;
				while (i < t)
				{
					num1 *= 10;
					num1 += (a[i++] - '0');
				}

				printf("\nPlease input another number:");
				t = read(*fd_stdin, b, 512);
				b[t] = 0;
				num2 = 0;
				i = 0;
				while (i < t)
				{
					num2 *= 10;
					num2 += (b[i++] - '0');
				}

				if (choice == 4 && num2 == 0)
				{
					printf("\nUh-oh, divisor can not be 0 !");
				}
				else
				{
					switch (choice)
					{
					case 1:
						result = num1 + num2;
						break;
					case 2:
						result = num1 - num2;
						break;
					case 3:
						result = num1 * num2;
						break;
					case 4:
						result = num1 / num2;
					}
					print_result(num1, num2, result, choice);
				}
			} while (choice == 4 && num2 == 0);
		}
	} while (choice != 0);

}

void print_result(int num1, int num2, int result, int choice)
{
	char operator;
	switch (choice)
	{
	case 1:
		operator= '+';
		break;
	case 2:
		operator= '-';
		break;
	case 3:
		operator= '*';
		break;
	case 4:
		operator= '/';
		break;
	}
	printf("\n** %d %c %d = %d **\n", num1, operator, num2, result);
}

void calculator_menu()
{
	clear();
printf("      ====================================================================\n");
	printf("      #                    Welcome to Calculator !                       #\n");
	printf("      #                                                                  #\n");
	printf("      #              &              |          [COMMAND LIST]            #\n");
	printf("      #             & &             |                                    #\n");
	printf("      #            &   &            |     $ 4 fundamental operations $   #\n");
	printf("      #           &     &           |            1 --- Add               #\n");
	printf("      #          &   *   &          |            2 --- Minus             #\n");
	printf("      #         &         &         |            3 --- Multiply          #\n");
	printf("      #        &           &        |            4 --- Divide            #\n");
	printf("      #       &   *     *   &       |       $ For expression input $     #\n");
	printf("      #      &&             &&      |            5 --- Advance           #\n");
	printf("      #     &&               &&     |            $ Exit $                #\n");
	printf("      #    && &&&&       &&&& &&    |            0 --- Quit              #\n");
	printf("      #   &&& ---  &&&&&  --- &&&   |                                    #\n");
	printf("      #     &&&&&  -----  &&&&&     |       Press ENTER to continue...   #\n");
	printf("      #           &&&&&&&           |                                    #\n");
	printf("      #                                                                  #\n");
	printf("      #                 $ Designed by  HKX PH SBW $                      #\n");;
	printf("      #                 $ TONGJI UNIVERSITY  2022 $                      #\n");
	printf("      ====================================================================\n");

	printf("\n\n");
}
