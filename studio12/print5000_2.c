#include <stdio.h>
#include <signal.h>
#include <unistd.h>

#define size 5000

volatile int i;
char gacMsg[9] = "i:     \n";

int called [size];

void sigint_handler( int signum){
	called[i] = 1;
	return;
}

int main (int argc, char* argv[]){

	struct sigaction ss;
	int s32temp;

	ss.sa_handler = sigint_handler;
	ss.sa_flags = SA_RESTART;

	sigaction( SIGINT, &ss, NULL );

	for(i = 0; i < size; i++){
		s32temp = i;
		gacMsg[3] = '0' + s32temp / 1000;
		s32temp %= 1000;
		gacMsg[4] = '0' + s32temp / 100;
		s32temp %= 100;
		gacMsg[5] = '0' + s32temp / 10;
		s32temp %= 10;
		gacMsg[6] = '0' + s32temp;
		write(0, gacMsg, 9);
	}

	
	for(i = 0; i < size; i++){
		if( called[i] == 1 )
			printf("%d was possibly interrupted\n", i);
	}

	return 0;
}

