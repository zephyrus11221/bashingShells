#ifndef SHELL_COMMANDS_h
#define SHELL_COMMANDS_h
void sigHand(int sigNum);//creates handle for user signal inputs
void commCentral(char *comm);//checks for shell programs, and prepares the child to run them. Includes pipe, cd, and redirections
void rmChar (char arr[], int start);//removes the char at the index equal to start of the array myarray[]
#endif
