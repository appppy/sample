#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/ioctl.h>


#if 1
#define LOGD(fmt, ...) printf("[Sender]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define WRITE_SOCK_NAME	"/tmp/socket"
#define READ_SOCK_NAME	"/tmp/connection_socket"

#define PACKET_SIZE 1024

enum STATE
{
	ON_CLOSE,
	ON_SOCKET,
	ON_BIND,
	ON_LISTEN,
	ON_SELECT,
	ON_CONNECT,
	ON_WRITE
};

static int write_fd;
static int listen_fd;

void cleanup_handler(void *arg) 
{
	if (write_fd >= 0) {
		close(write_fd);
	}
	if (listen_fd >= 0) {
		close(listen_fd);
	}
	unlink(READ_SOCK_NAME);
}

void signal_handler(int sig) 
{
	LOGD("SIGNAL... (%d)\n",sig);
	if (write_fd >= 0) {
		close(write_fd);
	}
	if (listen_fd >= 0) {
		close(listen_fd);
	}
	unlink(READ_SOCK_NAME);
	exit(1);
}

int SOCKET(int state) {
	if (ON_CLOSE != state) {
		return state;
	}
	LOGD("SOCKET... \n");
	if ((write_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		close(write_fd);
		return ON_CLOSE;
    }
	if ((listen_fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		close(write_fd);
		close(listen_fd);
		return ON_CLOSE;
    }
	return ON_SOCKET;
}

int BIND(int state, struct sockaddr_un addr) {
	if (ON_SOCKET != state) {
		return state;
	}
	LOGD("BIND... \n");
	unlink(READ_SOCK_NAME);
	memset(&addr, 0, sizeof(addr));
    addr.sun_family = PF_UNIX;
    strcpy(addr.sun_path, READ_SOCK_NAME);
	if (bind(listen_fd, (struct sockaddr *)&addr, 
		sizeof(addr.sun_family) + strlen(READ_SOCK_NAME)) < 0){
    	perror("bind");
		close(write_fd);
		close(listen_fd);
		return ON_CLOSE;
    }
	return ON_BIND;
}

int LISTEN(int state) {
	if (ON_BIND != state) {
		return state;
	}
	LOGD("LISTEN... \n");
    if (listen(listen_fd, 1) < 0)
	{
    	perror("listen");
		close(write_fd);
		close(listen_fd);
		unlink(READ_SOCK_NAME);
		return ON_CLOSE;
    }
	return ON_LISTEN;
}

int SELECT(int state, struct timeval timeout) {
	int ret;
	fd_set fds;

	if (ON_LISTEN != state) {
		return state;
	}
	LOGD("SELECT...\n");
	FD_ZERO( &fds );
	FD_SET( listen_fd , &fds );
	ret = select(listen_fd+1 , &fds , NULL , NULL , &timeout );
	if(ret && FD_ISSET(listen_fd, &fds))
	{
		return ON_SELECT;
	}
	else 
	{
		//perror("select");
		return state;
	}
}

int CONNECT(int state, struct sockaddr_un addr) {
	if (ON_SELECT != state) {
		return state;
	}
	LOGD("CONNECT... \n");
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = PF_UNIX;
    strcpy(addr.sun_path, WRITE_SOCK_NAME);
	if (connect(write_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0)
	{
 		perror("connect");
		return state;
	}
	else
	{
		return ON_CONNECT;
	}
}

int WRITE(int state) {
	char   buf[PACKET_SIZE];

	if (!((ON_CONNECT == state) || (ON_WRITE == state))) {
		return state;
	}
	
	LOGD("WRITE...\n");
	memset(buf, 10, 10);
	if (write(write_fd, buf, 10) != 10) 
	{
		perror("write");
		return ON_BIND;
	}
	else
	{
		return state;
	}
}

void *func_thread(void *p)
{
	int 	FLAG = 0;
	struct	sockaddr_un saddr, caddr;
	struct  timeval timeout;

	write_fd        = -1;
	listen_fd       = -1;
	timeout.tv_sec  = 0;
	timeout.tv_usec = 0;

	if (SIG_ERR == signal(SIGHUP, signal_handler))
	{
		LOGD("ERROR SIGHUP \n");
	}
	if (SIG_ERR == signal(SIGINT, signal_handler))
	{
		LOGD("ERROR SIGINT \n");
	}
	if (SIG_ERR == signal(SIGKILL, signal_handler))
	{
		LOGD("ERROR SIGKILL \n");
	}
	if (SIG_ERR == signal(SIGALRM, signal_handler))
	{
		LOGD("ERROR SIGALRM \n");
	}
	if (SIG_ERR == signal(SIGTERM, signal_handler))
	{
		LOGD("ERROR SIGTERM \n");
	}

	pthread_cleanup_push(cleanup_handler, NULL);

	FLAG = SOCKET(FLAG);
	FLAG = BIND(FLAG, caddr);
	FLAG = LISTEN(FLAG);

	while(1) 
	{
		LOGD("Waiting... (%d) \n", FLAG);
		FLAG = SOCKET(FLAG);
		FLAG = BIND(FLAG, saddr);
		FLAG = LISTEN(FLAG);
		FLAG = SELECT(FLAG, timeout);
		FLAG = CONNECT(FLAG, saddr);
		FLAG = WRITE(FLAG);
		sleep(1);
	}

	/* ソケット終了 */
	LOGD("close \n");
	pthread_cleanup_pop(0);
    return 0;
}

int main(int argc, char *argv[])
{
	int a;
 	LOGD("start \n");

	pthread_t pthread;
	pthread_create( &pthread, NULL, &func_thread, NULL);

 	pthread_join(pthread, NULL);
	LOGD("end \n");
	return 0;
}

