#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/time.h>
#define MAXSIZE 1000000
#define THREADNUM 16
#define threadpool_invalid -1
#define threadpool_lock_failure -2
#define threadpool_queue_full -3
#define threadpool_shutdown -4
#define threadpool_thread_failure -5
#define threadpool_graceful  1
#define immediate_shutdown 1
#define graceful_shutdown 2

typedef struct {
    void (*function)(void *);
    void *argument;
} threadpool_task_t;

struct threadpool_t {
  pthread_mutex_t lock;
  pthread_cond_t notify;
  pthread_t *threads;
  threadpool_task_t *queue;
  int thread_count;
  int queue_size;
  int head;
  int tail;
  int count;
  int shutdown;
  int started;
};
typedef struct threadpool_t threadpool_t;

int arr_mt[MAXSIZE];
int arr_st[MAXSIZE];
int num;
int pivot1, pivot2, pivot3, pivot4, pivot5, pivot6, pivot7;
pthread_t thread[THREADNUM];
sem_t all_thread_create, sem_t1, sem_t2, sem_t3, sem_t4, sem_t5, sem_t6, sem_t7, sem_t8, sem_t9, sem_t10, sem_t11, sem_t12, sem_t13, sem_t14, sem_t15, all_thread_finish;
sem_t sem8to9, sem9to10, sem10to11, sem11to12, sem12to13, sem13to14, sem14to15;

threadpool_t *threadpool_create(int thread_count, int queue_size, int flags);
int threadpool_add(threadpool_t *pool, void (*routine)(void *),void *arg, int flags);
int threadpool_destroy(threadpool_t *pool, int flags);
static void *threadpool_thread(void *threadpool);
int threadpool_free(threadpool_t *pool);
void multiple_thread(int);
void write_file(int i);

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

void task_1(){
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
		sem_post(&sem_t2);
		sem_post(&sem_t3);
}

void task_2(){
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
        sem_post(&sem_t2);
		sem_post(&sem_t4);
		sem_post(&sem_t5);
}

void task_3(){
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
        sem_post(&sem_t3);
		sem_post(&sem_t6);
		sem_post(&sem_t7);
}	

void task_4(){
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
		sem_post(&sem_t4);
		sem_post(&sem_t8);
		sem_post(&sem_t9);
}

void task_5(){
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
		sem_post(&sem_t5);
		sem_post(&sem_t10);
		sem_post(&sem_t11);
}

void task_6(){
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
		sem_post(&sem_t6);
		sem_post(&sem_t12);
		sem_post(&sem_t13);
}

void task_7(){
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
		sem_post(&sem_t7);
		sem_post(&sem_t14);
		sem_post(&sem_t15);
}
void task_8(){
	sem_wait(&sem_t8);
	bubble_sort(arr_mt, 0, pivot4);
	sem_post(&sem_t8);
	sem_post(&sem8to9);
}

void task_9(){
	sem_wait(&sem_t9);
	bubble_sort(arr_mt, pivot4, pivot2);
	sem_post(&sem_t9);
	sem_wait(&sem8to9);
	sem_post(&sem8to9);//for destroy purpose
	sem_post(&sem9to10);
}

void task_10(){
	sem_wait(&sem_t10);
	bubble_sort(arr_mt, pivot2, pivot5);
	sem_post(&sem_t10);
	sem_wait(&sem9to10);
	sem_post(&sem9to10);
	sem_post(&sem10to11);
}

void task_11(){
	sem_wait(&sem_t11);
	bubble_sort(arr_mt, pivot5, pivot1);
	sem_post(&sem_t11);
	sem_wait(&sem10to11);
	sem_post(&sem10to11);
	sem_post(&sem11to12);
}

void task_12(){
	sem_wait(&sem_t12);
	bubble_sort(arr_mt, pivot1, pivot6);
	//job done
	sem_post(&sem_t12);
	sem_wait(&sem11to12);
	sem_post(&sem11to12);
	sem_post(&sem12to13);
}

void task_13(){
	sem_wait(&sem_t13);
	bubble_sort(arr_mt, pivot6, pivot3);
	//job done
	sem_post(&sem_t13);
	sem_wait(&sem12to13);
	sem_post(&sem12to13);
	sem_post(&sem13to14);
}

