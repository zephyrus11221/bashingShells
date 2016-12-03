# bashingShells
By Sebastian Dittgen, Stephan Doan, Matthew Zhu
~~~

**Features**

*Basic programs such as 'ls' can be called.
*Redirection works
*Changing cwd works

---

**Failed Features**

*Moving to previous commands with arrow keys
*Piping

---

**Bugs**

*Semicolon usage is gimmicky with white space.

---

**Headers**

~~~
void commCentral(char *comm);//checks for shell programs, and prepares the child to run them. Includes pipe, cd, and redirections
void rmChar (char arr[], int start);//removes the char at the index equal to start of the array myarray[]
~~~