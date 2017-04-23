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

#define CYC_TIME 1000

int main(int argc, char *argv[])
{
	int    fd;
	struct sockaddr_un addr;
	char   buf[PACKET_SIZE];
	int    i, nloop;
    
	/* 引数の設定 */    
	if (argc != 2) {
		printf("usage:\n./swrite <NLOOP>\n");
		exit(-1);
	}
	nloop = atoi(argv[1]);

	/* ソケット作成 */
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(-1);
	}

	/* ソケット接続 */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = PF_UNIX;
    strcpy(addr.sun_path, SOCK_NAME);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0){
        perror("connect");
        exit(-1);
    }

	/* ソケット送信 */
	for (i=0; i<nloop; i++) {
		usleep(CYC_TIME);
        	
		LOGD("write...\n");
		memset(buf, i, sizeof(buf));
		if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
			perror("write");
		}
	}
	printf("write loop= %d\n", i/2);

	/* ソケット終了 */
	close(fd);
	
	return 0;
}
