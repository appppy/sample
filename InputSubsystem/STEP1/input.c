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


void write_event(int type, int code, int value, int fd) {
    struct input_event event;
	event.type  = type;
    event.code  = code;
    event.value = value;
    write(fd, &event, sizeof(event));
}

typedef struct ABC
{
	short a;
    char  b;
    char  c;
    char  d;
    char  e[100];
} ABC2;

typedef struct ABA
{
	short a;
    char  b;
    char  c;
    char  d;
} ABC3;

typedef struct ABB
{
    char  e[100];
} ABC4;

typedef struct ddd
{
	short a;
} ABC5;

typedef struct fff
{
    char  b;
    char  c;
    char  d;
} ABC6;

typedef struct ddddd
{
	short a;
    char  b;
    char  c;
    char  d;
    char  e;
} ABC7;

int main(void)
{
    ABC2 a;
    ABC3 b;
    ABC4 c;
	ABC5 d;
    ABC6 e;
	ABC7 f;
    
	printf("size %ld \n",sizeof(a));
	printf("size %ld \n",sizeof(b));
	printf("size %ld \n",sizeof(c));
	printf("size %ld \n",sizeof(d));
	printf("size %ld \n",sizeof(e));
	printf("size %ld \n",sizeof(f));
#if 0
	char name[256] = "Unknown";
 	int fd0 = open("/dev/input/event0", O_RDWR);
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
 	int fd1 = open("/dev/input/event1", O_RDWR);
 	if (fd1 < 0) {
		printf("event1 NG %d \n",fd1);
	} else {
		printf("event1 OK %d \n",fd1);
		ioctl(fd1, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd2 = open("/dev/input/event2", O_RDWR);
 	if (fd2 < 0) {
		printf("event2 NG %d \n",fd2);
	} else {
		printf("event2 OK %d \n",fd2);
		ioctl(fd2, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd3 = open("/dev/input/event3", O_RDWR);
 	if (fd3 < 0) {
		printf("event3 NG %d \n",fd3);
	} else {
		printf("event3 OK %d \n",fd3);
		ioctl(fd3, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd4 = open("/dev/input/event4", O_RDWR);
 	if (fd4 < 0) {
		printf("event4 NG %d \n",fd4);
	} else {
		printf("event4 OK %d \n",fd4);
		ioctl(fd4, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd5 = open("/dev/input/event5", O_RDWR);
 	if (fd5 < 0) {
		printf("event5 NG %d \n",fd5);
	} else {
		printf("event5 OK %d \n",fd5);
		ioctl(fd5, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd6 = open("/dev/input/event6", O_RDWR);
 	if (fd6 < 0) {
		printf("event6 NG %d \n",fd6);
	} else {
		printf("event6 OK %d \n",fd6);
		ioctl(fd6, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd7 = open("/dev/input/event7", O_RDWR);
 	if (fd7 < 0) {
		printf("event7 NG %d \n",fd7);
	} else {
		printf("event7 OK %d \n",fd7);
		ioctl(fd7, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd8 = open("/dev/input/event8", O_RDWR);
 	if (fd8 < 0) {
		printf("event8 NG %d \n",fd8);
	} else {
		printf("event8 OK %d \n",fd8);
		ioctl(fd8, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd9 = open("/dev/input/event9", O_RDWR);
 	if (fd9 < 0) {
		printf("event9 NG %d \n",fd9);
	} else {
		printf("event9 OK %d \n",fd9);
		ioctl(fd9, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd10 = open("/dev/input/event10", O_RDWR);
 	if (fd10 < 0) {
		printf("event10 NG %d \n",fd10);
	} else {
		printf("event10 OK %d \n",fd10);
		ioctl(fd10, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd11 = open("/dev/input/event11", O_RDWR);
 	if (fd11 < 0) {
		printf("event11 NG %d \n",fd11);
	} else {
		printf("event11 OK %d \n",fd11);
		ioctl(fd11, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd12 = open("/dev/input/event12", O_RDWR);
 	if (fd12 < 0) {
		printf("event12 NG %d \n",fd12);
	} else {
		printf("event12 OK %d \n",fd12);
		ioctl(fd12, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd13 = open("/dev/input/event13", O_RDWR);
 	if (fd13 < 0) {
		printf("event13 NG %d \n",fd13);
	} else {
		printf("event13 OK %d \n",fd13);
		ioctl(fd13, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd14 = open("/dev/input/event14", O_RDWR);
 	if (fd14 < 0) {
		printf("event14 NG %d \n",fd14);
	} else {
		printf("event14 OK %d \n",fd14);
		ioctl(fd14, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd15 = open("/dev/input/event15", O_RDWR);
 	if (fd15 < 0) {
		printf("event15 NG %d \n",fd15);
	} else {
		printf("event15 OK %d \n",fd15);
		ioctl(fd15, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd16 = open("/dev/input/event16", O_RDWR);
 	if (fd16 < 0) {
		printf("event16 NG %d \n",fd16);
	} else {
		printf("event16 OK %d \n",fd16);
		ioctl(fd16, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd17 = open("/dev/input/event17", O_RDWR);
 	if (fd17 < 0) {
		printf("event17 NG %d \n",fd17);
	} else {
		printf("event17 OK %d \n",fd17);
		ioctl(fd17, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}
 	int fd18 = open("/dev/input/event18", O_RDWR);
 	if (fd18 < 0) {
		printf("event18 NG %d \n",fd18);
	} else {
		printf("event18 OK %d \n",fd18);
		ioctl(fd18, EVIOCGNAME(sizeof(name)),name);
		printf("name %s \n", name);
		if (strstr(name, "Keyboard") != NULL) {
			printf("OK \n");
		} else {
			printf("NG \n");
		}
	}

	int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);	
	ioctl(fd, UI_SET_EVBIT, EV_KEY);

 
	int i;
    for(i=0; i<0x0FFF; i++) {
		//printf("i=%d\n",i);
    	ioctl(fd, UI_SET_KEYBIT, i);
	}
	//ioctl(fd, UI_SET_KEYBIT, KEY_SPACE);
   	struct uinput_setup usetup;
    memset(&usetup, 0, sizeof(usetup));
    usetup.id.bustype = BUS_USB;
    usetup.id.vendor = 0x1234; /* sample vendor */
    usetup.id.product = 0x5678; /* sample product */
    strcpy(usetup.name, "Example device");

    ioctl(fd, UI_DEV_SETUP, &usetup);
    ioctl(fd, UI_DEV_CREATE);

	int fd19 = open("/dev/input/event19", O_RDWR);
 	if (fd19 < 0) {
		printf("event19 NG %d \n",fd19);
	} else {
		printf("event19 OK %d \n",fd19);
	}

 	if (fd < 0) {
		printf("event NG %d \n",fd);
	} else {
		printf("event OK %d \n",fd);
	}

	sleep(1);

 	for (;;) {
		struct input_event event;
		struct input_event event_r;

		printf("READ...\n");
		read(fd2, &event, sizeof(event));
		printf("  tv_sec: %lu, type: %04x, code: %04x, value: %08x\n", event.time.tv_sec, event.type, event.code, event.value);
		fflush(stdout);

		if (event.type == EV_KEY) {
			printf("-------------------WRITE..\n");
			int code = event.code + 0x400;
			write_event(event.type,     KEY_SPACE,       event.value, fd);
			sleep(1);
			printf("-------------------READ...\n");
			read(fd19, &event_r, sizeof(event_r));
			printf("-------------------tv_sec: %lu, type: %04x, code: %04x, value: %08x\n", event_r.time.tv_sec, event_r.type, event_r.code, event_r.value);
			printf("-------------------WRITE..\n");
			write_event(EV_SYN,     	SYN_REPORT,           0, fd);
			sleep(1);
			printf("-------------------READ...\n");
			read(fd19, &event_r, sizeof(event_r));
			printf("-------------------tv_sec: %lu, type: %04x, code: %04x, value: %08x\n", event_r.time.tv_sec, event_r.type, event_r.code, event_r.value);
			fflush(stdout);
		}
	}

	close(fd0);
  	close(fd1);
  	close(fd2);
  	close(fd3);
  	close(fd4);
  	close(fd5);
  	close(fd6);
  	close(fd7);
  	close(fd8);
  	close(fd9);
  	close(fd10);
  	close(fd11);
  	close(fd12);
  	close(fd13);
  	close(fd14);
  	close(fd15);
  	close(fd16); 
  	close(fd17);
  	close(fd18);
  	close(fd19);
  	close(fd);
#endif


}