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
#define LOGD(fmt, ...) printf("[Sender]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define CONNECTION_SOCK_NAME "/tmp/connection_socket"
#define SOCK_NAME		     "/tmp/socket"

#define PACKET_SIZE 1024

static int nloop;

static int cfd;
static int fd;

void cleanup_handler(void *arg) 
{
	if (cfd >= 0) {
		close(cfd);
	}
	if (fd >= 0) {
		close(fd);
	}
	unlink(CONNECTION_SOCK_NAME);
}

void *func_thread(void *p)
{
	struct	sockaddr_un saddr, caddr;
	int		i,len, val;
	char	buf[PACKET_SIZE];
	fd_set	cfds,fds;
	struct  timeval timeout;
	int		FLAG = 0;
	int 	re;

	cfd = -1;
	fd  = -1;

	pthread_cleanup_push(cleanup_handler, NULL);

	/* ソケットの作成 */
	LOGD("create connection socket... \n");
	if ((cfd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		exit(-1);
    }
	LOGD("create socket... \n");
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		exit(-1);
    }

	/* ソケットバインド */
	LOGD("bind connection socket... \n");
	unlink(CONNECTION_SOCK_NAME);
	memset(&caddr, 0, sizeof(caddr));
    caddr.sun_family = PF_UNIX;
    strcpy(caddr.sun_path, CONNECTION_SOCK_NAME);
	if (bind(cfd, (struct sockaddr *)&caddr, 
		sizeof(caddr.sun_family) + strlen(CONNECTION_SOCK_NAME)) < 0){
    	perror("bind");
    	close(cfd);
		exit(-1);
    }

	/* ソケットリッスン */
	LOGD("listen connection socket... \n");
    if (listen(cfd, 1) < 0)
	{
    	perror("listen");
		close(cfd);
		exit(-1);
    }

	for (i=0; i<nloop; i++) 
	{
		LOGD("Waiting...(%d) \n",i);
		
		if(FLAG)
		{
			FD_ZERO( &fds );
			FD_SET( fd , &fds );
			timeout.tv_sec =  0;
			timeout.tv_usec = 0; 
			re = select(fd+1 , NULL, &fds, NULL , NULL );
			if(re) {
				if (FD_ISSET(fd, &fds)) {
					/* ソケット送信 */
					LOGD("write socket...\n");
					memset(buf, i, i);
					if (write(fd, buf, i) != sizeof(buf)) 
					{
						perror("write");
					}
				}
			}
		}
		else 
		{
			LOGD("Waiting for connection ...\n");

			FD_ZERO( &cfds );
			FD_SET( cfd , &cfds );

			timeout.tv_sec =  0;
			timeout.tv_usec = 0; 

			re = select(cfd+1 , &cfds , NULL , NULL , &timeout );
			if(re) {
				if (FD_ISSET(cfd, &cfds)) {
					LOGD("connect sock ...\n");
					/* ソケット接続 */
    				memset(&saddr, 0, sizeof(struct sockaddr_un));
    				saddr.sun_family = PF_UNIX;
    				strcpy(saddr.sun_path, SOCK_NAME);
					if (connect(fd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_un)) < 0)
					{
 						perror("connect");
						exit(-1);
					}
					FLAG = 1;
				}
			}
		}

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

	/* 引数の設定 */    
	if (argc != 2) 
	{
		printf("usage:\n./swrite <NLOOP> \n");
		exit(-1);
	}
	nloop = atoi(argv[1]);
	LOGD("nloop   = %d\n",nloop);

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

