#include "assign2Headers.h"
int shouldRun = 1;
int answererPid;
const int buf_len = 8;

void TIME_OVER_SIGNAL_Handler(int sigNum) {
	shouldRun = 0;
	printf("You were too slow.\n");
}

void WIN_SIGNAL_Handler(int sigNum) {
	shouldRun = 0;
	printf("Victory achieved.\n");
}

void CORRECTNESS_Handler(int sigNum) {
	if(sigNum == INCORRECT_SIGNAL) {
		printf("Nope, back from the top.\n");
	}
	else if(sigNum == CORRECT_SIGNAL) {
		printf("Lucky guess.\n");
	}
}

int main(int argc, char* argv[]) {
	char buf[buf_len];
	int guess;
	struct sigaction act;

	if(argc <= 1)
		return(EXIT_FAILURE);
	answererPid = atoi(argv[1]);

	memset(&act, '\0', sizeof(act));
	act.sa_handler = TIME_OVER_SIGNAL_Handler;
	sigaction(TIME_OVER_SIGNAL, &act, NULL);
	act.sa_handler = WIN_SIGNAL_Handler;
	sigaction(WIN_SIGNAL, &act, NULL);
	act.sa_handler = CORRECTNESS_Handler;
	sigaction(CORRECT_SIGNAL, &act, NULL);
	sigaction(INCORRECT_SIGNAL, &act, NULL);

	while(shouldRun) {
		printf("Is it 0 or 1?: ");
		fgets(buf, buf_len, stdin);

		guess = atoi(buf);
		if(guess == 0) {
			kill(answererPid, ZERO_SIGNAL);
		}
		else if(guess == 1) {
			kill(answererPid, ONE_SIGNAL);
		}
		else {
			printf("Invalid input.\n");
		}
		sleep(1);
	}
	printf("guesser finished\n");
	return(EXIT_SUCCESS);
}

