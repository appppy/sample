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
#define LOGD(fmt, ...) printf("[Sender]:" fmt, ## __VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

#define SOCK_NAME "/tmp/test_socket"
#define PACKET_SIZE 1024

static int  fd = -1;

void cleanup_handler(void *arg) 
{
	if (fd >= 0) {
		close(fd);
	}
}

int main(int argc, char *argv[])
{
	struct sockaddr_un addr;
	char   buf[PACKET_SIZE];
	int	   FLAG=0;
	int	   CON1ST=0;
	int	   val;

	pthread_cleanup_push(cleanup_handler, NULL);

	/* ソケット作成 */
	LOGD("SOCKET\n");
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
	} else {
		FLAG=1;
	}
	/* ソケット接続 */
	LOGD("CONNECT\n");
	if (FLAG) {
    	memset(&addr, 0, sizeof(struct sockaddr_un));
    	addr.sun_family = PF_UNIX;
    	strcpy(addr.sun_path, SOCK_NAME);
    	if (connect(fd, (struct sockaddr *)&addr, 
			sizeof(struct sockaddr_un)) < 0){
			if (!CON1ST) {
    			perror("connect");
			}
    	} else {
			CON1ST=1;
			FLAG=2;
		}
	}

	if (FLAG) {
    	while (1) {
			/* ソケット接続 */
			LOGD("CONNECT\n");
			if (FLAG==1) {
    			memset(&addr, 0, sizeof(struct sockaddr_un));
    			addr.sun_family = PF_UNIX;
    			strcpy(addr.sun_path, SOCK_NAME);
    			if (connect(fd, (struct sockaddr *)&addr, 
					sizeof(struct sockaddr_un)) < 0){
					if (!CON1ST) {
    					perror("connect");
					}
    			} else {
					CON1ST=1;
					FLAG=2;
				}
			}

			/* ソケット送信 */
			LOGD("WRITE\n");
			if (FLAG==2) {
				memset(buf, 0xFF, 10);
				if (write(fd, buf, 10) != 10) {
					perror("write");
				}
			}

			sleep(1);
		}
	}

	/* ソケット終了 */
	LOGD("CLOSE\n");
	close(fd);
	pthread_cleanup_pop(0);

	return 0;
}
