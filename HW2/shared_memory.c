#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/time.h>

unsigned int *InitialMatrix(int d);

int main(){
	int dim;
	int shmID, shmID2; // id of shared memory

	printf("Input matrix dimension : ");
	scanf("%d", &dim);

	shmID = shmget(IPC_PRIVATE, sizeof(unsigned int)*dim*dim, IPC_CREAT|0666); // create shared memory to store Answer matrix
	if(shmID == -1){
		fprintf(stderr, "Shared memory get error\n");
        perror("Shared memory get error");
        exit(EXIT_FAILURE);
	}

	unsigned int *matrix; // the two initial matrix(identical)
	matrix = InitialMatrix(dim);
	shmID2 = shmget(IPC_PRIVATE, sizeof(unsigned int)*dim*dim, IPC_CREAT|0666); // store Initial matrix
	if(shmID2 == -1){
		fprintf(stderr, "Shared memory get error\n");
        perror("Shared memory get error");
        exit(EXIT_FAILURE);
	}

	pid_t pid;
	struct timeval start, end; // compute elapsed time
	unsigned int *shmAddr;
	unsigned int *shmAddr2;
	unsigned int checksum = 0;
	int status = 0;
	
	int process;
	for(process = 1; process <= 16; process++){
		int i;
		for(i = 0; i < process; i++){ // original parent process will fork process_num times(create process_num children)
										  // for each child process to execute their routines
			gettimeofday(&start, 0);
			pid = fork();

			if(pid < 0){ // Fork Failed
				fprintf(stderr, "Fork Failed");
       		 	exit(EXIT_FAILURE);
			}

			else if(pid == 0){ // Child process
				shmAddr = (unsigned int*)shmat(shmID, NULL, 0); // attach memory to child process
				if(shmAddr < 0){
					fprintf(stderr, "Shared memory attach error\n");
        			perror("Shared memory attach error");
        			exit(EXIT_FAILURE);
				}
				shmAddr2 = (unsigned int*)shmat(shmID2, NULL, 0); // Initial matrix
				if(shmAddr2 < 0){
					fprintf(stderr, "Shared memory attach error\n");
        			perror("Shared memory attach error");
        			exit(EXIT_FAILURE);
				}
				shmAddr2 = matrix;
				
				int j;
				for(j = 0; j < dim; j++){
					if(i == (j % process)){ // ith process compute j row answer , which j mode (process_num) = i
						int k, p;
						for(k = 0; k < dim; k++){ // for j row , compute each element(shmAddr[j][k])
							shmAddr[j*dim+k] = 0;
							for(p = 0; p < dim; p++){
								shmAddr[j*dim+k] += (shmAddr2[j*dim+p] * shmAddr2[p*dim+k]);
							}
						}
					}
				}

				int detach = shmdt(shmAddr); // detach from shared memory
				if(detach == -1){
			        fprintf(stderr, "Shared memory detach error\n");
			        perror("Shared memory detach error");
			        exit(EXIT_FAILURE);
			    }
			    detach = shmdt(shmAddr2);

				exit(0); // After child process done its job , then exit
			}
		}

		pid_t wpid;
		while((wpid = wait(&status)) != -1){;} // when parent calls wait() and return value is -1 ,
											   // meaning there's no child process to wait
		// parent process
		// compute elapsed time first
		gettimeofday(&end, 0);
		int sec = end.tv_sec - start.tv_sec;
		int usec = end.tv_usec - start.tv_usec;

		shmAddr = (unsigned int*)shmat(shmID, NULL, 0); // Attach memory to parent process
		if(shmAddr < 0){
			fprintf(stderr, "Shared memory attach error\n");
        	perror("Shared memory attach error");
        	exit(EXIT_FAILURE);
		}
	
		int p;
		for(p = 0; p < (dim*dim); p++){ // compute checksum
			checksum += shmAddr[p];
		}

		printf("Multiplying matrices using %d ", process);
		if(process == 1)
			printf("process\n");
		else
			printf("processes\n");
		printf("Elapsed time: %f sec, Checksum: %u\n", (sec*1000+(usec/1000.0))/1000, checksum);

		checksum = 0;

		int de = shmdt(shmAddr); // detach from shared memory
		if(de == -1){
			fprintf(stderr, "Shared memory detach error\n");
			perror("Shared memory detach error");
			exit(EXIT_FAILURE);
		}

	}
		shmctl(shmID, IPC_RMID, NULL) ;
		shmctl(shmID2, IPC_RMID, NULL) ;

	return 0;

}

unsigned int *InitialMatrix(int d){
	unsigned int *m;
	m = (unsigned int*)malloc(sizeof(unsigned int)*d*d);
	int i, j;
	for(i = 0; i < d; i++){
		for(j = 0; j < d; j++){
			m[i*d+j] = i*d+j;
		}
	}

	return m;
}
