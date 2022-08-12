# 1 项目描述

## 1.1 项目目的

本次的操作系统课程设计旨在让我们通过学习并实现一个最基本的的操作系统，增加对进程管理、内存管理、文件管理等基本组成部分的理解，并了解操作系统是如何发展的出来的，同时也帮助我们熟悉Linux的环境。

## 1.2 开发环境

* 操作系统：Ubuntu 64bits*(使用 VMware虚拟机)*

* 操作系统模拟器：Bochs开源模拟器

* 代码编辑器：Visual Studio Code

* 代码语言：C语言、汇编语言

## 1.3 项目选题及达成指标

项目选题：完成《Orange's：一个操作系统的实现》项目要求

达成指标：

* B级：本系统对文件系统进行重新实现，新增代码量达到相关模块代码的一半。

* C级：在参考源码上实现了系统级应用，如磁盘、工具台、进程管理等，通过调用较多系统API实现对系统的检测和控制。

* D级：在参考源码上实现了用户级应用，包括2个小游戏、日历、计算器。

# 2 设计方案

## 2.1 项目概述

本系统以《Orange's：一个操作系统的实现》一书中的源代码为基础，实现了一个简单的操作系统，通过调用部分系统API实现了贪吃蛇、扫雷等小游戏，以及日历、计算器等工具以及一个开机动画；同时对进程管理和文件系统进行了一定程度的实现。

## 2.2 系统功能及使用说明

* 在`SummerOS`打开终端

* 输入`bochs`->`6`->`c`

* 进入`SummerOS`操作系统

### 2.2.1 开机动画

在系统启动前为用户展示开机动画，动态演示SummerOs，及团队开发者。

![](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fa977b3e5-a649-4508-a45c-2615a9074d47%2FUntitled.png?table=block&id=e759776a-a3ae-40b5-9440-e59e03fc2dac)

### 2.2.2 帮助界面/主界面

主界面主要是提供所有能接收到的指令。输入不同的命令可以进入相应功能界面。

回到帮助界面/主界面的方法是在命令行中输入`help`后按下回车。

### 2.2.3 清屏功能

当需要清理屏幕时，输入指令clear按下回车即可。

### 2.2.4 进程管理

`runProcessManager()` 进程管理——用户输入指令`process`，进入进程管理帮助界面。

* **实现方法**

* 进程管理系统为对计算机内的全部进程的调度，展示，修改等控制功能。主要包含的操作有：**ps，block，start，quit，help，clear**。该界面包含了一个命令提示帮助界面。

* <img src="https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F0046eef1-f542-4be2-aaed-7efe96bedb11%2FUntitled.png?table=block&id=6db35ddb-2cc7-4ca0-88f0-e5b314344682&spaceId=cd37e22d-bc20-4364-9838-fb09d9455024" alt="image-20220809224654583" style="zoom:60%;" />

#### 2.2.4.1 ps

**描述：**

用户进入进程管理系统后，输入指令`ps`，系统打印出全部进程以及运行状态、优先级等全部信息。

**实现方法**

调⽤`show_all_Process()`⽅法，访问`proc_table[]`，依次输出其中进程的各种信息。

**截图**

<img src="https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F3563fbd1-28c5-4d5c-bed9-402551b32ee1%2FUntitled.png?table=block&id=2ff2a611-3046-434c-8271-01d5630d0ce0&spaceId=cd37e22d-bc20-4364-9838-fb09d9455024" style="zoom:60%;" />

#### 2.2.4.2 block

**描述：**

用户进入进程管理系统后，输入指令`block x`，系统将关闭第x号进程。

**实现方法**

调⽤`block_a_Process()`⽅法，根据输入的x的值寻找到`proc_table[]`的相应的位置，修改进程的优先级和运行状态。

#### 2.2.4.3 start

**描述：**

用户进入进程管理系统后，输入指令`start x`，系统将打开第x号进程。

