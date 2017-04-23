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
    
	/* $B0z?t$N@_Dj(B */    
	if (argc != 2) {
		printf("usage:\n./swrite <NLOOP>\n");
		exit(-1);
	}
	nloop = atoi(argv[1]);

	/* $B%=%1%C%H:n@.(B */
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(-1);
	}

	/* $B%=%1%C%H@\B3(B */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = PF_UNIX;
    strcpy(addr.sun_path, SOCK_NAME);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0){
        perror("connect");
        exit(-1);
    }

	/* $B%=%1%C%HAw?.(B */
	for (i=0; i<nloop; i++) {
		usleep(CYC_TIME);
        	
		LOGD("write...\n");
		memset(buf, i, sizeof(buf));
		if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
			perror("write");
		}
	}
	printf("write loop= %d\n", i/2);

	/* $B%=%1%C%H=*N;(B */
	close(fd);
	
	return 0;
}
