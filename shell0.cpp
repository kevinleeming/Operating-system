#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string>

using namespace std;

int main(){
	string s;
	pid_t pid;
	pid = fork();
	if(pid < 0){
		fprintf(stderr,"Fork Failed");
		exit(-1);
	}

	else if(pid == 0){
		execlp("/bin/ls","ls",NULL);
	}
	else{
		wait(NULL);
		printf("Child Complete!\n");
		cin >> s;
		if(s == ">ls"){
			execlp("ls","ls",NULL);
		}
		else if(s == ">ps"){
			execlp("/bin/ps","ps",NULL);
		}
		exit(0);
	}
}