**实现方法**

调⽤`start_a_Process()`⽅法，根据输入的x的值寻找到proc_table[]的相应的位置，修改进程的优先级和运行状态。

#### 2.2.4.4 quit

**描述：**

用户进入进程管理系统后，输入指令`quit`，系统退出进程管理系统。

#### 2.2.4.5 clear

**描述：**

用户进入进程管理系统后，输入指令`clear`，后，系统会自动清理屏幕。

#### 2.2.4.6 help

**描述：**

用户进入进程管理系统后，输入指令`help`，后，系统会自动清理屏幕并回到命令帮助界面。

### 2.2.5 文件管理

`runFileManage()`:文件系统

本文件系统模拟Linux的部分简单文件操作，设置初始用户为home，实现了可长期保存的多级目录下的文件系统。主要包含操作有：查看该目录下所有目录及文件名（`ls`），创建普通文件（`touch`），创建目录文件（`mkdir`），删除文件（`rm`），读文件（`rd`），写文件（`wt`），进入多级目录（`cd`）。

用户通过在1号控制台中输入`file`指令进入文件管理系统。

下面是文件系统包含命令帮助界面：

#### 2.2.5.1 quit

**描述**

用户进入文件系统后，输入指令`ls`，系统打印出当前⽂件⽬录下的全部⽂件及⽬录。

**实现方法**

调⽤`ls()`⽅法，找到当前⽬录下的全部⽂件名。



#### 2.2.5.2 mkdir

**描述**

用户进入文件系统后，输入指令`mkdir + filename`，系统即在当前目录下创建一个新的目录文件并命名为`filename`。若创建成功，系统无提示，若存在重名文件夹，则系统提示“Mkdir error, xx exists.”的消息。

**实现方法**

根据传入的type类型，通过调⽤`open()`⽅法创建新目录，根据⽅法返回值判断是否创建成功并给⽤户发出反馈消息。

**截图**

![](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fe10f1eaa-822d-44e4-8792-2417f0a9b156%2FUntitled.png?table=block&id=26ad1ca9-bc5c-42b3-9a16-5831eed8555b&spaceId=cd37e22d-bc20-4364-9838-fb09d9455024)

#### 2.2.5.3 touch

**描述**

⽤户输⼊`touch + filename`指令，在当前⽬录下创建⼀个新的⽂件并命名，若存在重名文件夹，则系统提示“touch error, xx exists.”的消息。

**实现方法**

根据传入的type类型，通过调⽤`open()`⽅法创建对应类型的新⽂件。

**截图**

![](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F4664cb7c-1bdc-4046-9ce3-2aec476a5426%2FUntitled.png?table=block&id=f591da0b-42b3-4e01-bd61-0a86231128cc)

#### 2.2.5.4 remove（rm）

**描述**

用户进入文件系统某一目录后，可以输入`rm`在当前目录下进行文件删除操作。若删除普通文件，则输入操作`rm filename`，系统执行删除操作；若删除目录文件，则输入操作`rm -r dir_name`，系统执行删除目录操作。

**实现方法**

通过调用`unlink()`API实现文件删除，通过递归调用`dir_unlink()`实现目录文件的级联删除。

**截图**

![](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F70c1e85e-d28c-4bd9-be42-66cc7d6d7a36%2FUntitled.png?table=block&id=7d3f8d64-9c46-4936-b4a8-b66ef5070006)

#### 2.2.5.5 write（wt）

**描述**

⽤户输⼊`wt+filename`指令，系统在定位到⽬标⽂件后显示⽂件路径，之后⽤户输⼊要写⼊⽂件的内容并回⻋，系统显示写入byte数，完成写⽂件操作。

**实现方法**

调用`open()`⽅法定位⽂件，然后调⽤`write()`⽅法对⽂件进⾏写操作。

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fb4b6d8a7-1e4e-4f50-b30b-6ef7a075121b%2FUntitled.png?table=block&id=c113cbe0-c060-4118-bf5a-796d50b7abda)

