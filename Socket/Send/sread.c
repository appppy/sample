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
        int    fd1, fd2;
        struct sockaddr_un    saddr;
        struct sockaddr_un    caddr;
        int    len, val;
        fd_set rfds, wfds;
        char buf[128];
        int read_start;


        if ((fd1 = socket(PF_UNIX, SOCK_STREAM, 0)) < 0) {
                perror("socket");
                exit(-1);
        }

        memset((char *)&saddr, 0, sizeof(saddr));
        saddr.sun_family = AF_UNIX;
        strcpy(saddr.sun_path, SOCK_NAME);

        unlink(SOCK_NAME);
        if (bind(fd1, (struct sockaddr *)&saddr,
                         sizeof(saddr.sun_family) + strlen(SOCK_NAME)) < 0){
                perror("bind");
                exit(-1);
        }

        if (listen(fd1, 1) < 0) {
                perror("listen");
                exit(-1);
        }

        len = sizeof(caddr);
        if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, (socklen_t *)&len)) < 0) {
                perror("accept");
                exit(-1);
        }
        close(fd1);

        /* set non-blocking */
        val = 1;
        ioctl(fd2, FIONBIO, &val);

        read_start=1;
        while (1) {
                if (read_start) {
                        buf[0] = '\0';

                        FD_ZERO(&rfds);
                        FD_SET(fd2, &rfds);

                        DPRINTF("selecting read...\n");
                        if (select(fd2+1, &rfds, NULL, NULL, NULL) == -1) {
                                perror("select");
                        }

                        if (FD_ISSET(fd2, &rfds)) {
                                int n;
                                n = read(fd2, buf, sizeof(buf));
                                if (n > 0 ) {
                                        DPRINTF("%d = read [%s]\n", n, buf);
                                } else {
                                        perror("read");
                                        exit(-1);
                                }
                        }
                        read_start = 0;
                } else {
                        memset(buf, 'r', sizeof(buf));
                        buf[sizeof(buf)-1] = '\0';

                        FD_ZERO(&wfds);
                        FD_SET(fd2, &wfds);
                        DPRINTF("selecting write...\n");
                        if (select(fd2+1, NULL, &wfds, NULL, NULL) == -1) {
                                perror("select");
                                exit(-1);
                        }

                        if (FD_ISSET(fd2, &wfds)) {
                                if (write(fd2, buf, sizeof(buf)) != sizeof(buf)) {
                                        perror("write");
                                        exit(-1);
                                }
                        }
                        read_start = 1;
//                      sleep(1);
                }
        }
        close(fd2);

        return 0;
}
