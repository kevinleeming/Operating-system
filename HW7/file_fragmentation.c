#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#define FILESIZE 65536
#define FILENUM 1300
#define FRAGNUM 650
#define LARGEFILESIZE 50000000

int main(int argc, char **argv){
	FILE *fp[FILENUM];
	char filename[50];
	int i, j;
	struct timeval start, end;
	gettimeofday(&start, 0);
	for(i = 0; i < FILENUM; i++){
		bzero(&filename, sizeof(filename));
		sprintf(filename, "test%d.txt", i);
		fp[i] = fopen(filename, "w+");
		if(fp[i]){
			int k;
			for(k = 0; k < FILESIZE; k++){
				fprintf(fp[i], "a");
			}
			fclose(fp[i]);
		}
		else{
			printf("file %d open error\n", i);
		}
		int fd = fileno(fp[i]);
		fsync(fd);
	}
	for(i = 0; i < FRAGNUM; i++){
		j = i * 2;
		bzero(&filename, sizeof(filename));
		sprintf(filename, "test%d.txt", j);
		int status;
		if((status = remove(filename)) != 0){
			printf("remove file %d failed\n", j);
		}
	}
	FILE *large;
	large = fopen("largefile.txt", "w+");
	if(large){
		int k;
                for(k = 0; k < LARGEFILESIZE; k++){
                	fprintf(large, "a");
                }
		fclose(large);
	}
	pid_t p1;
	int status;
	if((p1 = fork()) == 0){
		system("sudo filefrag -v largefile.txt");
		exit(0);
	}
	waitpid(p1, &status, 0);
	gettimeofday(&end, 0);
	int sec = end.tv_sec - start.tv_sec;
	int usec = end.tv_usec - start.tv_usec;
	printf("elapsed %f s\n", (((float)sec*1000.0) + ((float)usec/1000.0))/1000.0);
	return 0;
}