void task_14(){
	sem_wait(&sem_t14);
	bubble_sort(arr_mt, pivot3, pivot7);
	//job done
	sem_post(&sem_t14);
	sem_wait(&sem13to14);
	sem_post(&sem13to14);
	sem_post(&sem14to15);
}
void task_15(){
	sem_wait(&sem_t15);	
	bubble_sort(arr_mt, pivot7, num);
	//job done
	sem_post(&sem_t15);
	sem_wait(&sem14to15);
	sem_post(&sem14to15);
	sem_post(&all_thread_finish);
}


int main(){
	FILE *fp;
	int i;

	fp = fopen("input.txt", "r");

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

	for(int i = 1; i <= 8; i++){
		printf("multi-thread with thread pools size = %d\n", i);
		multiple_thread(i);
		write_file(i);
		for(int j = 0; j < num; j++){
			arr_mt[j] = arr_st[j];
		}
	}
	return 0;
}

void multiple_thread(int num_thread){
	struct timeval start, end;
	gettimeofday(&start,0);

	int ret;

	ret = sem_init(&sem_t2, 0, 0);
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
	sem_init(&sem8to9, 0, 0);
	sem_init(&sem9to10, 0, 0);
	sem_init(&sem10to11, 0, 0);
	sem_init(&sem11to12, 0, 0);
	sem_init(&sem12to13, 0, 0);
	sem_init(&sem13to14, 0, 0);
	sem_init(&sem14to15, 0, 0);

	ret = sem_init(&all_thread_finish, 0, 0);
	threadpool_t *tp;
	tp = threadpool_create(num_thread, 16, 0);
	
	ret = threadpool_add(tp, &task_1, 0, 0);
	ret = threadpool_add(tp, &task_2, 0, 0);
	ret = threadpool_add(tp, &task_3, 0, 0);
	ret = threadpool_add(tp, &task_4, 0, 0);
	ret = threadpool_add(tp, &task_5, 0, 0);	
	ret = threadpool_add(tp, &task_6, 0, 0);
	ret = threadpool_add(tp, &task_7, 0, 0);
	ret = threadpool_add(tp, &task_8, 0, 0);
	ret = threadpool_add(tp, &task_9, 0, 0);
	ret = threadpool_add(tp, &task_10, 0, 0);
	ret = threadpool_add(tp, &task_11, 0, 0);
	ret = threadpool_add(tp, &task_12, 0, 0);
	ret = threadpool_add(tp, &task_13, 0, 0);
	ret = threadpool_add(tp, &task_14, 0, 0);
	ret = threadpool_add(tp, &task_15, 0, 0);

	ret = sem_wait(&all_thread_finish);
	sem_post(&all_thread_finish);
	sem_destroy(&all_thread_finish);

	threadpool_destroy(tp, 0);

	sem_destroy(&sem_t2);
	sem_destroy(&sem_t3);
	sem_destroy(&sem_t4);
	sem_destroy(&sem_t5);
	sem_destroy(&sem_t6);
	sem_destroy(&sem_t7);
	sem_destroy(&sem_t8);
	sem_destroy(&sem_t9);
	sem_destroy(&sem_t10);
	sem_destroy(&sem_t11);
	sem_destroy(&sem_t12);
	sem_destroy(&sem_t13);
	sem_destroy(&sem_t14);
	sem_destroy(&sem_t15);
	sem_destroy(&sem8to9);
	sem_destroy(&sem9to10);
	sem_destroy(&sem10to11);
	sem_destroy(&sem11to12);
	sem_destroy(&sem12to13);
	sem_destroy(&sem13to14);
	sem_destroy(&sem14to15);

	gettimeofday(&end,0);
	int sec = end.tv_sec-start.tv_sec;
	int usec = end.tv_usec-start.tv_usec;
	printf("elapsed %f ms\n", (end.tv_sec-start.tv_sec)*1000+((end.tv_usec-start.tv_usec)/1000.0));
}

threadpool_t *threadpool_create(int thread_count, int queue_size, int flags)
{
    threadpool_t *pool;
    int i;
    (void) flags;

    if(thread_count <= 0 ||  queue_size <= 0) {
        return NULL;
    }
    pool = (threadpool_t *)malloc(sizeof(threadpool_t));

    pool->thread_count = 0;
    pool->queue_size = queue_size;
    pool->head = pool->tail = pool->count = 0;
    pool->shutdown = pool->started = 0;

    pool->threads = (pthread_t *)malloc(sizeof(pthread_t) * thread_count);
    pool->queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t) * queue_size);

    if((pthread_mutex_init(&(pool->lock), NULL)) || (pthread_cond_init(&(pool->notify), NULL)) || (!pool->threads) || (!pool->queue)){
        return NULL;
    }

    for(i = 0; i < thread_count; i++) {
        if(pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void*)pool)) {
            threadpool_destroy(pool, 0);
            return NULL;
        }
        pool->thread_count++;
        pool->started++;
    }
    return pool;
}

