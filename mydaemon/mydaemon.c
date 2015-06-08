#include <syslog.h>
#include <signal.h>
#include <sys/wait.h>

static volatile int sigterm = 0;
static volatile int sigint = 0;
static volatile int sighup = 0;

static void handle_sigint(int sig)
{
    dlog(LOG_INFO, "SIGINT received.\n");
    sigint = 1;
}
static void handle_sigterm(int sig)
{
    dlog(LOG_INFO, "SIGTERM received.\n");
    sigterm = 1;
}
static void handle_sighup(int sig)
{
    dlog(LOG_INFO, "SIGHUP received.\n");
    sighup = 1;
}

int daemon_main(int argc, char* argv[], char* envp[])
{
    dlog(LOG_INFO, "mydaemon started.\n");
    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        dlog(LOG_ERR, "fail to setup SIGINT.\n");
        return 2;
    } else
    if (signal(SIGTERM, handle_sigterm) == SIG_ERR) {
        dlog(LOG_ERR, "fail to setup SIGTERM.\n");
        return 2;
    } else if (signal(SIGHUP, handle_sighup) == SIG_ERR) {
        dlog(LOG_ERR, "fail to ignore SIGHUP.\n");
        return 2;
    }

	while(!sigterm && !sigint) {
        /**
         * some job
         */
		usleep(1000000);
	}

    dlog(LOG_INFO, "mydaemon stopped.\n");
	return 0;
}

