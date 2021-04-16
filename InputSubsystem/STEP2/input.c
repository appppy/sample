#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/uinput.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(void)
{
	char name[256] = "Unknown";
 	int fd0 = open("/dev/input/event1", O_RDWR);
 	if( fd0 < 0) {
		printf("event0 NG %d \n",fd0);
	} else {
		printf("event0 OK %d \n",fd0);
		ioctl(fd0, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}

  	close(fd0);
	printf("fd %d \n",fd0);

}