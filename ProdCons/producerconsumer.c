/*	Programmer: Isaac Tucker
	Explanation: I used the code as provided by the assignment and then implemented a queue for 	the put and get. Once the Queue is full the producer will stop producing until there is room 	 within the Q again. I am using two threads to run the program itself, one producer and one 		consumer. */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void put(int i);
int get();

/****************************************
 *     ITEMS PROVIDED BY ASSIGNMENT     *
 ****************************************/
int theProduct;

int produce() { return theProduct++; }
void consume(int i) { printf("Consumed %i\n", i); }     //added the word 'consumed'

void producer() {
	int i;
	while(1) {
		i = produce();
		put(i);
	}
}

void consumer() {
	int i;
	while(1) {
		i = get();
		consume(i);
	}
}

/****************************************
 *   END ITEMS PROVIDED BY ASSIGNMENT   *
 ****************************************/
#define MAX 10	//Max Buffer Size
static char buffer[MAX]; 
int f = -1, r = -1, c = -1;

void put(int i) {
	if(c < MAX) {
		if(c<0) {
			r = f = 0;
			buffer[r] = i;
			c = 1;
		} else {
			r++;
			buffer[r % 10] = i;
			c++;
		}
		printf("Produced %i\n",i);
	} else {
		theProduct--; //don't want to increment if we're not actually loading into buffer.
		sleep(1);
	}
}
int get() {
	sleep(1);
	int i;
	if(c > 0) {
		i = buffer[f % MAX];
		f++;
		c--;
		return i;
	} else {
		sleep(1);
	}
} 

int main(int argt, char *argv[]) {
	pthread_t thread_prod;
	pthread_t thread_cons;
	
	pthread_create(&thread_prod,   NULL, (void *)consumer, NULL);
	pthread_create(&thread_cons,   NULL, (void *)producer, NULL);
	
	pthread_join(thread_prod, NULL);
	pthread_join(thread_cons, NULL);
	
	return 0;
}
