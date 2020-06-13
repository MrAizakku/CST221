/*	Programmer: Isaac Tucker
	Solultion: Make use of sem_t semaphore within a monitor construct to ensure mutual exclusion 	when accessing the char buf. This way one thread is writing and the other can read at separate 		times. As this is the monitor solution and C does not have inherent monitors a seperate 		structure which houses the semphore exclusivity is being used instead of having the wait and 	post within the seperate functions themselves; the semaphore is only housed within the monitor 		structure. */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void function1(void *ptr);
void function2(void *ptr);
void monitor(void *ptr);	//the structure in which the semaphore will be used.

char buf[256];		//could be very big in reality
sem_t semaphore;	//to enable mutex

int main(int argt, char *argv[]) {
	pthread_t first_thread;
	pthread_t second_thread;
	
	char *msg1 = "This is the first thread.";
	char *msg2 = "This is the second thread.";
	
	sem_init(&semaphore, 0, 1);	//initialize the semaphore
	
	pthread_create (&first_thread, NULL, (void *) &function1, (void *) msg1);
	pthread_create (&second_thread, NULL, (void *) &function2, (void *) msg2);
	
	pthread_join(first_thread, NULL);
	pthread_join(second_thread, NULL);
	
	sem_destroy(&semaphore);	//destroy semaphore once done
	
	return 0;
}
void function1 (void *ptr) {
	char *msg = (char *)ptr;
	printf("%s\n", msg);
	monitor("Thread 1 is writing to the buffer");
	pthread_exit(0);
}
void function2 (void *ptr) {
	char *msg = (char *)ptr;
	printf("%s\n", msg);
	sleep(2);
	monitor(NULL);
	pthread_exit(0);
}

void monitor(void *ptr) {
	sem_wait(&semaphore); //protect buffer with semaphore.
	char *msg = (char *)ptr;
	if(msg) {
		sprintf(buf, "%s", msg);
		sleep(2);
	}
	else {
		printf("%s\n", buf);
	}
	sem_post(&semaphore); //exit the semaphore for other items can enter
}
