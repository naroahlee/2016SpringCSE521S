#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sched.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_CORE_NO     (3)
#define IRT_NUM (500000000)
/*
 * Set affinity of the task. pin it to a dedicated core 
 */
static void set_cpu(int s32CPUNo)
{
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(s32CPUNo, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
	{
        perror("sched_setaffinity");
        exit(EXIT_FAILURE);
    }
	return;
}

static void set_sched(void)
{
    struct sched_param sched;
    sched.sched_priority = 99;
    if (sched_setscheduler(getpid(), SCHED_RR, &sched) < 0)
	{
        perror("sched_setscheduler");
        exit(EXIT_FAILURE);
	}
	return;
}

int main(int argc, char *argv[])
{
    sigset_t allsigs;
    int cur_val = 0;
	int s32CPUNo = 0;
	int s32CHDNo = 0;
	int s32i = 0;
	int s32pid = 0;

	if(argc != 3)
	{
		printf("Error!\n");
		exit(EXIT_FAILURE);
	}

	s32CPUNo = atoi(argv[1]);
	s32CHDNo = atoi(argv[2]) - 1;
	if(s32CPUNo < 0 || s32CPUNo > MAX_CORE_NO)
	{
		printf("OUT of Range\n");
		exit(EXIT_FAILURE);
	}

	printf("CPU bind: %d\n", s32CPUNo);
	set_cpu(s32CPUNo);
	printf("Set Sched:RR\n");
	set_sched();

	for(s32i = 0; s32i < s32CHDNo; s32i++)
	{
		s32pid = fork();
		if(0 == s32pid)
		{
			/* Child */
			break;
		}	
		else
		{
			/* Parent */
		}
	}
	

	for(s32i = 0; s32i < IRT_NUM; s32i++)
	{
	}
    
    exit(EXIT_SUCCESS);
}