int threadpool_add(threadpool_t *pool, void (*function)(void *), void *argument, int flags)
{
    int err = 0;
    int next;
    (void) flags;

    if(!pool || !function) return threadpool_invalid;

    if(pthread_mutex_lock(&(pool->lock))) return threadpool_lock_failure;

    next = (pool->tail + 1) % pool->queue_size;

    do {
        if(pool->count == pool->queue_size) {
            err = threadpool_queue_full;
            break;
        }

        if(pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }

        // load the jobs
        pool->queue[pool->tail].function = function;
        pool->queue[pool->tail].argument = argument;
        pool->tail = next;
        pool->count += 1;

        if(pthread_cond_signal(&(pool->notify)) != 0) {
            err = threadpool_lock_failure;
            break;
        }
    } while(0);

    if(pthread_mutex_unlock(&pool->lock) != 0) {
        err = threadpool_lock_failure;
    }

    return err;
}

int threadpool_destroy(threadpool_t *pool, int flags)
{
    int i, err = 0;

    if(!pool) return threadpool_invalid;

    if(pthread_mutex_lock(&(pool->lock))) return threadpool_lock_failure;
    do {
        if(pool->shutdown) {
            err = threadpool_shutdown;
            break;
        }
        pool->shutdown = (flags & threadpool_graceful) ? graceful_shutdown : immediate_shutdown;

        if((pthread_cond_broadcast(&(pool->notify))) || (pthread_mutex_unlock(&(pool->lock)))) {
            err = threadpool_lock_failure;
            break;
        }

        for(i = 0; i < pool->thread_count; i++) {
            if(pthread_join(pool->threads[i], NULL)) {
                err = threadpool_thread_failure;
            }
        }
    } while(0);

    if(!err) {
        threadpool_free(pool);
    }
    return err;
}

int threadpool_free(threadpool_t *pool)
{
    if(!pool || pool->started > 0) {
        return -1;
    }

    if(pool->threads) {
        free(pool->threads);
        free(pool->queue);
        pthread_mutex_lock(&(pool->lock));
        pthread_mutex_destroy(&(pool->lock));
        pthread_cond_destroy(&(pool->notify));
    }
    free(pool);    
    return 0;
}

static void *threadpool_thread(void *threadpool)
{
    threadpool_t *pool = (threadpool_t *)threadpool;
    threadpool_task_t task;

    while(1){
        pthread_mutex_lock(&(pool->lock));

        while((pool->count == 0) && (!pool->shutdown)){
            pthread_cond_wait(&(pool->notify), &(pool->lock));
        }

        if((pool->shutdown == immediate_shutdown) || ((pool->shutdown == graceful_shutdown) && (pool->count == 0))){
            break;
        }

        // Grab our task 
        task.function = pool->queue[pool->head].function;
        task.argument = pool->queue[pool->head].argument;
        pool->head = (pool->head + 1) % pool->queue_size;
        pool->count -= 1;

        pthread_mutex_unlock(&(pool->lock));

        // Get to work 
        (*(task.function))(task.argument);
    }

    pool->started--;

    pthread_mutex_unlock(&(pool->lock));
    pthread_exit(NULL);
    return(NULL);
}

void write_file(int i){
	FILE *fp;
	char filename[12];

	if(i == 1){
		strcpy(filename, "output_1.txt");
	}
	else if(i == 2){
		strcpy(filename, "output_2.txt");
	}
	else if(i == 3){
		strcpy(filename, "output_3.txt");
	}
	else if(i == 4){
		strcpy(filename, "output_4.txt");
	}
	else if(i == 5){
		strcpy(filename, "output_5.txt");
	}
	else if(i == 6){
		strcpy(filename, "output_6.txt");
	}
	else if(i == 7){
		strcpy(filename, "output_7.txt");
	}
	else if(i == 8){
		strcpy(filename, "output_8.txt");
	}
	fp = fopen(filename, "w");

	for(int k = 0; k < num; k++){
		if(k == num-1)
			fprintf(fp, "%d", arr_mt[k]);
		else
			fprintf(fp, "%d ", arr_mt[k]);
	}
	fprintf(fp, "\n");
}
