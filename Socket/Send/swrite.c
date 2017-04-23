#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <errno.h>

//#define DPRINTF(...)
#define DPRINTF(...) printf(__VA_ARGS__)

#define SOCK_NAME "/tmp/test_socket"

int main(int argc, char *argv[])
{
        int    fd;
        struct sockaddr_un    addr;
        int    len, val;
        fd_set rfds, wfds;
        char   buf[128];
        int    i, nloop;
        int    read_start;

        if (argc != 2) {
                printf("usage:\n./swrite <NLOOP>\n");
                exit(-1);
        }
        nloop = atoi(argv[1]);

        if ((fd = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
                perror("socket");
                exit(-1);
        }

        memset((char *)&addr, 0, sizeof(addr));
        addr.sun_family = AF_UNIX;
        strcpy(addr.sun_path, SOCK_NAME);

        /* set non-blocking */
        val = 1;
        ioctl(fd, FIONBIO, &val);

        if (connect(fd, (struct sockaddr *)&addr,
                                sizeof(addr.sun_family) + strlen(SOCK_NAME)) < 0){
                perror("connect");
                exit(1);
        }

        read_start=0;
        for (i=0; i<nloop; i++) {
                if (read_start) {
                        buf[0] = '\0';

                        FD_ZERO(&rfds);
                        FD_SET(fd, &rfds);

                        DPRINTF("selecting read...\n");
                        if (select(fd+1, &rfds, NULL, NULL, NULL) == -1) {
                                perror("select");
                        }

                        if (FD_ISSET(fd, &rfds)) {
                                int n;
                                n = read(fd, buf, sizeof(buf));
                                if (n > 0 ) {
                                        DPRINTF("%d = read [%s]\n", n, buf);
                                } else {
                                        perror("read");
                                        exit(-1);
                                }
                        }
                        read_start = 0;
                } else {
                        memset(buf, 'w', sizeof(buf));
                        buf[sizeof(buf)-1] = '\0';

                        FD_ZERO(&wfds);
                        FD_SET(fd, &wfds);
                        DPRINTF("selecting write...\n");
                        if (select(fd+1, NULL, &wfds, NULL, NULL) == -1) {
                                perror("select");
                                exit(-1);
                        }

                        if (FD_ISSET(fd, &wfds)) {
                                if (write(fd, buf, sizeof(buf)) != sizeof(buf)) {
                                        perror("write");
                                        exit(-1);
                                }
                        }
                        read_start = 1;
//                      sleep(1);
                }
        }
        printf("write loop= %d\n", i/2);
        close(fd);

        return 0;
}
