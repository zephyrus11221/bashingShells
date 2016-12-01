#ifndef SHELL_COMMANDS_h
#define SHELL_COMMANDS_h
int * cd1(char *dir);//changes cwd, dir is target. Returns 0 for success, -1 for error.
int * check(char *comm);//checks if comm is one of our functions, returns 0 for yes, -1 for no
int * pipe1(char *comm);//pipes
int * redirWrite(char *comm);//calls functions using given redirection, overwrite
int * redirApp(char *comm);//calls functions using given redirection, append

#endif
