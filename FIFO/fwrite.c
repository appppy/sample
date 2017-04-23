#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <errno.h>

//#define DPRINTF(...)
#define DPRINTF(...) printf(__VA_ARGS__)

int main(int argc, char *argv[])
{
        int fd1, fd2;
        fd_set rfds, wfds;
        char buf[128];
        int read_start;
        int nloop, i;

        if (argc != 2) {
                printf("usage:\n./fwrite <NLOOP>\n");
                exit(-1);
        }
        nloop = atoi(argv[1]);

        if ((fd1 = open("/tmp/fifo2", O_RDONLY|O_NONBLOCK)) == -1) {
                perror("open /tmp/fifo2");
                exit(-1);
        }
        if ((fd2 = open("/tmp/fifo1", O_WRONLY|O_NONBLOCK)) == -1) {
                perror("open /tmp/fifo1");
                exit(-1);
        }

        read_start=0;
        for (i=0; i<nloop; i++) {
                if (read_start) {
                        buf[0] = '\0';

                        FD_ZERO(&rfds);
                        FD_SET(fd1, &rfds);

                        DPRINTF("selecting read...\n");
                        if (select(fd1+1, &rfds, NULL, NULL, NULL) == -1) {
                                perror("select");
                        }

                        if (FD_ISSET(fd1, &rfds)) {
                                int n;
                                n = read(fd1, buf, sizeof(buf));
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
        printf("write loop= %d\n", i/2);
        close(fd1);
        close(fd2);

        return 0;
}
