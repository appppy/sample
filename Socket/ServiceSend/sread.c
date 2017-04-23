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

/* ReadClient */
int main(int argc, char *argv[])
{

	int    fd;
	struct sockaddr_un addr;
	char   buf[PACKET_SIZE];
	int    i;
	int	   val;
    fd_set rfds,wfds;

	/* ソケット作成 */
	LOGD("[C] create socket... \n");
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		exit(-1);
	}

//	FD_ZERO( &rfds );
//	FD_SET( fd, &rfds );

	select(fd+1 , &rfds, NULL, NULL , NULL );
	if (FD_ISSET(fd, &rfds)) {

	/* ソケット接続 */
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = PF_UNIX;
    strcpy(addr.sun_path, SOCK_NAME);
	if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0)
	{
 //       perror("connect");
//		exit(-1);
	}

	}

	while(1) 
	{
		/* ソケット読み込み */
	    int n;
		LOGD("[C] read socket... \n");
		n = read(fd, buf, sizeof(buf));
    	if (n > 0) 
		{
			LOGD("%d = read [", n);
			for(i = 0; i < n; i++) 
			{
				LOGD("%02x",buf[i]);
				if (n != (i+1)) 
				{
					LOGD(" ");	
				}
			}
			LOGD("]\n");
		} else if(n == 0) {
   		   	break;
		} else {
    	   	perror("read");
    	   	exit(-1);
		}
		if(buf[0] == 0xFF) {
			break;
		}
	}

	/* ソケット終了*/
	LOGD("[C] close \n");
	close(fd);
	
	return 0;
}
