#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

void main ()
{
//declaration variables
int ex_ch,cd_ch,e_ch;
system("clear");
while(1)
{
//arguments of command
char *arg[100],i=0;
//string from user
char su[50];

pid_t pid;
int status;

printf("Shell> ");
//get string from user
fgets(su,100,stdin);

//to separate command arguments
arg[0]= strtok (su," \n");

while (arg[i] != NULL)
{
//printf("\n%s\n",arg[i]);
i++;
arg[i]=strtok (NULL,"\n");
}
//terminate the program
e_ch=strcmp(su,"exit");
if (e_ch==0)
break;  // can use "exit(0);"

//create process for execute the command
pid=fork();
if (pid==0)
{
// to execute cd command
if ((*arg[0]=='c')&&(*(arg[0]+1)=='d'))
{
cd_ch=chdir(arg[1]);
//error handle of cd
if(cd_ch==-1)
printf("bash: cd: %s: No such file or directory\n",arg[1]);
}
// to execute rest of commands
else
{
ex_ch=execvp(arg[0],arg);
//error handle of commands
if (ex_ch==-1)
printf("command not found\n");
}

}
//parent process
else if (pid>0)
{
 waitpid(pid,&status,0);
//return ; // this cause break from while loop
}
else 
{
printf("process failed");
}

}

}
