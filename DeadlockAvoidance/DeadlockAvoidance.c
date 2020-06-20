/*	Programmer: Isaac Tucker	
	Solution: 3 threads attempting to access a resrouce for read/write.
	Threads will go through monitor to see if resrouce is avaialble.
	If unavailable then timer will start and process will try again
	timer has lapsed.							*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

void function(void *ptr);
int monitor(void *ptr);
void waitRand(int time);

int counter = 0;
FILE * logOutput;
sem_t semaphore;	//to be used in monitor

struct Node {
	void *data;
	struct Node *next;
};

struct Node *start = NULL;

void printList(struct Node *node) {
	printf("*****\nList:\n");
	fprintf(logOutput, "*****\nList:\n");
	while (node != NULL) {
		printf("%s\n", (char *)node->data);
		fprintf(logOutput, "%s\n", (char *)node->data);
		node = node->next;
	}
	printf("*****\n");
	fprintf(logOutput, "*****\n");
}

void addNode(struct Node** head_ref, void *new_data) {
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	struct Node *last = *head_ref;
	
	new_node->data = new_data;
	new_node->next = NULL;
	
	if(*head_ref == NULL) {
		*head_ref = new_node;
		return;
	}
	
	while(last->next != NULL) {
		last = last->next;
	}
	
	last ->next = new_node;
	counter++;
	return;
}

int main(int argt, char *argv[]) {
	pthread_t thread1, thread2, thread3;
	logOutput = fopen("logOutput.txt","w");
	
	char *msg1 = "Thread 1";
	char *msg2 = "Thread 2";
	char *msg3 = "Thread 3";
	
	sem_init(&semaphore, 0, 1);	//initialize the semaphore
	
	pthread_create (&thread1, NULL, (void *) &function, (void *) msg1);
	pthread_create (&thread2, NULL, (void *) &function, (void *) msg2);
	pthread_create (&thread3, NULL, (void *) &function, (void *) msg3);
	
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
	
	sem_destroy(&semaphore);	//destroy semaphore once done
	
	printList(start);
	return 0;
}

void function (void *ptr) {
	char *msg = (char *)ptr;
	waitRand(0);		//To simulate threads needing resource at random times
	while(counter < 6) {	//To only allow access to resource 5 times (for assignment sake)
		fprintf(logOutput, "%s is trying to access the resouce.\n", msg);
		printf("%s is trying to access the resouce.\n", msg);
		int s = monitor(msg);
		if(s == -1) {
			fprintf(logOutput, "   %s is starved. Trying again in 2 sec.\n", msg);
			printf("   %s is starved. Trying again in 2 sec.\n", msg);
			sleep(2);
		}	
	}
	pthread_exit(0);	//once max counter hit, exit threads
}

int monitor(void *ptr) {
	int success = sem_trywait(&semaphore); //protect buffer with semaphore.
	if(success != 0) { return -1; }
	char *msg = (char *)ptr;
	
	printf("%s has the resouce.\n", msg);
	fprintf(logOutput, "%s has the resouce.\n", msg);
	waitRand(0);		//simulate random processing times
	addNode(&start, msg);
	printf("%s is releasing the resouce.\n", msg);
	fprintf(logOutput, "%s is releasing the resouce.\n", msg);
	sem_post(&semaphore); 	//exit the semaphore for other items can enter
	waitRand(2);		//simulate cooldown time before starting again.
}

void waitRand(int time) {	//simulate some randomness
	srand(pthread_self());
	int rand_wait = (rand() % 5);
	sleep(rand_wait + time);
}
