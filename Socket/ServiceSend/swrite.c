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

/* WriteServer */
int main(int argc, char *argv[])
{
	int		fd1,fd2;
	struct	sockaddr_un caddr, saddr;
	int		i,len, val;
	char	buf[PACKET_SIZE];
	fd_set	rfds,wfds;
	struct  timeval timeout;
	int		FLAG = 0;
	int 	re;
	int		nloop;

	/* 引数の設定 */    
	if (argc != 2) 
	{
		printf("usage:\n./swrite <NLOOP> \n");
		exit(-1);
	}
	nloop = atoi(argv[1]);
	LOGD("[C] nloop   = %d\n",nloop);

	/* ソケットの作成 */
	LOGD("[S] create listen socket... \n");
	if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
		exit(-1);
    }

	unlink(SOCK_NAME);
	memset(&saddr, 0, sizeof(saddr));
    saddr.sun_family = PF_UNIX;
    strcpy(saddr.sun_path, SOCK_NAME);
	/* ソケットバインド */
	LOGD("[S] bind listen socket... \n");
	if (bind(fd1, (struct sockaddr *)&saddr, 
					sizeof(saddr.sun_family) + strlen(SOCK_NAME)) < 0){
    	perror("bind");
    	close(fd1);
		exit(-1);
    }

	/* ソケットリッスン */
	LOGD("[S] listen socket... \n");
    if (listen(fd1, 1) < 0)
	{
    	perror("listen");
		close(fd1);
		exit(-1);
    }

	for (i=0; i<nloop; i++) 
	{
		LOGD("[S] select socket...\n");
		if(FLAG)
		{

			FD_ZERO( &wfds );
			FD_SET( fd2 , &wfds );

			//timeout.tv_sec =  0;
			//timeout.tv_usec = 0; 

			re = select(fd2+1 , NULL, &wfds, NULL , NULL );
			if(re) {
				if (FD_ISSET(fd2, &wfds)) {
					/* ソケット送信 */
					LOGD("[S] write socket...\n");
					memset(buf, i, i);
					if (write(fd2, buf, i) != sizeof(buf)) 
					{
						perror("write");
					}
				}
			}
		}
		else 
		{

			printf("Waiting for connection ...\n");

			FD_ZERO( &rfds );
			FD_SET( fd1 , &rfds );

			timeout.tv_sec =  0;
			timeout.tv_usec = 0; 

			re = select(fd1+1 , &rfds , NULL , NULL , &timeout );
			if(re) {
				if (FD_ISSET(fd1, &rfds)) {
					/* クライアントの接続を待つ */
					LOGD("[S] accept listen socket... \n");
    				len = sizeof(caddr);
    				if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, (socklen_t *)&len)) < 0)	
					{
						perror("accept");
   						exit(-1);
					}
					else
					{
						close(fd1);
						FLAG = 1;
					}
			        /* set non-blocking */
        			//val = 1;
        			//ioctl(fd2, FIONBIO, &val);

				} else {
					LOGD("[S] select socket...\n");
				}
			}
		}

		sleep(1);
	}

	/* ソケット終了 */
	LOGD("[S] close \n");
	shutdown(fd2,2);
	close(fd2);
	unlink(SOCK_NAME);
    return 0;
}

