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
	int    fd1,fd2;
	struct sockaddr_un caddr, saddr;
	int    i,len, val;
	char   buf[PACKET_SIZE];

	fd_set rfds;

	/* ソケットの作成 */
	LOGD("[S] create listen socket... \n");
	if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) 
	{
		perror("socket");
    }
	else
	{
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
    	}
		else
		{
			/* ソケットリッスン */
			LOGD("[S] listen socket... \n");
    		if (listen(fd1, 1) < 0)
			{
    		    perror("listen");
				close(fd1);
    		}
			else
			{
				while(1) {
					close(fd2);
    				/* クライアントの接続を待つ */
					LOGD("[S] accept listen socket... \n");
    				len = sizeof(caddr);
    				if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, (socklen_t *)&len)) < 0)
					{
						perror("accept");
   						exit(-1);
					}

					/* set non-blockig */
					//val = 1;
					//ioctl(fd2, FIONBIO, &val);

    				while (1) 
					{
		
						//FD_ZERO(&rfds);
						//FD_SET(fd2, &rfds);
	
						//LOGD("[S] selecting read...\n");
						//if (select(fd2+1, &rfds, NULL, NULL, NULL) == -1) 
						//{
						//	perror("select");
						//}
	
						//if (FD_ISSET(fd2, &rfds)) 
						//{
							/* ソケット受信 */
	    	    			int n;
							LOGD("[S] read socket... \n");
    		    			n = read(fd2, buf, sizeof(buf));
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
						//}
					}
    			}
			
				LOGD("[S] close read socket... \n");
				/* ソケット終了 */
				close(fd1);
				close(fd2);
			}
		}
	}
    return 0;
}
