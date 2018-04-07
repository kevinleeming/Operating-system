#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

#define ARRAY_ROW_SIZE 10
#define ARRAY_COL_SIZE 50


int main(int argc, char **argv){

  while(1){
    printf("> ");

    //----read command----
    int rw = 0, cl = 0;
    char in_com[ARRAY_ROW_SIZE][ARRAY_COL_SIZE];
    while(1){
      char c;
      c = getchar();
      if(c == '\n')
        break;
      else if(c == ' '){
        rw++;
        cl = 0;
      }
      else{
        in_com[rw][cl] = c;
        cl++;
      }
    }
    //---------------------

    //--------exit---------
    if(in_com[0][0] == 'e' && in_com[0][1] == 'x' && in_com[0][2] == 'i' && in_com[0][3] == 't')
      break;
    //---------------------

    bool ParentWaitChild = true; // check whether end of input command equals to '&'
    if(in_com[rw][0] == '&'){
      rw--;
      ParentWaitChild = false;
    }

    int pipeRow;
    bool Pipe = false; // check whether is the pipe
    for(int i = 0; i < rw+1; i++){
      if(in_com[i][0] == '|' && in_com[i][1] != '|'){
        Pipe = true;
        pipeRow = i;
        break;
      }
    }

    bool IO = false;
    int IOrow;
    for(int i = 0; i < rw+1; i++){ // check whether is output redirection
      if(in_com[i][0] == '>'){
        IO = true;
        IOrow = i + 1;
      }
    }
    
    //------------------------pipe------------------------
    if(Pipe){
      int fd[2]; // declare a two-d array, store file_descriptor of the pipe (two side)
                 // fd[0] means read side, fd[1] means write side
      pid_t ppid, gpid; // pid of child process and grandchild process

      pipe(fd);

      ppid = fork();

      if(ppid == -1){
        perror("Failed forking");
        exit(-1);
      }

      else if(ppid == 0){ // Child process
        gpid = fork();

        if(gpid < 0){
          fprintf(stderr, "Fork Failed");
          exit(-1);
        }

        else if(gpid == 0){ // Grandchild process
          close(fd[1]); // Child process closes up output side of pipe
          dup2(fd[0], 0); // duplicate fd[0] and take it as stdin
          close(fd[0]);
          if((rw-pipeRow) == 1){
            execlp(in_com[pipeRow + 1], in_com[pipeRow + 1], NULL);
          }
          else if((rw-pipeRow) == 2){
            execlp(in_com[pipeRow + 1], in_com[pipeRow + 1], in_com[pipeRow + 2], NULL);
          }
          else if((rw-pipeRow) == 3){
            execlp(in_com[pipeRow + 1], in_com[pipeRow + 1], in_com[pipeRow + 2], in_com[pipeRow + 3], NULL);
          }
          else if((rw-pipeRow) == 4){
            execlp(in_com[pipeRow + 1], in_com[pipeRow + 1], in_com[pipeRow + 2], in_com[pipeRow + 3], in_com[pipeRow + 4], NULL);
          }
          else if((rw-pipeRow) == 5){
            execlp(in_com[pipeRow + 1], in_com[pipeRow + 1], in_com[pipeRow + 2], in_com[pipeRow + 3], in_com[pipeRow + 4], in_com[pipeRow + 5], NULL);
          }
          //exit(0);
          
        }

        else{ // Child process
          close(fd[0]); // Grandchild process closes up input side of pipe
          dup2(fd[1], 1); // duplicate fd[1] and take it as stdout
          close(fd[1]);
          if(pipeRow == 1){
            execlp(in_com[0], in_com[0], NULL);
          }
          else if(pipeRow == 2){
            execlp(in_com[0], in_com[0], in_com[1], NULL);
          }
          else if(pipeRow == 3){
            execlp(in_com[0], in_com[0], in_com[1], in_com[2], NULL);
          }
          else if(pipeRow == 4){
            execlp(in_com[0], in_com[0], in_com[1], in_com[2], in_com[3], NULL);
          }
          else if(pipeRow == 5){
            execlp(in_com[0], in_com[0], in_com[1], in_com[2], in_com[3], in_com[4], NULL);
          }
          exit(0);
        }
        
      }

      else{ // Parent process
        wait(NULL);
        usleep(50000);
        //printf ("Child Complete\n");
      }
        
    }
    //----------------------------------------------------

    else if(IO){
      int fd[2];
      pid_t pid = fork();
      FILE *ptr;
      ptr = fopen(in_com[IOrow],"w");

      close(fd[1]);

      if (pid == -1) {
          perror("fork");
      } 
      else if (pid == 0) {   
          execlp(in_com[0], in_com[0], NULL);
      } 
      else {
          
      }
    }

    else{
      pid_t pid;
      pid = fork();

      if (pid < 0) { // error occurred 
        fprintf(stderr, "Fork Failed");
        exit(-1);
      }
      // prevent zombie process
      else if(pid == 0){ // child process
        if(!fork()){              // grandchild process , as child process exit , 
          if((rw+1) == 1){        // its return value would be caught by init ( because it became orphan process )
            execlp(in_com[0],in_com[0],NULL);
          }
          else if((rw+1) == 2){
            execlp(in_com[0],in_com[0],in_com[1],NULL);
          }
          else if((rw+1) == 3){
            execlp(in_com[0],in_com[0],in_com[1],in_com[2],NULL);
          }
          else if((rw+1) == 4){
            execlp(in_com[0],in_com[0],in_com[1],in_com[2],in_com[3],NULL);
          }
          else if((rw+1) == 5){
            execlp(in_com[0],in_com[0],in_com[1],in_com[2],in_com[3],in_com[4],NULL);
          }
          exit(0);
        }

        else{
          exit(0);
        }
        /*if((rw+1) == 1){
          execlp(in_com[0],in_com[0],NULL);
        }
        else if((rw+1) == 2){
          execlp(in_com[0],in_com[0],in_com[1],NULL);
        }
        else if((rw+1) == 3){
          execlp(in_com[0],in_com[0],in_com[1],in_com[2],NULL);
        }
        else if((rw+1) == 4){
          execlp(in_com[0],in_com[0],in_com[1],in_com[2],in_com[3],NULL);
        }
        else if((rw+1) == 5){
          execlp(in_com[0],in_com[0],in_com[1],in_com[2],in_com[3],in_com[4],NULL);
        }
        exit(0); */// if user input command that doesn't exist , we have to terminate this child process
      }

      else{
          // parent process
          if(ParentWaitChild){
            wait (NULL);
            usleep(50000);
            //printf ("Child Complete\n");
          }
          //exit(0);
      }
    }

  }

  return 0;
}