#### 2.2.5.6 read（rd）

**描述**

⽤户输⼊`rd+filename`指令，查看该文件内容，若文件已写入内容，则显示文件内容；若文件已创建但为空（未写入内容），则打印空行；若文件未查找到或文件打开失败，则提示用户fail to open [filename]！。

**实现方法**

调用`open()`⽅法定位⽂件，然后调⽤`read()`⽅法对⽂件进⾏读操作。

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fcd2d99c2-3265-496f-b107-08a8a4b3ef20%2FUntitled.png?table=block&id=6ec7ba87-ea51-4e86-8f54-c090609d311f)

#### 2.2.5.7 cd

**描述**

⽤户输⼊`cd+directory`指令，系统定位到该相对路径所在的目录并检索其是否存在，如果存在则将cur_dir变量后追加用户所输入的相对路径，在此后进行操作时，控制台屏幕上显示的当前目录为cd后进入的目录，以后操作中涉及的目录均以此为基础进行定位。

同时支持多级文件检索，比如`cd ./././../.././`能够返回到上上级目录

**实现方法**

调用`open()`方法确认要进入的目录是否存在，如果存在则使用strcat()函数更新cur_dir。对于多级目录，采用循环的方式，每检测到一个指令就进行一步操作

**截图**

可以看到qq是当前目录，经过一串指令后其实是进入到上级目录

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F1b4ecef7-3b69-4a63-b9ae-00a64e2ea1ce%2FUntitled.png?table=block&id=b1d3427e-5ebb-46d9-9445-407f89f26935)

### 2.2.6 游戏及工具

#### 2.2.6.1 游戏界面

用户输入指令`game`，进入游戏界面，控制台将显示所有游戏简介及相应指令。

#### 2.2.6.2 mine（扫雷）

**操作描述**

*   用户输入指令`mine`，进入扫雷游戏界面，控制台将显示游戏选项，用户输入`1`即开始游戏，输入`0`退出游戏

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F3c3d23c6-6548-46bb-b15f-f1550bc325ee%2FUntitled.png?table=block&id=345b7dae-8f85-4c4e-ba38-8a8fbba5ad3a)

*   用户可以通过指令在扫雷棋盘中翻开指定块，每次操作后将打印新的棋盘

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F52865831-6648-4b5b-a75c-ec413195ceb5%2FUntitled.png?table=block&id=1813dcce-3d85-4705-ad92-65572a03f0f0)

*   用户成功排除所有雷（10个）时，将显示游戏获胜信息

*   用户“踩”到雷则游戏失败

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F6782056a-924d-4405-b50e-d1fd70b92b87%2FUntitled.png?table=block&id=55d1e563-f351-4df6-8dd9-f49a9880bef6)

**功能实现**

*   通过调用InitBoard()生成两个棋盘，一个用于显示给用户，一个用于记录哪里埋雷

*   调用`sweepMine()`接收用户的指令进行游戏

#### 2.2.6.3 calendar（日历）

**操作描述**

*   用户输入指令`calend`，进入日历应用界面，控制台将显示日历的操作说明

*   用户输入要查询的年月日

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F8cbeb836-835d-4e4a-95d8-70d4d0092c0c%2FUntitled.png?table=block&id=82678d73-5d79-4b34-a049-a545fc2c17c7)

系统输出查询的日期具体是星期几，并且输出该月份的日历

**功能实现**

*   调用`zeller()`函数，通过蔡勒公式来判断输入日期是星期几

*   调用`printCalendar`来打印该月的日历
*   调用`printWeekday`来打印是星期几

*   调用`calendar_main()`函数来接受用户指令进行查询

#### 2.2.6.4 calculator（计算器）

**操作描述**

*   用户输入指令`calcul`，进入计算器应用界面，控制台将显示计算器的操作说明

