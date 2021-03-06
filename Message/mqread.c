#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <mqueue.h>
#include <fcntl.h>
#include <errno.h>

//#define DPRINTF(...)
#define DPRINTF(...) printf(__VA_ARGS__)

int main(int argc, char *argv[])
{
        mqd_t fd1, fd2;
        fd_set rfds, wfds;
        char buf[128];
        int read_start;
        unsigned int prio=10;
        struct mq_attr attr;
        char *rbuf;

        memset(&attr, 0, sizeof(attr));

        mq_unlink("/mq1");
        mq_unlink("/mq2");
        if ((fd1 = mq_open("/mq1", O_RDONLY|O_NONBLOCK|O_CREAT|O_EXCL,
                         S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, NULL)) == -1) {
                perror("open /mq1");
                exit(-1);
        }
        if ((fd2 = mq_open("/mq2", O_WRONLY|O_NONBLOCK|O_CREAT|O_EXCL,
                         S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH, NULL)) == -1) {
                perror("open /mq2");
                exit(-1);
        }

        mq_getattr(fd1,&attr);
        if((rbuf = malloc(attr.mq_msgsize)) == NULL) {
                fprintf(stderr, "malloc error\n");
                exit(-1);
        }

        read_start=1;
        while (1) {
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
                                n = mq_receive(fd1, rbuf, attr.mq_msgsize, &prio);
                                if (n > 0 ) {
                                        DPRINTF("%d = read [%s] prio=%d\n", n, rbuf, prio);
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
                                if (mq_send(fd2, buf, sizeof(buf), prio) != 0) {
                                        perror("write");
                                        exit(-1);
                                }
                        }
                        read_start = 1;
//                      sleep(1);
                }
        }
        mq_close(fd1);
        mq_close(fd2);

        return 0;
}

