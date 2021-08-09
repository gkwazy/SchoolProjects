//
//  main.cpp
//  unixShell
//
//  Created by Garret Wasden on 2/23/21.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <vector>
#include "shelpers.hpp"


char *commandOptions[] = {
    (char*)"alias",
    (char*)"cat",
    (char*)"cd",
    (char*)"chmod",
    (char*)"chown",
    (char*)"curl",
    (char*)"df",
    (char*)"diff",
    (char*)"echo",
    (char*)"exit",
    (char*)"find",
    (char*)"finger",
    (char*)"free",
    (char*)"grep",
    (char*)"group",
    (char*)"head",
    (char*)"history",
    (char*)"less",
    (char*)"ls",
    (char*)"man",
    
    NULL
};
// code from libray exsample changed to fit out purpose;
char * Commandgenerator(const char *text, int state){
    char *command;
    static int commandList, length;

    if (!state) {
        commandList = 0;
        length = (int)strlen(text);
    }

    while ((command = commandOptions[commandList++])) {
        if (strncmp(command, text, length) == 0) {
            return strdup(command);
        }
    }

    return NULL;
}

// code from libray exsample changes the behavoir of he rl_completion_matches function;
char ** commandcompletion(const char *text, int start, int end){
    return rl_completion_matches(text, Commandgenerator);
}


int main(int argc, const char * argv[]) {
// auto complete function from library
    rl_attempted_completion_function = commandcompletion;
    while(char *buffer = readline("> ")){
            if (buffer) {
                free(buffer);
            }
//grabing tokens and command for shelpers functions
        auto tokens = tokenize(buffer);
        auto commands = getCommands(tokens);
        
// looping through commands and forking
        for (int i = 0; i < commands.size(); ++i){
           const auto& currentCommand = commands[i];
            int commandFork = fork();
            if (commandFork < 0){
                perror("fork broke");
            }
            else if(commandFork == 0){
//start of child after fork()
                //checking if command has been piped or not
                if (currentCommand.fdStdin != 0){
                    if (dup2(currentCommand.fdStdin, 0) == -1){
                        perror("error with dup2 and stdin");
                    }
                }
                //checking if command has been piped or not
                if (currentCommand.fdStdout != 1){
                    if (dup2(currentCommand.fdStdout, 1) == -1){
                        perror("error with dup2 and stdout");
                    }
                }
                
                if (execvp(currentCommand.exec.c_str(), const_cast<char* const *> (currentCommand.argv.data())) == -1){
                    perror("exec");
                }
            }
            else{
//start of Parent after fork()
                //checks if command is "cd" because that need to be ran in the shell
                if (strcmp(currentCommand.exec.c_str(), "cd") == 0){
                    //checks is cd has any arguments with it
                    if (currentCommand.argv.size() > 2){
                        if (chdir(currentCommand.argv[1]) != 0){
                        }
                    }else{
                        if (chdir(getenv("HOME")) != 0){
                            perror("cd did not find HOME");
                        }
                    }
                }
                
                int parentWait = wait(NULL);
                //closing pipes
                if (currentCommand.fdStdin != 0){
                    if(close(currentCommand.fdStdin) == -1){
                        perror("error in closing stdin");
                    }
                }
                //closing pipes
                if (currentCommand.fdStdout != 1){
                    if(close(currentCommand.fdStdout) == -1){
                        perror("error in closing stdin");
                    }
                }
            }
        }
    }
    return 0;
}
