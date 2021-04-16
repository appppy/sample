/* input.c */

#include <assert.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

void write_event(int type, int code, int value, int fd) {
    struct input_event event;
	event.type  = type;
    event.code  = code;
    event.value = value;
    write(fd, &event, sizeof(event));
}

int main(void)
{
//  int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);
  int fd = open("/dev/uinput", O_RDWR);
  //int fd = open("/dev/input/event10", O_RDWR);
  printf("fd = %d errno = %d \n",fd,errno);

  int i = 0x20;

  for (;;) {
    struct input_event event;

	printf("ON write %d \n",i);
    write_event(EV_KEY, i, 1, fd);
	printf("OFF write %d \n",i);
    write_event(EV_KEY, i, 0, fd);
	printf("sync\n");
    write_event(EV_SYN, i, 0, fd);
    i++;

    sleep(1); 

 }
  close(fd);
}