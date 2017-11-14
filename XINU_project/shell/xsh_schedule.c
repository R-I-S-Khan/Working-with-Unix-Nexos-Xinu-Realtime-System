#include <kernel.h>
#include <shell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gpio.h>
//#include <ctype.h>
//#include <unistd.h>
//#include <sys/times.h> 
#define NFRAME 6
#define NFRAME2 10
#define NSLOT 2
#define SLOT_T 5000
int tps,slot=0,frame=0;
//int tps, cycle=0, slot=0;
//clock_t now, then;
//struct tms n;
void one() {
  printf("Task 1 running\n");
  sleep(1000);
}

void two() {
  printf("Task 2 running\n");
  sleep(2000);
}

void three() {
  printf("Task 3 running\n");
  sleep(3000);
}

void four() {
  printf("Task 4 running\n");
  sleep(4000);
}

void burn() { 

printf ("burn cycle taking as there is no task \n ");
//clock_t bstart = times(&n);
sleep(5000);
//while ( ((now=times(&n))-then) < SLOT_T*tps/1000 ) {
/* burn time here */
//}
//printf("burn time = %2.2dms\n\n", (times(&n)-bstart)*1000/tps);
//then = now;
//cycle = NSLOT;
}

void (*ttable[NFRAME][NSLOT])() = {
{one, one},
{two, three},
{one, one},
{two, burn},
{one, one},
{burn, burn}};

void (*ttable2[NFRAME2][NSLOT])() = {
{one, three},
{two, burn},
{four, four},
{one, burn},
{two, two},
{one, burn},
{two,two},
{one , burn},
{one, burn},
{two, two}};

command xsh_schedule(ushort stdin, ushort stdout, ushort stderr, ushort nargs, char *args[])

{
	//tps = sysconf(_SC_CLK_TCK);
	//fprintf(stdout,"clock ticks/sec = %d\n\n", tps);
	if (nargs == 2 && strncmp(args[1],"--help",6) == 0)
    	{
        	fprintf(stdout, "Usage: clear\n");
        	fprintf(stdout, "Clears the terminal.\n");
       		 fprintf(stdout, "\t--help\t display this help and exit\n");
        	return SYSERR;
    	}
        char str[10];
        char *table1 = "1";
        char *table2 = "2";
        fprintf(stdout,"Enter 1 to get table 1 and 2 to get table 2\n");
	//gets(str);
	scanf("%s",str);        
        int choose1 = strcmp(str,table1);
        int choose2 = strcmp(str,table2);
        if(choose1 == 0){
		//tps = sysconf(_SC_CLK_TCK);
		//fprintf(stdout,"clock ticks/sec = %d\n\n", tps);
	    	while (1) {
			fprintf(stdout,"\nU = 0.75 < 1\n");
	      		fprintf(stdout,"\nStarting a new hyperperiod, H = 12\n");
			fprintf(stdout,"\nFrame size = 2\n");
			fprintf(stdout,"\n (Number of frames = 6) and (Number of slots in each frame = 2)\n");
		      	for (frame=0; frame <NFRAME; frame++)
			{ 
				fprintf (stdout,"\n Starting a new frame\n");
				for (slot=0; slot<NSLOT; slot++)
					(*ttable[frame][slot])();
			
			}
			
		}
        }
	else if (choose2 == 0){
	    	while (1) {
			fprintf(stdout,"\nU = 0.76 < 1\n");
		      	fprintf(stdout,"\n Starting a new hyperperiod, H= 20 \n");
			fprintf(stdout,"\nFrame size = 2\n");
			fprintf(stdout,"\n (Number of frames = 10) and (Number of slots in each frame = 2)\n");
		      	for (frame=0; frame <NFRAME2; frame++)
			{ 
				fprintf (stdout,"\n Starting a new frame\n");
				for (slot=0; slot<NSLOT; slot++)
					(*ttable2[frame][slot])();
			}
			
		}
	}
	 /* Just so the next prompt doesn't run on to this line */
    	fprintf(stdout, "\n");
 
   	 /* there were no errors so, return OK */
	return OK;
}
