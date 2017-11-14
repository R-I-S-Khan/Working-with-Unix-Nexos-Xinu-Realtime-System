#include <kernel.h>
#include <shell.h>
#include <string.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
static semaphore synch12 = NULL;
static semaphore synch23 = NULL;
static  semaphore synch31 = NULL;
int counter1 = 0;
void process1(void)
 {
	while(1) {
		//signal(synch12);
		sleep(rand()%1000);
		wait(synch12);
		fprintf(TTY0, "Count before is: %d, now proc1 will increase it by 1\n", counter1);
		counter1++;
		//wait(synch12);
		signal(synch23);
		//sleep(rand()%1000);
		//wait(synch12);
	}
}
void process2(void) 
{
	//printf("process2\n");
	while(1) {
		//printf("inside while of 2\n");
		sleep(rand()%1000);
		wait(synch23);
		//signal(synch23);
		sleep(rand()%1000);
		fprintf(TTY0, "Count before is %d, now proc2 will increase it by 1\n", counter1);
		counter1++;
		//wait(synch23);
		//signal(synch31);
		//sleep(rand()%1000);
		//wait(synch23);
		signal(synch31);
	}
}
void process3(void) {
	while(1) {
		//sleep(rand()%1000);
		//wait(synch31);
		//signal(synch31);
		sleep(rand()%1000);
		wait(synch31);
		fprintf(TTY0, "Count before is %d, now proc3 will increase it by 1\n", counter1);
		counter1++;
		//wait(synch31);
		//signal(synch12);
		//sleep(rand()%1000);
		//wait(synch31);
		signal(synch12);
	}
}
command	xsh_semaphore2(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[]) {
	synch12 = newsem(0);
	synch23 = newsem(0);
	synch31 = newsem(0);
		
	ready(create((void*)process1, 1024, 20, "PROCESS1", 2, 0, NULL), RESCHED_NO);
	ready(create((void*)process2, 1024, 20, "PROCESS2", 2, 0, NULL), RESCHED_NO);
	ready(create((void*)process3, 1024, 20, "PROCESS3", 2, 0, NULL), RESCHED_NO);
	signal(synch31);
	return OK;
}



