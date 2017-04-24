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

#if 1
#define LOGD(fmt, ...) printf("[Reader]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define SOCK_NAME "/tmp/test_socket"
#define PACKET_SIZE 1024

static int  fd1 = -1;
static int	fd2 = -1;

void cleanup_handler(void *arg) 
{
	if (fd1 >= 0) {
		close(fd1);
	}
	if (fd2 >= 0) {
		close(fd2);
	}
	unlink(SOCK_NAME);
}

int main(int argc, char *argv[])
{
	struct sockaddr_un caddr, saddr;
	int    len, val;
	char   buf[PACKET_SIZE];
	char   t[64];
	int	   FLAG=0;

	pthread_cleanup_push(cleanup_handler, NULL);

	/* ソケットの作成 */
	LOGD("SOCKET\n");
	if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
    } else {
		FLAG=1;
	}

	/* ソケットバインド */
	LOGD("BIND\n");
	if (FLAG) {
		unlink(SOCK_NAME);
		memset(&saddr, 0, sizeof(saddr));
    	saddr.sun_family = PF_UNIX;
    	strcpy(saddr.sun_path, SOCK_NAME);
		if (bind(fd1, (struct sockaddr *)&saddr,
			sizeof(saddr.sun_family) + strlen(SOCK_NAME)) < 0){
    	    perror("bind");
    	} else {
			FLAG=2;
		}
	}

	/* ソケットリッスン */
	LOGD("LISTEN\n");
	if (FLAG==2) {
		if (listen(fd1, 1) < 0){
		    perror("listen");
		} else {
			FLAG=3;
		}
	}

	if (FLAG==3) {
		while(1) {
    		/* クライアントの接続を待つ */
			if (FLAG==3) {
				LOGD("ACCEPT\n");
			    len = sizeof(caddr);
			    if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, 
					(socklen_t *)&len)) < 0){
			    	perror("accept");
				} else {
					FLAG=4;
				}
			}

			/* ソケット受信 */
    		while (1) {
				LOGD("READ\n");
    		    int n;
    		    n = read(fd2, buf, sizeof(buf));
    		    if (n > 0) {
    		       	LOGD("READ (%d)\n", n);
				} else if(n == 0) {
					FLAG=3;
					break;
		        } else {
    		       	perror("read");
				}
			}
		}
    }

	/* ソケット終了 */
	LOGD("CLOSE\n");
	close(fd1);
	close(fd2);
	unlink(SOCK_NAME);
	pthread_cleanup_pop(0);

    return 0;
}
