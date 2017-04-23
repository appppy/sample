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

int main(int argc, char *argv[])
{
	int    fd;
	struct sockaddr_un addr;
	char   buf[PACKET_SIZE];
	int    i, nloop, cyctime;
    
	/* 引数の設定 */    
	if (argc != 3) 
	{
		printf("usage:\n./swrite <NLOOP> <CYCTIME> \n");
		exit(-1);
	}
	nloop = atoi(argv[1]);
	cyctime = atoi(argv[2]);
	
	LOGD("[C] nloop   = %d\n",nloop);
	LOGD("[C] cyctime = %d \n",cyctime);

	/* ソケット作成 */
	LOGD("[C] create socket... \n");
	if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
	}
	else
	{
		while(1) 
		{
			usleep(cyctime);

			/* ソケット接続 */
    		memset(&addr, 0, sizeof(struct sockaddr_un));
    		addr.sun_family = PF_UNIX;
    		strcpy(addr.sun_path, SOCK_NAME);
			if (connect(fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un)) < 0)
			{
    		    perror("connect");
			}
			else
			{
				/* ソケット送信 */
				for (i=0; i<nloop; i++) 
				{
					usleep(cyctime);
				
					/* ソケット送信 */
					LOGD("[C] write socket...\n");
					memset(buf, i, i);
					if (write(fd, buf, i) != sizeof(buf)) 
					{
						perror("write");
					}
				}
				break;
			}
		}
		/* ソケット終了*/
		LOGD("[C] close \n");
		close(fd);
	}
	
	return 0;
}

