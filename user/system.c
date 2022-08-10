
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
							system.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
													Forrest Yu, 2005
													 ph & sbw,  2022
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

#define NULL ((void *)0)

/*======================================================================*
                            	Process Manager
 *======================================================================*
							                        	 sbw    2022
 *======================================================================*/


 /*****************************************************************************
 *                                processManager
 *****************************************************************************/
 //进程管理主函数
 
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


//welcome ui of process manager
void Process_Welcome()
{
	printf("      ====================================================================\n");
	printf("      #                            Welcome to          *******  *******  #\n");
	printf("      #                     SummerOS ~ Process Manager *     *  *        #\n");
	printf("      #                                                *     *  *******  #\n");
	printf("      #                                                *     *        *  #\n");
	printf("      #                                                *******  *******  #\n");
	printf("      #                                                                  #\n");	
	printf("      #             [COMMAND]                 [FUNCTION]                 #\n");
	printf("      #                                                                  #\n");
	printf("      #           $ clear        |     clear the cmd                     #\n");
	printf("      #           $ ps           |     show all process                  #\n");
	printf("      #           $ block id     |     block a process                   #\n");
	printf("      #           $ start id     |     start a process                   #\n");
	printf("      #           $ quit         |     quit process management system    #\n");
	printf("      #           $ help         |     show command list of this system  #\n");
	printf("      #                                                                  #\n");
	printf("      #                                                                  #\n");
	printf("      #                 $ Designed by  HKX PH SBW $                      #\n");
	printf("      #                 $ TONGJI UNIVERSITY  2022 $                      #\n");
	printf("      ====================================================================\n");	    

	printf("\n\n");
}


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
int get_Mag(int n)
{
	int mag = 1;
	for (int i = 0; i < n; i++)
	{
		mag = mag * 10;
	}
	return mag;
}

//get process's id
int get_Pid(char str[])
{
	int length = 0;
	for (; length < MAX_FILENAME_LEN; length++)
	{
		if (str[length] == '\0')
		{
			break;
		}
	}
	int pid = 0;
	for (int i = 0; i < length; i++)
	{
		if (str[i] - '0' > -1 && str[i] - '9' < 1)
		{
			pid = pid + (str[i] + 1 - '1') * get_Mag(length - 1 - i);
		}
		else
		{
			pid = -1;
			break;
		}
	}
	return pid;
}

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

//restart a process
void start_a_Process(char str[])
{
	int pid = get_Pid(str);

	if (pid >= 8 || pid < 0)
	{
		printf("The pid out of the range\n");
	}
	else if (proc_table[pid].p_flags == 1)
	{
		printf("This process is already running.\n");
	}
	else
	{
		proc_table[pid].priority = 1;
		proc_table[pid].p_flags = 1;
		printf("Target process is running.\n");
	}

	show_all_Process();
}


/*======================================================================*
								File System
 *======================================================================*

 *======================================================================*/
/*************************************************************
 * @title  file system
 * @author ph
 * @data 2022
 * ***********************************************************/

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

void fsComList()
{
	clear();
	printf("==============================================================================\n");
	printf("   Command List           :\n");
	printf("1. ls                     : List all files of current directory.\n");
	printf("2. touch     [filename]   : Create a new file in current directory.\n");
	printf("3. rm        [filename]   : Delete a file in current directory.\n");
	printf("4. rd        [filename]   : Print the content of a file.\n");
	printf("5. wt        [filename]   : Write new content at the end of the file\n");
	printf("6. mkdir     [dirname]    : Create a new directory in current directory\n");
	printf("7. cd        [dirname]    : Enter a directory, './ is current,'../' is previous\n");
	printf("8. help                   : Display the command list\n");
	printf("9. exit                   : Exit file system\n");
	printf("a. clear                  : Clear the screen\n");
	printf("==============================================================================\n");
	printf("\n\n");
}

void fs_welcome()
{
	clear();
	printf("      ====================================================================\n");
	printf("      #                                         Welcome to               #\n");
	printf("      #                                   SummerOS's File Manager        #\n");
	printf("      #              &              |                                    #\n");
	printf("      #             & &             |           [ COMMAND ]              #\n");
	printf("      #            &   &            |                                    #\n");
	printf("      #           &     &           | 1 --- ls                           #\n");
	printf("      #          &   *   &          | 2 --- touch [filename]             #\n");
	printf("      #         &         &         | 3 --- rm    [filename]             #\n");
	printf("      #        &           &        | 4 --- rd    [filename]             #\n");
	printf("      #       &   *     *   &       | 5 --- wt    [filename]             #\n");
	printf("      #      &&             &&      | 6 --- mkdir [filename]             #\n");
	printf("      #     &&               &&     | 7 --- cd    [filename]             #\n");
	printf("      #    && &&&&       &&&& &&    | 8 --- help                         #\n");
	printf("      #   &&& ---  &&&&&  --- &&&   | 9 --- exit                         #\n");
	printf("      #     &&&&&  -----  &&&&&     |                                    #\n");
	printf("      #           &&&&&&&           |    Now press ENTER to continue     #\n");
	printf("      #                                                                  #\n");
	printf("      #                 $ Designed by  HKX PH SBW $                      #\n");
	printf("      #                 $ TONGJI UNIVERSITY  2022 $                      #\n");
	printf("      ====================================================================\n");	    

	printf("\n\n");
}

