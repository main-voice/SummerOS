
/*************************************************************
 * @title calculator 计算器
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
int curPtr = 0;//全局指针

// 单项结构体
struct Item {
	int data;	//数据项
	int tag;	//0：符号；1：数字
};


//数字栈
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


//符号栈
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


//括号栈
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

//栈内优先级
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
//栈外优先级
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

// 添加结尾标识
void addEndTag(char* exp) {
	int i = strlen(exp);
	exp[i] = ' ';
	exp[i + 1] = '@';
}
// 判断运算符
bool isOpr(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')' || c == '@') {
		return True;
	}
	return False;
}
// 判断数字
bool isDigit(char c)
{
	return (c >= '0' && c <= '9');
}
//判断数
bool isNum(char* exp)
{
	char c = exp[0];
	if (c == '+' && strlen(exp) > 1)
		//  +i 只存 i
	{
		exp = exp + 1;	//删除+
		c = exp[0];		//更新一下c
	}

	if (isDigit(c) || (c == '-' && strlen(exp) > 1))//储存各类型数字
	{
		return True;
	}
	return False;
}

struct Item next(char* exp)
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
			index++;	//空格分隔元素项,非空格添加
		}
		else
		{
			while (exp[i] == ' ') {
				i++;
			}
			curPtr = i;	//指向下一个位置,结束当前对象的寻找
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
		if (e[i].tag == 1) {//如果是数字就压入栈中
			pushNum(e[i].data);
		}
		else {// 如果是操作符，就从栈中弹出两个数字做运算
			int n2 = popNum();
			int n1 = popNum();
			pushNum(basCal(n1, n2,e[i].data));// 再将计算结果压入栈中
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
	// 初始化
	clearNum();
	clearOpr();
	curPtr = 0;

	struct Item result[100];
	int index = 0;

	// 在表达式尾部添加结束标识符
	addEndTag(exp);

	pushOpr('@');//进入循环条件
	struct Item elem = next(exp);
	while (!isEmpty_opr()) {
		char ch = elem.data;

		if (elem.tag == 1) {		
			result[index] = elem;
			index++;
			elem = next(exp);
		}
		else if (elem.tag == 0) {	//比较优先级
			char topEle = getOprTop();
			if (priorityInStack(topEle) < priorityOutStack(ch)) {		//当前操作符优先级大
				pushOpr(ch);
				elem = next(exp);
			}
			else if (priorityInStack(topEle) > priorityOutStack(ch)) {	//当前优先级小
				struct Item buf;
				buf.data = popOpr();
				buf.tag = 0;
				result[index] = buf;
				index++;
			}
			else {
				if (getOprTop() == '(') {	//如果退出的是左括号则读入下一个内容
					elem = next(exp);
				}
				popOpr();
			}
		}
	}

	return calculate(result, index);
}

// 括号是否匹配
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

/*判断表达式是否有非法符号*/
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
		// 检查符号是否合法
		if (!checkOpr(expression)) {
			printf("Uh-oh, please check and try again.\n\n");
			return;
		}
		// 检查括号是否匹配
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
		printf("\n #=====  2.minus    =====#");
		printf("\n #=====   3.mutiply  =====#");
		printf("\n #=====  4.division =====#");
		printf("\n #=====   5.advance =====#");
		printf("\n #=====   0.exit     =====#");
		printf("\n #========================#\n");
		printf("Please select a function :");


		int t = read(*fd_stdin, option, 512);//返回读取的字节数
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

