#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	pid_t s32pid;
	int s32Level;
	char pcLevel[5] = "";

	if(2 != argc)
	{
		printf("Argument Error!\n");
		exit(EXIT_FAILURE);
	}

	s32Level = atoi(argv[1]);
	//printf("%d\n", s32Level);

	if(s32Level > 1)
	{

		s32pid = fork();
		if(0 == s32pid)
		{
			// Child
			sprintf(pcLevel, "%d", s32Level - 1);
			if(0 > execlp("./tree", "tree", pcLevel, NULL))
			{
				printf("Execlp Error!\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
		}

		s32pid = fork();
		if(0 == s32pid)
		{
			// Child
			sprintf(pcLevel, "%d", s32Level - 1);
			if(0 > execlp("./tree", "tree", pcLevel, NULL))
			{
				printf("Execlp Error!\n");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
		}

	}

	printf("Level %d PID = %d!\n", s32Level , getpid());
	sleep(60);
	
	return 0;
}
