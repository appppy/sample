#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <errno.h>

//#define LOGD(...)
#define LOGD(...) printf(__VA_ARGS__)

#define SOCK_NAME "/tmp/test_socket"

#define PACKET_SIZE 1024

#define CYC_TIME 1000*1000

#define CYC_TIME2 1000

int main(int argc, char *argv[])
{
	int    fd1,fd2;
	struct sockaddr_un caddr, saddr;
	int    len, val;
	char   buf[PACKET_SIZE];

	char   t[64];

	/* ソケットの作成 */
	if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(-1);
    }

	unlink(SOCK_NAME);
	memset(&saddr, 0, sizeof(saddr));
    saddr.sun_family = PF_UNIX;
    strcpy(saddr.sun_path, SOCK_NAME);
    
	/* ソケットバインド */
	if (bind(fd1, (struct sockaddr *)&saddr, /
					sizeof(saddr.sun_family) + strlen(SOCK_NAME)) < 0){
        perror("bind");
        exit(-1);
    }

	/* ソケットリッスン */
    if (listen(fd1, 1) < 0){
        perror("listen");
        exit(-1);
    }

    while (1) {
		usleep(CYC_TIME);

        // クライアントの接続を待つ
    	len = sizeof(caddr);
    	if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, (socklen_t *)&len)) < 0){
    		perror("accept");
   		    exit(-1);
		}

		/* ソケット受信 */
        int n;
		while (1) {
			usleep(CYC_TIME2);
        	n = read(fd2, buf, sizeof(buf));
        	if (n > 0 ) {
            	LOGD("%d = read [%02x %02x %02x %02x %02x]\n", n, buf[0], buf[1], buf[2], buf[3], buf[4]);
			} else if(n == 0) {
				break;
        	} else {
            	perror("read");
            	exit(-1);
			}
		}

        // ソケットのクローズ
        if (close(fd2) == -1)
        {
           perror("close");
           exit(-1);
        }
    }
	printf("close \n");

	/* ソケット終了 */
	close(fd1);
    close(fd2);

    return 0;
}
