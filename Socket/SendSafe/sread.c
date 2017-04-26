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
#define LOGD(fmt, ...) printf("[Reader]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define SOCK_NAME 	"/tmp/test_socket"
#define PACKET_SIZE 1024

typedef enum SOCKET_RESULT
{ 
	eSOCKET_RESULT_SUCCESS = 0,
	eSOCKET_RESULT_ERROR,
	eSOCKET_RESULT_CONNECT_ERROR,
} 	eSOCKET_RESULT;

static pthread_t pthread;
static int  	 fd1 = -1;
static int		 fd2 = -1;

void cleanup_handler(void *arg) 
{
	LOGD("CLEAN\n");
	if (fd1 >= 0) {
		close(fd1);
	}
	if (fd2 >= 0) {
		close(fd2);
	}
	unlink(SOCK_NAME);
}

void *func_thread(void *p)
{
	struct sockaddr_un 	caddr, saddr;
	int    				len, val;
	char   				buf[PACKET_SIZE];
	eSOCKET_RESULT		result=eSOCKET_RESULT_SUCCESS;

	pthread_cleanup_push(cleanup_handler, NULL);

	/* ソケットの作成 */
	LOGD("SOCKET\n");
	if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		result=eSOCKET_RESULT_ERROR;
	}

	/* ソケットバインド */
	if (eSOCKET_RESULT_SUCCESS == result) {
		LOGD("BIND\n");
		unlink(SOCK_NAME);
		memset(&saddr, 0, sizeof(saddr));
    	saddr.sun_family = PF_UNIX;
    	strcpy(saddr.sun_path, SOCK_NAME);
		if (bind(fd1, (struct sockaddr *)&saddr,
			sizeof(saddr.sun_family) + strlen(SOCK_NAME)) < 0){
    	    perror("bind");
			result=eSOCKET_RESULT_ERROR;
    	}
	}

	/* ソケットリッスン */
	if (eSOCKET_RESULT_SUCCESS == result) {
		LOGD("LISTEN\n");
		if (listen(fd1, 1) < 0){
		    perror("listen");
			result=eSOCKET_RESULT_ERROR;
		}
	}

	/* クライアントの接続を待つ */
	if (eSOCKET_RESULT_SUCCESS == result) {
		LOGD("ACCEPT\n");
		len = sizeof(caddr);
		if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, 
			(socklen_t *)&len)) < 0){
		    perror("accept");
			result=eSOCKET_RESULT_ERROR;
		}
	}

	while(result==eSOCKET_RESULT_SUCCESS) {
		/* ソケット待機失敗時 */
		if (eSOCKET_RESULT_SUCCESS != result) {
			break;
		}

		/* ソケット受信 */
		LOGD("READ\n");
    	int n;
    	n = read(fd2, buf, sizeof(buf));
    	if (n > 0) {
    	    LOGD("READ (%d)\n", n);
		} else if(n == 0) {
			LOGD("ACCEPT\n");
			len = sizeof(caddr);
			if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, 
				(socklen_t *)&len)) < 0){
			    perror("accept");
				result=eSOCKET_RESULT_ERROR;
			}
		} else {
    	    perror("read");
		}
    }

	/* ソケット終了 */
	LOGD("CLOSE\n");
	if (fd1 >= 0) {
		close(fd1);
	}
	if (fd2 >= 0) {
		close(fd2);
	}
	unlink(SOCK_NAME);
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

