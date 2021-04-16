/* input.c */

#include <assert.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>



int main(void)
{
  int fd = open("/dev/input/event0", O_RDWR);
  printf("fd = %d \n",fd);

  for (;;) {
    struct input_event event;

    printf("read\n");
    read(fd, &event, sizeof(event));
    printf("tv_sec: %lu, type: %04x, code: %04x, value: %08x\n", event.time.tv_sec, event.type, event.code, event.value);

    sleep(1); 

 }
  close(fd);
}