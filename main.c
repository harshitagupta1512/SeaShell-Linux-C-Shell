#include "def.h"

void CleanUpCommand(char * str) {
    int i = 0;
    char output[max_size];
    int output_iterator = 0;
    int spaceAddedBefore = 0;
    while (str[i] != '\0') {
        if(str[i] != ' ' && str[i] != '\t') {
            output[output_iterator++] = str[i++];
            spaceAddedBefore = 0;
            continue;
        }

        if(str[i] == ' ') {
            if(spaceAddedBefore == 1) {
                i++;
                continue;
            }
            else {
                output[output_iterator++] = str[i++];
                spaceAddedBefore = 1;
                continue;
            }
        }

        if(str[i] == '\t') {
            if(spaceAddedBefore == 1) {
                i++;
                continue;
            }
            else {
                output[output_iterator++] = ' ';
                ++i;
                spaceAddedBefore = 1;
                continue;
            }
        }

    }
    output[output_iterator] = '\0';

    int start = 0;

    while(output[start] != '\0' && (output[start] == ' ' || output[start] == '\t')) {
        ++start;
    }

    int end = strlen(output) - 1;

    while(end >= 0 && (output[end] == ' ' || output[start] == '\t')) {
        --end;
    }

    char new_output[max_size];

    int iter = 0;

    for(int i = start; i <= end; ++ i) {
        new_output[iter++] = output[i];
    }
    new_output[iter] = '\0';
    strcpy(str, new_output);
}


void runCommand(char* currCommand) {

    char tempCommand[max_size];
    strcpy(tempCommand, currCommand);

    if (history->NumEle < 20)
        Inject(history, currCommand);
    else
    {
        Pop(history);
        Inject(history, currCommand);
    }

    char currCommandName[max_size];
    unsigned long int l = strlen(currCommand);
    unsigned long int i = 0;

    while (currCommand[i] != ' ' && i < l) {
        currCommandName[i] = currCommand[i];
        i++;
    }

    currCommandName[i] = '\0';

    if (strcmp(currCommandName, "exit") == 0)
    {
        write_history();
        exit(0);

    }
    else if (strcmp(currCommandName, "echo") == 0)
        echo(currCommand);
    else if (strcmp(currCommandName, "pwd") == 0) {
        pwd();
    }
    else if (strcmp(currCommandName, "cd") == 0)
        cd(currCommand, homeDir);
    else if(strcmp(currCommandName,"pinfo") == 0)
        pinfo(tempCommand);
    else if(strcmp(currCommandName,"ls") == 0)
        ls(currCommand, homeDir);
    else if(strcmp(currCommandName, "repeat") == 0)
        repeat(currCommand);
    else if(strcmp(currCommandName, "history") == 0)
        getHistory(currCommand);
    else
        system_commands(currCommand);
}

int main(void)
{
    signal(SIGINT, SIGINT_handler);
    strcpy(lastAddedCommand ,"");
    numBgProc = 0;
    signal(SIGCHLD, SIGCHLD_handler);
    history = initQueue();
    getcwd(homeDir, max_size);
    load_history();
    strcpy(lastVisitedDir, "");

    //homeDir and lastVisitedDir are global variables

    char* command = (char*)malloc(max_size*sizeof (char));

    size_t x;
    x = max_size;
    char* token;
    const char s[2] = ";";      //deliminator
    char currCommand[max_size];
    while (1)
    {
        prompt(homeDir);

        getline(&command, &x, stdin);
        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';
        //REMOVE LAST \n CHARACTERmake
        token = strtok(command, ";");
        char commands[strlen(command)][max_size];
        int itr = 0;
        while (token != NULL)
        {
            strcpy(commands[itr++], token);
            token = strtok(NULL, ";");
        }
        for (int i = 0; i < itr; i++)
        {
            strcpy(currCommand, commands[i]);
            CleanUpCommand(currCommand);
            runCommand(currCommand);
        }
    }
}
