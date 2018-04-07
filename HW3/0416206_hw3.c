#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#define MAXSIZE 1000000
#define THREADNUM 16

int arr_mt[MAXSIZE];
int arr_st[MAXSIZE];
int num;
int pivot1, pivot2, pivot3, pivot4, pivot5, pivot6, pivot7;
pthread_t thread[THREADNUM];
sem_t all_thread_create, sem_t1, sem_t2, sem_t3, sem_t4, sem_t5, sem_t6, sem_t7, sem_t8, sem_t9, sem_t10, sem_t11, sem_t12, sem_t13, sem_t14, sem_t15, all_thread_finish;
sem_t sem8to9, sem9to10, sem10to11, sem11to12, sem12to13, sem13to14, sem14to15;

void bubble_sort(int *arr, int downIndex, int upperIndex){
	int i, j;
	for(i = upperIndex - 1; i > downIndex; i--){
		for(j = downIndex; j < i; j++){
			if(arr[j] > arr[j + 1]){
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void print_array(int *arr, int down, int up){
	int i;
	for(i = down; i <= up; i++){
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void *thread_funct(void *p){
	pthread_t id = pthread_self();

	if(pthread_equal(id, thread[1])){
		sem_wait(&all_thread_create);

		int i, j;
		pivot1 = 0;
		i = 0;
		j = num;


        if(i != j){
            do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot1] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot1]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot1];
		arr_mt[pivot1] = arr_mt[j];
		arr_mt[j] = temp;
		pivot1 = j;
        }

		//print_array(arr_mt, 0, num-1);

		sem_post(&sem_t2);
		sem_post(&sem_t3);
	}

	else if(pthread_equal(id , thread[2])){
		sem_wait(&sem_t2);

		int i, j;
		pivot2 = 0;
		i = pivot2;
		j = pivot1;

        if(i != j){
            do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot2] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot2]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot2];
		arr_mt[pivot2] = arr_mt[j];
		arr_mt[j] = temp;
		pivot2 = j;
        }


		//print_array(arr_mt, 0, pivot1-1);


		sem_post(&sem_t4);
		sem_post(&sem_t5);
	}

	else if (pthread_equal(id, thread[3])){
		sem_wait(&sem_t3);

		int i, j;
		pivot3 = pivot1 + 1;
		i = pivot3;
		j = num;

        if(i != j){
            do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot3] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot3]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot3];
		arr_mt[pivot3] = arr_mt[j];
		arr_mt[j] = temp;
		pivot3 = j;
        }


		//print_array(arr_mt, pivot1, num-1);


		sem_post(&sem_t6);
		sem_post(&sem_t7);
	}

	else if(pthread_equal(id, thread[4])){
		sem_wait(&sem_t4);

		int i, j;
		pivot4 = 0;
		i = pivot4;
		j = pivot2;


		if(i != j){
            do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot4] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot4]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot4];
		arr_mt[pivot4] = arr_mt[j];
		arr_mt[j] = temp;
		pivot4 = j;
		}


		//print_array(arr_mt, 0, pivot2-1);


		sem_post(&sem_t8);
		sem_post(&sem_t9);
	}

	else if (pthread_equal(id, thread[5])){
		sem_wait(&sem_t5);

		int i, j;
		pivot5 = pivot2 + 1;
		i = pivot5;
		j = pivot1;


		if(i != j){
            do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot5] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot5]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot5];
		arr_mt[pivot5] = arr_mt[j];
		arr_mt[j] = temp;
		pivot5 = j;
		}


		//print_array(arr_mt, pivot2 + 1, pivot1-1);

		sem_post(&sem_t10);
		sem_post(&sem_t11);
	}

	else if (pthread_equal(id, thread[6])){
		sem_wait(&sem_t6);

		int i, j;
		pivot6 = pivot1+1;
		i = pivot6;
		j = pivot3;


		if(i != j){
           do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot6] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot6]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot6];
		arr_mt[pivot6] = arr_mt[j];
		arr_mt[j] = temp;
		pivot6 = j;
		}



		//print_array(arr_mt, pivot1 + 1, pivot3-1);

		sem_post(&sem_t12);
		sem_post(&sem_t13);
	}

	else if (pthread_equal(id, thread[7])){
		sem_wait(&sem_t7);

		int i, j;
		pivot7 = pivot3 + 1;
		i = pivot7;
		j = num;


		if(i != j){
            do{
			do{
				i++;
			}while(arr_mt[i] < arr_mt[pivot7] && i < j);
			do{
				j--;
			}while(arr_mt[j] > arr_mt[pivot7]);
			if(i < j){
				int temp = arr_mt[i];
				arr_mt[i] = arr_mt[j];
				arr_mt[j] = temp;
			}
		}while(i<j);

		int temp = arr_mt[pivot7];
		arr_mt[pivot7] = arr_mt[j];
		arr_mt[j] = temp;
		pivot7 = j;
		}


		//print_array(arr_mt, pivot3 + 1, num-1);

		sem_post(&sem_t14);
		sem_post(&sem_t15);
	}

	else if (pthread_equal(id, thread[8])){
		sem_wait(&sem_t8);
		bubble_sort(arr_mt, 0, pivot4);
		sem_post(&sem8to9);
	}

	else if (pthread_equal(id, thread[9])){
		sem_wait(&sem_t9);
		bubble_sort(arr_mt, pivot4, pivot2);
		sem_wait(&sem8to9);
		sem_post(&sem9to10);
	}

	else if (pthread_equal(id, thread[10])){
		sem_wait(&sem_t10);
		bubble_sort(arr_mt, pivot2, pivot5);
		sem_wait(&sem9to10);
		sem_post(&sem10to11);
	}

	else if (pthread_equal(id, thread[11])){
		sem_wait(&sem_t11);
		bubble_sort(arr_mt, pivot5, pivot1);
		sem_wait(&sem10to11);
		sem_post(&sem11to12);
	}

	else if (pthread_equal(id, thread[12])){
		sem_wait(&sem_t12);
		bubble_sort(arr_mt, pivot1, pivot6);
		sem_wait(&sem11to12);
		sem_post(&sem12to13);
	}

	else if (pthread_equal(id, thread[13])){
		sem_wait(&sem_t13);
		bubble_sort(arr_mt, pivot6, pivot3);
		sem_wait(&sem12to13);
		sem_post(&sem13to14);
	}

	else if (pthread_equal(id, thread[14])){
		sem_wait(&sem_t14);
		bubble_sort(arr_mt, pivot3, pivot7);
		sem_wait(&sem13to14);
		sem_post(&sem14to15);
	}

	else if (pthread_equal(id, thread[15])){
		sem_post(&all_thread_create);
		sem_wait(&sem_t15);
		bubble_sort(arr_mt, pivot7, num);
		sem_wait(&sem14to15);
		sem_post(&all_thread_finish);
	}
	pthread_exit(NULL);
}