void cmd_ls(char *cur_dir)
{
	printf("      ==================================\n");
	printf("      |%12s   |%12s    |\n", "file_name", "type");
	printf("      |---------------|----------------|\n");
	if (ls(cur_dir) < 0)
		printf("ls error");
	printf("      ==================================\n\n");
}

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

void touch(char *cur_dir, char *filename)
{
	if (filename[0] <= 0)
	{
		printf("touch:: error: command touch need one parameter.\n");
		return;
	}
	if (filename[0] == ' ')
	{
		printf("touch:: error: file name cannot start with space.\n");
		return;
	}

	char path[32] = "#"; // identifier of normal file directory
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
		if (filename[j] == 0)
			break;
		path[i++] = filename[j];
	}
	path[i] = 0;
	int fd = open(path, O_CREAT); // create a file using orange's kernel
	if (fd != -1)
	{
		close(fd);
	}
	else
	{
		printf("touch error: file exists.\n");
	}
}

void rm(char *cur_dir, char *filename, int flag)
{
	if (filename[0] <= 0)
	{
		printf("mkdir:: error: command rm need one parameter which should be the name of file.\n");
		return;
	}

	char path[32] = "#";

	if (flag == 1)
	{
		path[0] = '$';
	}
	int i = 0;
	// transform char* to char[];
	while (1)
	{
		if (cur_dir[i] == 0)
			break;
		path[i + 1] = cur_dir[i];
		i++;
	}
	i++;
	// transform char* to char[];
	for (int j = 0;; j++)
	{
		if (filename[j] == 0)
			break;
		path[i++] = filename[j];
	}

	path[i] = 0;
	int fd = unlink(path); // delete a file

	if (fd == 0)
	{
		printf("Remove success: %s has been removed!\n", filename);
	}
	else if (fd == -2)
	{
		printf("Remove fail: cannot find the file : %s!\n", filename);
	}
	else if (fd != -3)
	{
		printf("Failed to remove the file : %s!\n", filename);
	}
}

void wt(char *cur_dir, char *filename)
{
	if (filename[0] <= 0)
	{
		printf("mkdir:: error: command wt need one parameter which should be the name of file.\n");
		return;
	}

	char path[32] = "#";
	int i = 0;
	// transform char* to char[];
	while (1)
	{
		if (cur_dir[i] == 0)
			break;
		path[i + 1] = cur_dir[i];
		i++;
	}
	i++;

	// transform char* to char[];
	for (int j = 0;; j++)
	{
		if (filename[j] == 0)
			break;
		path[i++] = filename[j];
	}

	path[i] = 0;
	int fd = open(path, O_RDWR);
	if (fd == -1)
	{
		printf("Failed to open the file : %s!\n", filename);
		return;
	}

	char tty_name[] = "/dev_tty0";
	int fd_stdin = open(tty_name, O_RDWR);
	if (fd_stdin == -1)
	{
		printf("Failed to write file!\n");
		return;
	}
	char writeBuf[4096]; // write buffer
	printf("Enter the content you want write to the file:\n");
	int final = read(fd_stdin, writeBuf, 4096);
	writeBuf[final] = 0;

	write(fd, writeBuf, final + 1);

	printf("\nWrite %d bytes in the file : %s\n", final, filename);

	close(fd);
}

void rd(char *cur_dir, char *filename)
{
	if (filename[0] <= 0)
	{
		printf("mkdir:: error: command rd need one parameter which should be the name of file.\n");
		return;
	}

	char path[32] = "#";
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
		if (filename[j] == 0)
			break;
		path[i++] = filename[j];
	}

	path[i] = 0; // end of path

	int fd = open(path, O_RDWR); // using oranges kernel
	if (fd == -1)
	{
		printf("Failed to open %s!\n", filename);
		return;
	}

	char buf[4096]; // read buffer
	int rdFlag = read(fd, buf, 4096);
	if (rdFlag == -1) // 读取文件内容失败
	{
		printf("Failed to read file!\n");
		close(fd);
		return;
	}

	printf("Content of file %s :\n", filename);

	printFileContent(filename, buf);

	close(fd);
}

void printFileContent(char *filename, char *buf)
{
	printf("      ==================================\n");
	printf("      |%17s%15s|\n", filename, " ");
	printf("      ==================================\n");

	int count = 0;

	char temp[33];

	while (buf[count] != NULL)
	{
		copyStr(temp, buf, 32);
		printf("       %s\n", temp);
		buf += 32;
		count += 32;
	}

	printf("       %s\n", buf); // this is the rest of the file content
	printf("      ==================================\n\n");
}
