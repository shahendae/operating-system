#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#define MAXLINE 512
#define MAXARGS 20

int parseline(char *line, char **argv)
{
  int i = 0;
  char *token = " \n\t";
  argv[i] = strtok(line, token);
  while ((argv[i] != NULL) && (i+1 < MAXARGS)) {
   argv[++i] = strtok((char *) 0, token);
  }
  return i;
}

int isBuiltInCommand(char *cmd)
{
    if((strcmp(cmd, "cd") == 0 ) || (strcmp(cmd, "exit") == 0 ) )

        return 1;
    else
        return -1;
}

void executeBuiltInCommand(char *cmd, int argc, char **argv)
{
    if(strcmp(cmd, "cd") == 0){
        if(argc > 2)
            perror("ERROR - Too many args for cd. \n");
        else if(!argv[1])
            chdir(getenv("HOME"));
        else
        {
         if (chdir(argv[1]) != 0) {
      perror("shell");
    }
    }
    }
    if(strcmp(cmd, "exit") == 0){
    _exit(EXIT_FAILURE);

    }
    }


int main()
{

char line[MAXLINE];
char *argv[MAXARGS];
 int argc;
 int status;
 pid_t pid ;
 int n,background;


 while (1) {
  printf("shell>");
  fgets(line, 99999999, stdin);
   if(strlen(line)>512){printf("ERROR MAX Exceeded\n");exit(0);}
  argc = parseline(line, argv);


   if(argc == 0)
    {
        continue;
    }

    if(isBuiltInCommand(line)){
        executeBuiltInCommand(line, argc, argv);
        continue;
    }

   else{


      while(argv[n]!=NULL)
        n++;
    if(strcmp(argv[--n],"&")==0){
        argv[n]=NULL;
        background=1;
        }

  pid = fork();
  if (pid < 0) {
    perror("Shell Program fork error");
    _exit(EXIT_FAILURE);
  }
  else if (pid == 0) {
      execvp(argv[0], argv);
  }
  else {
  if (background==0) {

    do {
     waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
   }
  }
 }

 }

 }