int main(){
	FILE *fp;
	char filename[20];
	char c;
	int index = 0;
	int i;

	printf("The file name of test data : ");
	while((c = getchar()) != '\n'){
		filename[index] = c;
		index++;
	}
	filename[index] = '\0';

	fp = fopen(filename, "r");

	if(!fp){
		printf("This file doesn't exist!\n");
		return 0;
	}

	fscanf(fp, "%d", &num);
	for(i = 0; i < num; i++){
		fscanf(fp, "%d", &arr_mt[i]);
		arr_st[i] = arr_mt[i];
	}
	fclose(fp);

	struct timeval start, end;

	gettimeofday(&start,0);

	sem_init(&all_thread_create, 0, 0);
	sem_init(&sem_t1, 0, 0);
	sem_init(&sem_t2, 0, 0);
	sem_init(&sem_t3, 0, 0);
	sem_init(&sem_t4, 0, 0);
	sem_init(&sem_t5, 0, 0);
	sem_init(&sem_t6, 0, 0);
	sem_init(&sem_t7, 0, 0);
	sem_init(&sem_t8, 0, 0);
	sem_init(&sem_t9, 0, 0);
	sem_init(&sem_t10, 0, 0);
	sem_init(&sem_t11, 0, 0);
	sem_init(&sem_t12, 0, 0);
	sem_init(&sem_t13, 0, 0);
	sem_init(&sem_t14, 0, 0);
	sem_init(&sem_t15, 0, 0);
	sem_init(&all_thread_finish, 0, 0);
	sem_init(&sem8to9, 0, 0);
	sem_init(&sem9to10, 0, 0);
	sem_init(&sem10to11, 0, 0);
	sem_init(&sem11to12, 0, 0);
	sem_init(&sem12to13, 0, 0);
	sem_init(&sem13to14, 0, 0);
	sem_init(&sem14to15, 0, 0);

	int pc;
	for(i = 0; i < THREADNUM; i++){
		pc = pthread_create(&thread[i], NULL, thread_funct, NULL);
	}
	sem_wait(&all_thread_finish);

	gettimeofday(&end,0);

	int sec = end.tv_sec-start.tv_sec;
	int usec = end.tv_usec=start.tv_usec;
	printf("MT : elapsed %f ms\n", sec*1000+(usec/1000.0));

	gettimeofday(&start,0);
	bubble_sort(arr_st, 0, num);
	gettimeofday(&end,0);
	sec = end.tv_sec-start.tv_sec;
	usec = end.tv_usec=start.tv_usec;
	printf("ST : elapsed %f ms\n", sec*1000+(usec/1000.0));

	FILE *outfile1, *outfile2;

	outfile1 = fopen("output1.txt", "w");
	for(i = 0; i < num; i++){
		fprintf(outfile1, "%d", arr_mt[i]);
		if(i != num-1){
			fprintf(outfile1, " ");
		}
	}

	outfile2 = fopen("output2.txt", "w");
	for(i = 0; i < num; i++){
		fprintf(outfile2, "%d", arr_st[i]);
		if(i != num-1){
			fprintf(outfile2, " ");
		}
	}

	fclose(outfile1);
	fclose(outfile2);


	return 0;

}
