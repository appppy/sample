#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <signal.h>

#if 1
#define LOGD(fmt, ...) printf("[Sender]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define SOCK_NAME	"/tmp/test_socket"
#define PACKET_SIZE 1024

typedef enum SOCKET_RESULT
{ 
	eSOCKET_RESULT_SUCCESS = 0,
	eSOCKET_RESULT_ERROR,
	eSOCKET_RESULT_CONNECT_ERROR,
} 	eSOCKET_RESULT;

static	pthread_t pthread;
static	int  	  fd = -1;

void cleanup_handler(void *arg) 
{
	LOGD("CLEAN\n");
	if (fd >= 0) {
		close(fd);
	}
}

void *func_thread(void *p)
{
	struct sockaddr_un 	addr;
	char   				buf[PACKET_SIZE];
	eSOCKET_RESULT		result=eSOCKET_RESULT_SUCCESS;

	signal(SIGPIPE, SIG_IGN);
	pthread_cleanup_push(cleanup_handler, NULL);

	/* ソケット作成 */
	LOGD("SOCKET\n");
	/* ソケット接続 */
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		result=eSOCKET_RESULT_ERROR;
	}


	if (eSOCKET_RESULT_SUCCESS == result) {
		LOGD("CONNECT\n");
    	memset(&addr, 0, sizeof(struct sockaddr_un));
    	addr.sun_family = PF_UNIX;
    	strcpy(addr.sun_path, SOCK_NAME);
    	if (connect(fd, (struct sockaddr *)&addr, 
			sizeof(struct sockaddr_un)) < 0){
			perror("connect");
			result=eSOCKET_RESULT_CONNECT_ERROR;
    	}
	}

    while ( result == eSOCKET_RESULT_SUCCESS || 
			result == eSOCKET_RESULT_CONNECT_ERROR) {

		/* ソケット接続 */
		if (eSOCKET_RESULT_CONNECT_ERROR == result) {
			LOGD("CONNECT\n");
    		memset(&addr, 0, sizeof(struct sockaddr_un));
    		addr.sun_family = PF_UNIX;
    		strcpy(addr.sun_path, SOCK_NAME);
    		if (connect(fd, (struct sockaddr *)&addr, 
				sizeof(struct sockaddr_un)) < 0){
				perror("connect");
				result=eSOCKET_RESULT_CONNECT_ERROR;
    		} else {
				result=eSOCKET_RESULT_SUCCESS;
			}
		}

		/* ソケット送信 */
		if (eSOCKET_RESULT_SUCCESS == result) {
			LOGD("WRITE\n");
			memset(buf, 0xFF, PACKET_SIZE);
			int n = write(fd, buf, PACKET_SIZE);
			if (n == PACKET_SIZE) {
				LOGD("WRITE (%d)\n", n);
			} else {
				perror("write");
				if (errno==EPIPE) {
#if 1
					close(fd);
					/* ソケット再作成 */
					LOGD("SOCKET\n");
					/* ソケット接続 */
					if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
						result == eSOCKET_RESULT_ERROR;
						perror("socket");
						break;
					}
#endif
					result=eSOCKET_RESULT_CONNECT_ERROR;
				}
			}
		}

		sleep(1);
	}

	/* ソケット終了 */
	LOGD("CLOSE\n");
	if (fd >= 0) {
		close(fd);
	}
	pthread_cleanup_pop(0);

	return 0;
}

void sig_catch(int sig) {
	LOGD("SIGNAL(%d)\n",sig);
	pthread_cancel(pthread);
}

int main(int argc, char *argv[])
{
	int a;

 	LOGD("START \n");

	if (SIG_ERR == signal(SIGHUP, sig_catch)) {
		LOGD("NotSupported signal(SIGHUP, void) \n");
	}
	if (SIG_ERR == signal(SIGINT, sig_catch)) {
	 	LOGD("NotSupported signal(SIGINT, void) \n");
	}
	if (SIG_ERR == signal(SIGKILL, sig_catch)) {
	 	LOGD("NotSupported signal(SIGKILL, void) \n");
	}
	if (SIG_ERR == signal(SIGTERM, sig_catch)) {
	 	LOGD("NotSupported signal(SIGTERM, void) \n");
	}
	if (SIG_ERR == signal(SIGTSTP, sig_catch)) {
	 	LOGD("NotSupported signal(SIGTSTP, void) \n");
	}

	pthread_create( &pthread, NULL, &func_thread, NULL);

 	pthread_join(pthread, NULL);

	LOGD("STOP \n");
	return 0;
}
