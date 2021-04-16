/* input.c */

#include <assert.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void write_event(int type, int code, int value, int fd) {
    struct input_event event;
	event.type  = type;
    event.code  = code;
    event.value = value;
    write(fd, &event, sizeof(event));
}

int main(void)
{
  int fd = open("/dev/input/event10", O_RDWR);
  printf("fd = %d \n",fd);

  int i = 0x20;

  for (;;) {
    struct input_event event;

	printf("write\n");
    write_event(EV_KEY, i, 1, fd);

    printf("read\n");
    read(fd, &event, sizeof(event));
    printf("tv_sec: %lu, type: %04x, code: %04x, value: %08x\n", event.time.tv_sec, event.type, event.code, event.value);
    fflush(stdout);
   
	printf("write\n");
    write_event(EV_KEY, i, 0, fd);
    
    printf("read\n");
    read(fd, &event, sizeof(event));
    printf("tv_sec: %lu, type: %04x, code: %04x, value: %08x\n", event.time.tv_sec, event.type, event.code, event.value);
    fflush(stdout);

    i++;

    sleep(1); 

 }
  close(fd);
}