*   输入要进行的操作，包括基本的四则运算和复杂表达式的算术功能，按0则退出计算器
*   输入要计算的表达式或数字

![图片](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2F79ca5301-1e02-4a1f-adea-81cd9a81e97d%2FUntitled.png?table=block&id=c8b975a3-515b-45bc-9a76-96c69c0fbb76)

**功能实现**

*   调用`calculator_main(int* fd_stdin)`核心代码运行计算器，其中调用`get_choice(int *fd_stdin)`函数让用户选择要进行的功能操作

*   用户在基本模式中输入要计算的数字或在高级模式中直接输入可带括号的算术表达式

*   最后，调用`print_result()`函数打印计算结果

#### 2.2.6.5 Snake（贪吃蛇）

**操作描述**

* 用户输入指令`Snake`，进入贪吃蛇的游戏界面。首先是一个简介与欢迎界面，为用户提供了基本的玩法说明，本界面输入任意键进入游戏界面。

*   游戏界面可以通过指令的输入控制贪吃蛇的行走，例如“w 3”将控制贪吃蛇向上行走三格。

**功能实现**

* 调用`snake_game(int fd_stdin)`函数进入贪吃蛇游戏中
* 首先调用`welcome()`和`rule()`函数进入简介与欢迎界面，输入任意键可以退出。
* 系统自动初始化地图和蛇以及蛇并打印出来开始接受用户的指令。用户可以通过输入相应的指令执行行走的操作。
* 通过一个`while()`循环不断地接受指令直到游戏结束。

**截图**

