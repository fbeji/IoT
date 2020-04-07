/***************************************************************************
	Sample daemon process
	gcc sample_daemon.c -o sampled

Author: Chris Lamb
Edits: Faycel Beji

Description: Simulates a simple daemon process that handles the SIGHUP and
	SIGTERM signals.

To see syslog: cat /var/log/syslog
***************************************************************************/

#include <stdio.h>
#include <syslog.h> //For syslog()
#include <signal.h> //For SIGHUP, SIGTERM
#include <stdbool.h> //For true
#include <unistd.h> //For sleep()
#include <errno.h> //For errno
#include <string.h> //For strerror()
#include <sys/stat.h> //For S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH
#include <stdlib.h>

#define OK 0
#define ERR_FORK 1
#define ERR_SETSID 2
#define ERR_CHDIR 3
#define ERR_WTF 4

#define DAEMON_NAME "sampled"

//Input: Signal (SIGHUP, SIGTERM, SIGKILL, etc)
//Output: Does nothing for SIGHUP, logs signal and exits program for
//	SIGTERM for all other signals, it logs it as an unhandled signal.
//	Returns nothing.
static void _signal_handler(const int signal) {
	switch(signal) {
		case SIGHUP:
			break;
		case SIGTERM:
			syslog(LOG_INFO, "Received SIGTERM,\
			exiting program.\n");

			closelog();
			exit(OK);
			break;
		default:
			syslog(LOG_INFO, "Received unhandled signal.\n");
	}
}

//Input: None
//Output: Counts and sleeps, returns nothing.
static void _do_work() {
	int i;
	for(i=0; true; i++) {
		syslog(LOG_INFO, "Iteration: %d.\n", i);
		sleep(1);
	}
}

int main(void) {
	//Opening syslog
	openlog(DAEMON_NAME, LOG_PID | LOG_NDELAY | LOG_NOWAIT, LOG_DAEMON);
	syslog(LOG_INFO, "Starting sampled\n");
	
	//Creating child process
	pid_t pid = fork();
	printf("Child process is made\n");

	if(pid < 0) {
		syslog(LOG_ERR, "Help: %s\n", strerror(errno));
		return ERR_FORK;
	}

	//Getting rid of parent process
	if(pid > 0) {
		return OK;
	}
	
	//Creating session id
	if(setsid() < -1) {
		syslog(LOG_ERR, "Help: %s\n", strerror(errno));
		return ERR_SETSID;
	}
	printf("Session ID was made\n");

	//Closing file descriptors
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	printf("Closed file descriptors");

	//Set umask
	umask(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	//Setting up working directory
	if(chdir("/") < 0) {
		syslog(LOG_ERR, "Help: %s\n", strerror(errno));
		return ERR_CHDIR;
	}

	//Setting signal handler [_signal_handler is a custom fn]
	signal(SIGTERM, _signal_handler);
	signal(SIGHUP, _signal_handler);

	//Time to do work [_do_work is a custom fn]
	_do_work();

	return ERR_WTF;
}

