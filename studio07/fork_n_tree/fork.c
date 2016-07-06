#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	pid_t s32pid;

	if(s32pid = fork())
	{
		if(0 == s32pid)
		{
			// Child
			printf("Parent!\n");
		}
		else
		{
			// parent
			printf("Child PID = %d\n", s32pid);
		}
	}
	
	return 0;
}
