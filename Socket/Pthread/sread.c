#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/ioctl.h>

#if 1
#define LOGD(fmt, ...) printf("[Reader]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define CONNECTION_SOCK_NAME "/tmp/connection_socket"
#define SOCK_NAME		     "/tmp/socket"

#define STATE_SOCKET_ON_CLOSE		0
#define STATE_SOCKET_ON_SOCKET		1
#define STATE_SOCKET_ON_BIND		2
#define STATE_SOCKET_ON_LISTEN		3
#define STATE_SOCKET_ON_CONNECT		4
#define STATE_SOCKET_ON_ACCEPT		5
#define STATE_SOCKET_ON_READ		6

#define PACKET_SIZE 1024

static int cfd;
static int fd1;
static int fd2;

static struct sockaddr_un saddr, caddr;


void cleanup_handler(void *arg) 
{
	if (cfd >= 0) {
		close(cfd);
	}
	if (fd1 >= 0) {
		close(fd1);
	}
	if (fd2 >= 0) {
		close(fd1);
	}
	unlink(SOCK_NAME);
}

int SOCKET(int state) {
	if (STATE_SOCKET_ON_CLOSE != state) {
		return state;
	}
	/* ソケット作成 */
	LOGD("create socket... \n");
	if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		close(fd1);
		return STATE_SOCKET_ON_CLOSE;
    }
	LOGD("create connection socket... \n");
	if ((cfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		close(fd1);
		close(cfd);
		return STATE_SOCKET_ON_CLOSE;
    }
	return STATE_SOCKET_ON_SOCKET;
}

int BIND(int state) {
	if (STATE_SOCKET_ON_SOCKET != state) {
		return state;
	}
	/* ソケットバインド */
	LOGD("bind socket... \n");
	unlink(SOCK_NAME);
	memset(&saddr, 0, sizeof(saddr));
    saddr.sun_family = PF_UNIX;
    strcpy(saddr.sun_path, SOCK_NAME);
	if (bind(fd1, (struct sockaddr *)&saddr, 
		sizeof(saddr.sun_family) + strlen(SOCK_NAME)) < 0){
    	perror("bind");
		close(fd1);
		close(cfd);
		return STATE_SOCKET_ON_CLOSE;
    }
	return STATE_SOCKET_ON_BIND;
}

int LISTEN(int state) {
	if (STATE_SOCKET_ON_BIND != state) {
		return state;
	}
	/* ソケットリッスン */
	LOGD("listen socket... \n");
    if (listen(fd1, 1) < 0)
	{
    	perror("listen");
		close(fd1);
		close(cfd);
		unlink(SOCK_NAME);
		return STATE_SOCKET_ON_CLOSE;
    }
	return STATE_SOCKET_ON_LISTEN;
}

int CONNECT(state) {
	if (STATE_SOCKET_ON_LISTEN != state) {
		return state;
	}
	LOGD("connect socket... \n");
    memset(&caddr, 0, sizeof(struct sockaddr_un));
    caddr.sun_family = PF_UNIX;
    strcpy(caddr.sun_path, CONNECTION_SOCK_NAME);
	if (connect(cfd, (struct sockaddr *)&caddr, sizeof(struct sockaddr_un)) < 0)
	{
 		perror("connect");
		return state;
	}
	else
	{
		return STATE_SOCKET_ON_CONNECT;
	}
}

int ACCEPT(state) {
	int len;

	if (STATE_SOCKET_ON_CONNECT != state) {
		return state;
	}
	/* クライアントの接続を待つ */
	LOGD("accept socket... \n");
    len = sizeof(saddr);
    if ((fd2 = accept(fd1, (struct sockaddr *)&saddr, (socklen_t *)&len)) < 0)	
	{
		perror("accept");
		return state;
	}
	else
	{
		close(fd1);
		return STATE_SOCKET_ON_ACCEPT;
	}
}

int READ(state) {
	char   buf[PACKET_SIZE];
	int    i,len,n;

	if (!((STATE_SOCKET_ON_ACCEPT == state) || (STATE_SOCKET_ON_READ == state))) {
		return state;
	}
	
	/* ソケット読み込み */
	LOGD("read socket... \n");
	n = read(fd2, buf, sizeof(buf));
    if (n > 0) 
	{
		LOGD("read (%d) \n",n);
#if 0
		printf("%d = read [", n);
		for(i = 0; i < n; i++) 
		{
			printf("%02x",buf[i]);
			if (n != (i+1)) {
				printf(" ");	
			}
		}
		printf("]\n");
#endif
		return STATE_SOCKET_ON_READ;
	} else if(n == 0) {
		return STATE_SOCKET_ON_BIND;
	} else {
		perror("read");
		exit(-1);
		return STATE_SOCKET_ON_READ;
	}
}


void *func_thread(void *p)
{
	int FLAG = 0;
	cfd = -1;
	fd1 = -1;
	fd2 = -1;

	pthread_cleanup_push(cleanup_handler, NULL);

	FLAG = SOCKET(FLAG);
	FLAG = BIND(FLAG);
	FLAG = LISTEN(FLAG);

	while(1) 
	{
		LOGD("Waiting... \n");
		FLAG = SOCKET(FLAG);
		FLAG = BIND(FLAG);
		FLAG = LISTEN(FLAG);
		FLAG = CONNECT(FLAG);
		FLAG = ACCEPT(FLAG);
		FLAG = READ(FLAG);
		sleep(1);
	}

	/* ソケット終了*/
	LOGD("close \n");
	pthread_cleanup_pop(0);
	
	return 0;

}

/* ReadClient */
int main(int argc, char *argv[])
{
	int a;
 	LOGD("start \n");

	pthread_t pthread;
	pthread_create( &pthread, NULL, &func_thread, NULL);

#if 0
	printf("input number:");
	scanf("%d",&a);
	printf("->%d \n",a);
	if(a==0) {
		pthread_cancel(pthread);
	}
#endif

 	pthread_join(pthread, NULL);
	LOGD("end \n");
	return 0;
}