![](https://pengpeng73.notion.site/image/https%3A%2F%2Fs3-us-west-2.amazonaws.com%2Fsecure.notion-static.com%2Fb5b17b2c-88e2-41bc-9239-185b10c7ea6a%2FUntitled.png?table=block&id=9e0e3df6-029f-4cef-9239-64915c8fc112)

# 3 项目核心代码

仅展示进程管理和文件管理的部分核心代码

## 3.1 进程管理

```
void runProcessManage(int fd_stdin)
{
	clear();
	char readbuffer[12];
	Process_Welcome();
	
	while (1)
	{
		printf("SummerOS process-manager: $ ");

		int end = read(fd_stdin, readbuffer, 12);
		readbuffer[end] = 0;
		int i = 0, j = 0;
		//get instruction
		char com[8] = { 0 };
		while (readbuffer[i] != ' ' && readbuffer[i] != 0)
		{
			com[i] = readbuffer[i];
			i++;
		}
		i++;
		//get target
		char number[2] = { 0 };
		while (readbuffer[i] != ' ' && readbuffer[i] != 0)
		{
			number[j] = readbuffer[i];
			i++;
			j++;
		}
		//kill a process
		if (strcmp(com, "block") == 0)
		{
			block_a_Process(number);
			continue;
		}
		//restart a process
		else if (strcmp(com, "start") == 0)
		{
			start_a_Process(number);
			continue;
		}
		//command list
		else if (strcmp(readbuffer, "help") == 0)
		{
			Process_Welcome();
		}
		//get all process and their status
		else if (strcmp(readbuffer, "ps") == 0)
		{
			show_all_Process();
		}
		//exit
		else if (strcmp(readbuffer, "quit") == 0)
		{
			clear();
			break;
		}
		else if (!strcmp(readbuffer, "clear")) {
			clear();
		}
		//no such command
		else
		{
			clear();
			printf("\nSorry, there is no such command in this Process Management System.\n\n");
		}
		
	}
}
```

```
void show_all_Process()
{
	int i;
	printf("===============================================================================\n");
	printf("    ProcessID    *    ProcessName    *    ProcessPriority    *    Running?           \n");
	
	printf("-------------------------------------------------------------------------------\n");
	for (i = 0; i < 8; i++)
	{
		printf("        %d", proc_table[i].pid);
		printf("                 %5s", proc_table[i].name);
		printf("                   %2d", proc_table[i].priority);
		if (proc_table[i].priority == 0)
			printf("                   no\n");
		else
			printf("                   yes\n");

	}
	printf("===============================================================================\n\n");
}
```

```
//kill a process
void block_a_Process(char str[])
{
	int pid = get_Pid(str);

	
	if (pid >= 8 || pid < 0)
	{
		printf("The pid out of the range\n");
	}
	else if (pid < NR_TASKS)
	{
		printf("System tasks cannot be blocked.\n");
	}
	else if (proc_table[pid].priority == 0 || proc_table[pid].p_flags == -1)
	{
		printf("Process not found.\n");
	}
	else if (pid == 4 || pid == 6)
	{
		printf("This process cannot be blocked.\n");
	}
	else
	{
		proc_table[pid].priority = 0;
		proc_table[pid].p_flags = -1;
		printf("Target process has been blocked.\n");
	}

	show_all_Process();
}
```

## 3.2 文件管理

主函数

```
void runFileManage(int fd_stdin)
{

	fs_welcome();
	char _curdir[512] = "/";
	char _rdbuf[256];
	char _cmd[20];
	char _filename1[128];
	char _filename2[128];

	read(fd_stdin, _rdbuf, 512);
	fsComList();

	while(1)
	{
		printf("SummerOS file system : $%s", _curdir); // current path
		int r = read(fd_stdin, _rdbuf, 512);
		_rdbuf[r] = 0;

		// resolve parameter
		int pos = 0;
		while (_rdbuf[pos] != ' ' && _rdbuf[pos] != 0)
		{
			_cmd[pos] = _rdbuf[pos];
			pos++;
		}
		_cmd[pos] = 0;
		if (_rdbuf[pos] != 0)
		{
			pos++;
			int len = pos;
			while (_rdbuf[pos] != ' ' && _rdbuf[pos] != 0) //the first parameter
			{
				_filename1[pos - len] = _rdbuf[pos];
				pos++;
			}
			_filename1[pos - len] = 0;
		}
		else // there is not the first parameter
		{
			_filename1[0] = 0;
		}
		if (_rdbuf[pos] != 0) // there is the second parameter
		{
			pos++;
			int len = pos;
			while (_rdbuf[pos] != ' ' && _rdbuf[pos] != 0) // read the second parameter
			{
				_filename2[pos - len] = _rdbuf[pos];
				pos++;
			}
			_filename2[pos - len] = 0;
		}
		else // there is not the second parameter
		{
			_filename2[0] = 0;
		}

		//比对用户输入内容执行相应命令
		// ls = print all file and directory of current directory
		// cd = enter a directory, './' is current directory, '../' is previous directory
		// mkdir = create a directory
		// touch = create a file
		// wt = write to a file
		// rd = read from a file
		// rm = delete a file
		// help = print the instruction of file system
		// exit = exit file system 
		// clear
		if (strcmp(_cmd, "ls") == 0)
		{
			cmd_ls(_curdir);
		}
		else if (strcmp(_cmd, "cd") == 0)
		{
			//printf("\ncurrent dir: %s", _curdir);
			//printf("\ntarget dir: %s\n\n", _filename1);
			cd(_curdir, _filename1);
		}
		else if (strcmp(_cmd, "mkdir") == 0)
		{
			mkdir(_curdir, _filename1);
		}
		else if (strcmp(_cmd, "touch") == 0)
		{
			touch(_curdir, _filename1);
		}
		else if (strcmp(_cmd, "rm") == 0)
		{
			// 0 means regular file, 1 means directory
			if (strcmp(_filename1, "-r") == 0)
			{
				rm(_curdir, _filename2, 1);
			}
			else
			{
				rm(_curdir, _filename1, 0);
			}
		}
		else if (strcmp(_cmd, "wt") == 0)
		{
			wt(_curdir, _filename1);
		}
		else if (strcmp(_cmd, "rd") == 0)
		{
			rd(_curdir, _filename1);
		}
		else if (strcmp(_cmd, "help") == 0)
		{
			clear();
			fsComList();
		}
		else if (strcmp(_cmd, "clear") == 0)
		{
			clear();
		}
		else if (strcmp(_cmd, "exit") == 0)
		{
			break;
		}
		else
			printf("error: no command named %s\n", _cmd);
	}
}
```

```
void cd(char *cur_dir, char *next_dir_name)
{
	// special directory
	if (next_dir_name[0] <= 0)
	{
		printf("cd:: error: command cd need one parameter.\n");
		return;
	}
	if (next_dir_name[0] == ' ')
	{
		printf("cd:: error: directory cannot start with space.\n");
		return;
	}

	int length = 0;
	for (int i = 0; ; i++)
	{
		if (next_dir_name[i] == '\0')
			break;
		length = length + 1;
	}
	// printf("\nlength is %d\n", length);

	// idea : count the number of '.' and '/', so we know whether the operation is './' or '../'
	for (int i = 0; ;)
	{
		if (i >= length)
			break;

		if (next_dir_name[i] == '.')
		{
			int dotNum = 0;// '.' number
			int lineNum = 0; // '/' number
			while (i < length)
			{
				if (next_dir_name[i] == '.') {
					i++;
					dotNum++;
				}
				else {
					break;
				}
			}
			if (dotNum >= 3) {
				printf("Error input, './ is current directory, '../' is previous directory\n");
				return;
			}
			if (next_dir_name[i] != '/') {
				printf("Error input, './ is current directory, '../' is previous directory\n");
				return;
			}
			while (i < length)
			{
				if (next_dir_name[i] == '/') {
					lineNum++;
					i++;
				}
				else {
					break;
				}
			}
			if (lineNum >= 2) {
				printf("Error input\n");
				return;
			}

			if (lineNum == 1 && dotNum == 1) {
				; // do nothing
			}
			else if (lineNum == 1 && dotNum == 2) {
				cdPreDirectory(cur_dir);
			}
		}
		else {
			
			if(next_dir_name[i] == '/') // path like this : x/y/z
			{
				i++;
			}
			char temp[10];
			int count = 0;
			while (i < length)
			{
				if (next_dir_name[i] != '.' && next_dir_name[i] != '/') {
					temp[count] = next_dir_name[i];
					i++;
					count++;
				}
				else {
					break;
				}
			}
			temp[count] = 0; // this is very important, don't forget
			cdNextDirectory(cur_dir, temp);
		}
	}
	
}

// return current directory after cd
void cdPreDirectory(char *cur_dir)
{
	int i = 0;
	while(1) // find the end of current directory and store in i
	{
		if (cur_dir[i] == '/' && cur_dir[i + 1] == 0)
		{
			break;
		}
		i++;
	}

	if (i > 0)
	{
		cur_dir[i--] = 0;
		while (1)
		{
			if (cur_dir[i] == '/')
			{
				break;
			}
			cur_dir[i] = 0;
			i--;
		}
	}

	return; // cd ./ is current directory, cd ../ is pre directory,
					// we only need to update the current directory and directory view
}

// enter next directory
void cdNextDirectory(char* cur_dir, char *next_dir_name)
{
// cd deeper directory
	//printf("\n%s",cur_dir);
	//printf("\n%s\n",next_dir_name);

	char path[32] = "$";
	int i = 0;
	while (1)
	{
		if (cur_dir[i] == 0)
			break;
		path[i + 1] = cur_dir[i];
		i++;
	}
	i++;
	for (int j = 0;; j++)
	{
		if (next_dir_name[j] == 0)
			break;
		path[i++] = next_dir_name[j];
	}

	//printf("2path:%s\n", path);
	path[i] = '/';
	i++;
	path[i] = 0;
	//printf("3path:%s\n", path);

	int fd = open(path, O_RDWR);
	if (fd == -1)
	{
		printf("No such directory.\n");
		return;
	}
	close(fd);

	strcat(cur_dir, next_dir_name); // update current directory
	strcat(cur_dir, "/");
}

void mkdir(char *cur_dir, char *new_dir_name)
{
	if (new_dir_name[0] <= 0)
	{
		printf("mkdir:: error: command mkdir need one parameter.\n");
		return;
	}
	if (new_dir_name[0] == ' ')
	{
		printf("mkdir:: error: directory's name cannot start with space.\n");
		return;
	}
	char path[32] = "$"; // identifier of file directory
	int i = 0;
	while (1)
	{
		if (cur_dir[i] == 0)
			break;
		path[i + 1] = cur_dir[i];
		i++;
	}
	i++;

	for (int j = 0;; j++)
	{
		if (new_dir_name[j] == 0)
			break;
		path[i++] = new_dir_name[j];
	}
	path[i] = 0;

	int fd = open(path, O_CREAT);

	if (fd != -1)
	{
		close(fd);
	}
	else
	{
		printf("mkdir error: directory exists.\n");
	}
}
```

# 4 遇到的问题

#### Make image 时出现的问题

1.  **Fatal error: sys/cdefs.h: No such file or directory**
    1.  解决方法：命令行输入：
    2.  ```Apache
        sudo apt-get --reinstall install libc6 libc6-dev
        ```

1.  **Could not get lock /var/lib/dpkg/lock-frontend**
    1.  解决方法：命令行输入：
    2.  ```undefined
        sudo rm /var/lib/dpkg/lock-frontend
        ```

1.  **mount: ./mnt/floppy/: mount point does not exist.**
    1.  解决方法：在mnt文件夹下面新建floppy文件夹，需要命令行新建，无法鼠标新建


**[错误: fatal error: bits/libc-header-start.h: No such file or directory #include ](https://www.cnblogs.com/xuyaowen/p/libc-header-start.html)**

出现这个错误时，这多半是你所编译的项目是在64位机器上生成32位的项目，你需要安装对应的gcc 32位的库；此时检查gcc一定有-m32的存在；

你系统中gcc没有安装multilib 库；使用这个库可以在64位的机器上产生32位的程序或者库文件；

选择：apt install gcc-multilib进行完善安装；

####  在Ubuntu22.04中修改代码后的编译过程中出现了重定义问题。

在网上查阅解决方案时发现是由于使用gcc 10.0以上版本就会出现该错误，Ubuntu22.04的gcc版本为11.2.0, 于是ubuntu22.04上使用gcc-9版本

![img](https://gs0deem2h7.feishu.cn/space/api/box/stream/download/asynccode/?code=ZDk2OGE1ZTM0MjkwNjRmNzE1ZDM2OWIzNGNmZWY0MjRfNkhuNGR6OE9yY212ZmNFM2NHUHd5SU5kRjg3M0tTNFJfVG9rZW46Ym94Y254TG9rRktRYWpGMHA0V1Y2OXplYkRkXzE2NjAyMTkwODk6MTY2MDIyMjY4OV9WNA)解决方法：

1.   下载gcc-9与g++-9 

     sudo apt install gcc-9 g++-9

2.   将gcc g++版本都切换为9

     -   sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 100
     -   sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100
3. 再次查看gcc版本，可以看到版本已经变成9.4.0了

    -   gcc -v
# 5 成员分工

| 学号    | 姓名   | 分工                 |
| :------ | :----- | :------------------- |
| 2051488 | 韩可欣 | 开机动画、控制台、计算器|                  
| 2053380 | 彭浩   | 文件管理、扫雷、日历 |
| 2053512 | 孙博闻 | 进程管理、贪吃蛇   |

# 6 项目地址

https://github.com/main-voice/SummerOS

在final分支里


