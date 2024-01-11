#include "assign2Headers.h"

pid_t answererPid;
pid_t guesserPid;
int shouldRun = 1;

void SIGALRM_Handler(int sigNum) {
	shouldRun = 0;
	kill(answererPid, TIME_OVER_SIGNAL);
	kill(guesserPid, TIME_OVER_SIGNAL);
}
void SIGCHLD_Handler(int sigNum) {
	int status;
	shouldRun = 0;
	while(wait(&status)>0) {
		sleep(1);
	}
}

int main() {
	struct sigaction act;
	memset(&act, '\0', sizeof(act));
	act.sa_handler = SIGALRM_Handler;
	sigaction(SIGALRM, &act, NULL);
	act.sa_handler= SIGCHLD_Handler;
	sigaction(SIGCHLD, &act, NULL);

	answererPid = fork();
	if(answererPid == 0) {
		execl(ANSWERER_PROGNAME, ANSWERER_PROGNAME, NULL);
	}
	else {
		guesserPid = fork();
		if(guesserPid == 0) {
			char line[LINE_LEN];
			snprintf(line,LINE_LEN,"%d",answererPid);
			execl(GUESSER_PROGNAME, GUESSER_PROGNAME, line, NULL);
		}
	}

	alarm(NUM_SECONDS);
	while  (shouldRun)
  		sleep(1);
	sleep(1);
	sleep(1);
	printf("launcher finished\n");
	return(EXIT_SUCCESS);

}