/*	Programmer: Isaac Tucker
	Solultion: Make use of sem_t semaphore to ensure mutual exclusion 
	when accessing the char buf. This way one thread is writing and the 		
	other can read at separate times.
*/
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void function1(void *ptr);
void function2(void *ptr);
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
	sem_wait(&semaphore);	//protect buffer with semaphore.
	sleep(2);
	sprintf(buf, "%s", "Hello world - I am going to consume everything!!");
	sem_post(&semaphore); //exit the semaphore for other items can enter
	pthread_exit(0);
}
void function2 (void *ptr) {
	char *msg = (char *)ptr;
	printf("%s\n", msg);
	sleep(1);
	sem_wait(&semaphore);	//protect buffer with semaphore.
	printf("%s\n", buf);
	sem_post(&semaphore); //exit the semaphore for other items can enter
	pthread_exit(0);
}
