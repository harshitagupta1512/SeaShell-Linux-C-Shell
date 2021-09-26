#ifndef OSN_ASSI2_DEF_H
#define OSN_ASSI2_DEF_H

#include<stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <signal.h>
#include <sys/resource.h>

#define max_size 500
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1b[33m"

//Global Variables
char lastVisitedDir[max_size];
char homeDir[max_size];

struct proc{
    int pid;
    char procName[max_size];
    int deleted;
};

struct proc bgProc[max_size];
int numBgProc;
char lastAddedCommand[max_size];

void prompt(char* home);
void echo(char* command);
void pwd();
void cd(char* command, char* home);
void ls(char* command, char* home);
int countSpaces(char* str);
void system_commands(char* command);
void foreground(char* command);
void background(char* command);
void pinfo(char* command);
void findParent(char *parent, char* currDir);
void repeat(char* command);
void createPointers(char* command, char** argumentPointers);
void runCommand(char* currCommand);
int isDirectory(const char *path);
int processCommand(char* command, char dirName[max_size][max_size], int* dir_size, int* isA, int* isL, char* currDir, char* home);
void getPermissions(struct stat buf, char perm[11]);
void getProcessID(char* command, int* pid);
void getHistory(char* command);
void SIGINT_handler(int signal);
void SIGCHLD_handler(int signal);
void CleanUpCommand(char * str);
//----------------QUEUE------------------//

struct QueueEle
{
    char data[max_size];
    struct QueueEle *next;
    struct QueueEle *prev;
};
typedef struct QueueEle *PtrQueueEle;
typedef struct QueueEle QueueEle;
struct Queue
{
    PtrQueueEle Front;
    PtrQueueEle Rear;
    int NumEle;
};
typedef struct Queue *Queue;
void Pop(Queue D);                   //Remove from Front
void Inject(Queue D, char* x); //Add at Rear
Queue initQueue();
int IsEmpty(Queue D);
void deleteQueue(Queue D);
void printQueue(Queue D, int number);
void load_history();
void write_history();

//----------------------------------------//
Queue history;

#endif //OSN_ASSI2_DEF_H
